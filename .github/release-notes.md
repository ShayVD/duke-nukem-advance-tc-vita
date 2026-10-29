Duke Nukem Advance on your PS Vita: a native port of EDuke32 running the
[Duke Nukem Advance TC (DNA4PC)](https://www.moddb.com/mods/duke-nukem-advance-tc)
by branung and oasiz.

**No game data is included.** You need:

1. `DUKE3D.GRP` from the full Duke Nukem 3D (Atomic Edition, or Megaton Edition from Steam/GOG). Shareware won't work.
2. DNA4PC 1.0 from [ModDB](https://www.moddb.com/mods/duke-nukem-advance-tc).

### Install

1. Install `dna-vita.vpk` with VitaShell.
2. Put `DUKE3D.GRP` and the `DNA4PC` folder in `ux0:data/dna/`, so that `ux0:data/dna/DNA4PC/EDUKE.CON` exists.
3. Launch **Duke Nukem Advance**. If a file is missing, the game tells you which one.

Full guide, controls and troubleshooting: see the [README](https://github.com/ShayVD/duke-nukem-advance-tc-vita#readme).

### Features

- The whole campaign, all 19 levels, with the TC's options
- Vita controls: rear touchpad as L2/R2, Select for the mod menu, tap the screen for the map, Vita button names in every prompt
- Optional gyro aiming
- Half (480x272) or Full (960x544) resolution, VSync option, FPS counter
- Pauses on the PS button; levels load in about 7 seconds

### AI use

This port was made with heavy use of AI: Claude (Anthropic's coding assistant) wrote most of the Vita-specific code under Shay's direction, and Shay tested the builds on real hardware. The engine (EDuke32) and the game content (DNA4PC) were not written by AI.

### Licence

GPL v2 (game code) and Ken Silverman's BUILD licence (engine core); see `LICENSE` and `NOTICE.md`. The full source for this release is attached below as the source code archives.

Credits: branung, oasiz, Voxelvoid and the DNA4PC team for the TC; the EDuke32 team and Ken Silverman for the engine; Torus Games for the original Duke Nukem Advance.
