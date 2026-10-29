// PS Vita platform glue: memory setup, clocks, data folder and default arguments.

#ifdef __PSP2__

#include "compat.h"
#include "vitabits.h"

#include <psp2/appmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/motion.h>
#include <psp2/power.h>
#include <psp2/touch.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <unistd.h>

extern "C" {
// Leave room for SDL's GXM buffers and the audio thread outside the newlib heap.
int _newlib_heap_size_user = 300 * 1024 * 1024;
unsigned int sceUserMainThreadStackSize = 4 * 1024 * 1024;
}

// newlib on Vita has memalign but not posix_memalign
extern "C" int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    *memptr = memalign(alignment, size);
    return *memptr ? 0 : ENOMEM;
}

#define VITA_MAX_ARGS 64

static char *vita_argv[VITA_MAX_ARGS + 1];
static int vita_argc;

static void vita_addarg(char const *arg)
{
    // Runs before engineSetupAllocator(), so Xstrdup can't be used yet.
    if (vita_argc < VITA_MAX_ARGS)
        vita_argv[vita_argc++] = strdup(arg);
}

static int vita_isdir(char const *path)
{
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

// Reads whitespace-separated arguments from VITA_ARGS_FILE. Returns 0 if the file is missing.
static int vita_readargsfile(void)
{
    FILE *fp = fopen(VITA_ARGS_FILE, "r");

    if (!fp)
        return 0;

    char token[BMAX_PATH];

    while (fscanf(fp, "%255s", token) == 1)
        vita_addarg(token);

    fclose(fp);
    return 1;
}

void vita_preinit(int *argc, char ***argv)
{
    scePowerSetArmClockFrequency(444);
    scePowerSetBusClockFrequency(222);
    scePowerSetGpuClockFrequency(222);
    scePowerSetGpuXbarClockFrequency(166);

    // The game runs on core 0, leaving core 1 to present frames (see videoShowFrame()).
    vita_setthreadcore(0);

    mkdir(VITA_DATA_DIR, 0777);
    chdir(VITA_DATA_DIR);

    vita_addarg(*argc > 0 && (*argv)[0] ? (*argv)[0] : "eduke32");

    for (int i = 1; i < *argc; i++)
        vita_addarg((*argv)[i]);

    // With no arguments from the launcher, boot straight into the mod when it is installed.
    if (*argc <= 1 && !vita_readargsfile())
    {
        vita_addarg("-usecwd");
        vita_addarg("-nosetup");

        if (vita_isdir(VITA_DATA_DIR "/DNA4PC"))
        {
            vita_addarg("-game_dir");
            vita_addarg("DNA4PC");
        }
    }

    vita_argv[vita_argc] = NULL;

    *argc = vita_argc;
    *argv = vita_argv;
}

// Touch panel coordinates: both panels report x in 0..1919; the front reports y in 0..1087.
#define VITA_TOUCH_WIDTH 1920
#define VITA_FRONT_CORNER_W 480
#define VITA_FRONT_CORNER_H 272

int vita_readtouchtriggers(void)
{
    static int initialized;

    if (!initialized)
    {
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
        initialized = 1;
    }

    int zones = 0;
    SceTouchData touch;

    if (sceTouchPeek(SCE_TOUCH_PORT_BACK, &touch, 1) > 0)
    {
        for (unsigned i = 0; i < touch.reportNum; i++)
            zones |= touch.report[i].x < VITA_TOUCH_WIDTH / 2 ? VITA_TOUCH_L2 : VITA_TOUCH_R2;
    }

    if (sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1) > 0)
    {
        for (unsigned i = 0; i < touch.reportNum; i++)
        {
            if (touch.report[i].y < VITA_FRONT_CORNER_H && touch.report[i].x < VITA_FRONT_CORNER_W)
                zones |= VITA_TOUCH_L2;
            else if (touch.report[i].y < VITA_FRONT_CORNER_H && touch.report[i].x >= VITA_TOUCH_WIDTH - VITA_FRONT_CORNER_W)
                zones |= VITA_TOUCH_R2;
            else
                zones |= VITA_TOUCH_FRONT;
        }
    }

    return zones;
}

// SDK build version passed to SceAppMgr; firmware 3.60 accepts anything up to 0x03600011.
#define VITA_APPMGR_BUILD_VERSION 0x03570011

// SceAppMgrSystemEventType values. Older vitasdk headers, like the one in the CI image, lack ON_DEACTIVATE.
#define VITA_SYSTEMEVENT_ON_DEACTIVATE 0x10000002
#define VITA_SYSTEMEVENT_ON_RESUME     0x10000003

int vita_systemuitookover(void)
{
    static int wasoverlaid;

    SceAppMgrAppState state;
    Bmemset(&state, 0, sizeof(state));

    if (_sceAppMgrGetAppState(&state, sizeof(state), VITA_APPMGR_BUILD_VERSION) < 0)
        return 0;

    int tookover = state.isSystemUiOverlaid && !wasoverlaid;
    wasoverlaid = state.isSystemUiOverlaid;

    for (unsigned i = 0; i < state.systemEventNum; i++)
    {
        SceAppMgrSystemEvent event;

        if (sceAppMgrReceiveSystemEvent(&event) < 0)
            break;

        // Leaving for the LiveArea deactivates the app, and coming back after the system suspended it resumes it.
        if (event.systemEvent == VITA_SYSTEMEVENT_ON_DEACTIVATE || event.systemEvent == VITA_SYSTEMEVENT_ON_RESUME)
            tookover = 1;
    }

    return tookover;
}

// Ignore the slow drift left in a resting gyro.
#define VITA_GYRO_DEADZONE 0.015f

static float vita_gyrodeadzone(float v)
{
    if (v > VITA_GYRO_DEADZONE)
        return v - VITA_GYRO_DEADZONE;
    if (v < -VITA_GYRO_DEADZONE)
        return v + VITA_GYRO_DEADZONE;
    return 0.f;
}

void vita_readgyro(float *yaw, float *pitch)
{
    static int initialized;

    if (!initialized)
    {
        sceMotionStartSampling();
        initialized = 1;
    }

    SceMotionSensorState sensor;

    if (sceMotionGetSensorState(&sensor, 1) < 0)
    {
        *yaw = *pitch = 0.f;
        return;
    }

    *yaw   = vita_gyrodeadzone(sensor.gyro.y);
    *pitch = vita_gyrodeadzone(sensor.gyro.x);
}

#ifndef SCE_KERNEL_CPU_MASK_USER_0
# define SCE_KERNEL_CPU_MASK_USER_0 0x00010000
#endif

void vita_setthreadcore(int core)
{
    sceKernelChangeThreadCpuAffinityMask(sceKernelGetThreadId(), SCE_KERNEL_CPU_MASK_USER_0 << core);
}

void vita_convertframe(uint32_t *dst, int pitch, uint8_t const *src, int w, int h, uint32_t const *palette)
{
    for (int y = 0; y < h; y++)
    {
        uint32_t *__restrict d = (uint32_t *)((char *)dst + y * pitch);
        uint8_t const *__restrict s = src + y * w;
        int x = 0;

        for (; x <= w - 8; x += 8, s += 8, d += 8)
        {
            d[0] = palette[s[0]]; d[1] = palette[s[1]]; d[2] = palette[s[2]]; d[3] = palette[s[3]];
            d[4] = palette[s[4]]; d[5] = palette[s[5]]; d[6] = palette[s[6]]; d[7] = palette[s[7]];
        }

        for (; x < w; x++)
            *d++ = palette[*s++];
    }
}

#endif
