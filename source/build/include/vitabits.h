#pragma once

#ifndef vitabits_h_
#define vitabits_h_

#ifdef __PSP2__

// Folder on the memory card holding DUKE3D.GRP and the DNA4PC mod folder.
#define VITA_DATA_DIR "ux0:data/dna"

// Read-only copy of the same files inside the VPK, present only in builds made with the game data bundled.
// Settings and saves still go to VITA_DATA_DIR.
#define VITA_BUNDLED_DIR "app0:data"

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

// Returns 1 once each time the system UI (LiveArea, the PS button menu) takes over the screen,
// or the app comes back from being suspended, so the game can pause itself.
int vita_systemuitookover(void);

// Reads the gyroscope in radians per second, for a Vita held in landscape:
// yaw is positive when turning left and pitch is positive when tilting the top edge towards you.
void vita_readgyro(float *yaw, float *pitch);

// Pins the calling thread to one of the three CPU cores user code can run on (0-2).
void vita_setthreadcore(int core);

// Converts an 8-bit frame through palette into 32-bit pixels at dst, pitch bytes apart.
void vita_convertframe(uint32_t *dst, int pitch, uint8_t const *src, int w, int h, uint32_t const *palette);

#endif

#endif // vitabits_h_
