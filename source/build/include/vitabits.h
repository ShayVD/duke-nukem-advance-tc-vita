#pragma once

#ifndef vitabits_h_
#define vitabits_h_

#ifdef __PSP2__

// Folder on the memory card holding DUKE3D.GRP and the DNA4PC mod folder.
#define VITA_DATA_DIR "ux0:data/dna"

// Optional file in VITA_DATA_DIR with extra command-line arguments.
#define VITA_ARGS_FILE VITA_DATA_DIR "/args.txt"

void vita_preinit(int *argc, char ***argv);

#endif

#endif // vitabits_h_
