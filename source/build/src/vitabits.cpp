// PS Vita platform glue: memory setup, clocks, data folder and default arguments.

#ifdef __PSP2__

#include "compat.h"
#include "vitabits.h"

#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>
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

#endif
