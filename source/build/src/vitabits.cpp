// PS Vita platform glue: memory setup, clocks, data folder and default arguments.

#ifdef __PSP2__

#include "compat.h"
#include "vitabits.h"

#include <psp2/appmgr.h>
#include <psp2/kernel/processmgr.h>
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
        if (event.systemEvent == SCE_APPMGR_SYSTEMEVENT_ON_DEACTIVATE || event.systemEvent == SCE_APPMGR_SYSTEMEVENT_ON_RESUME)
            tookover = 1;
    }

    return tookover;
}

#endif
