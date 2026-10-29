#pragma once

#ifndef vitabits_h_
#define vitabits_h_

#ifdef __PSP2__

// Folder on the memory card holding DUKE3D.GRP and the DNA4PC mod folder.
#define VITA_DATA_DIR "ux0:data/dna"

// Optional file in VITA_DATA_DIR with extra command-line arguments.
#define VITA_ARGS_FILE VITA_DATA_DIR "/args.txt"

void vita_preinit(int *argc, char ***argv);

enum
{
    VITA_TOUCH_L2 = 1, // left half of the rear touchpad, or the front screen's top-left corner
    VITA_TOUCH_R2 = 2, // right half of the rear touchpad, or the front screen's top-right corner
    VITA_TOUCH_FRONT = 4, // anywhere else on the front screen
};

// Returns the VITA_TOUCH_* zones currently pressed.
int vita_readtouchtriggers(void);

#endif

#endif // vitabits_h_
