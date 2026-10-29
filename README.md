# Duke Nukem Advance for PS Vita

Play the whole Game Boy Advance campaign of Duke Nukem Advance on your PS Vita.

This is a PS Vita port of [EDuke32](https://www.eduke32.com/) built to run
[Duke Nukem Advance TC (DNA4PC)](https://www.moddb.com/mods/duke-nukem-advance-tc),
the total conversion that remakes Duke Nukem Advance in the Duke Nukem 3D
engine.

This repository only contains the game engine. You supply the game data
yourself: the Duke Nukem 3D data file and the DNA4PC mod.

**Contents**

- [Quick start](#quick-start)
- [What you need](#what-you-need)
- [Installing](#installing)
- [Controls](#controls)
- [Vita settings](#vita-settings)
- [What this port adds for the Vita](#what-this-port-adds-for-the-vita)
- [Troubleshooting](#troubleshooting)
- [Advanced: launch options](#advanced-launch-options)
- [Building it yourself](#building-it-yourself)
- [Credits](#credits)

## Quick start

1. Install `dna-vita.vpk` with VitaShell.
2. Put `DUKE3D.GRP` and the `DNA4PC` folder in `ux0:data/dna/`.
3. Launch **Duke Nukem Advance** from the home screen.

The rest of this page explains each step.

## What you need

| Item | Where to get it |
| --- | --- |
| A PS Vita or PS TV with homebrew enabled (HENkaku, h-encore or Ensō) | Any homebrew guide for your firmware |
| [VitaShell](https://github.com/TheOfficialFloW/VitaShell) | Its GitHub releases |
| `dna-vita.vpk` | See [Getting the VPK](#getting-the-vpk) |
| `DUKE3D.GRP`, Duke Nukem 3D 1.4/1.5 (Atomic Edition), about 43 MB | The GOG release of Atomic Edition, or the Steam/GOG Megaton Edition (in its `gameroot` folder). The original CD is also on the [Internet Archive](https://archive.org/details/DukeNukem3DUSAAtomicEdition). |
| DNA4PC 1.0 (only its `DNA4PC` folder, about 33 MB) | [ModDB](https://www.moddb.com/mods/duke-nukem-advance-tc) or [GitHub](https://github.com/branung/DNA4PC) |

The shareware `DUKE3D.GRP` will not work. The 20th Anniversary World Tour data
has not been tested.

### Getting the VPK

Download `dna-vita.vpk` from the latest release on this repository's Releases
page. Until there is a release, open the latest successful **Vita build** run
under the repository's Actions tab and download the `dna-vita` artifact (you
need to be signed in to GitHub). It's a zip that holds `dna-vita.vpk` and
`eduke32.elf`, which is only used to read crash dumps.

## Installing

1. **Install the VPK.** Copy `dna-vita.vpk` to the Vita (for example to
   `ux0:VPK/`), open it in VitaShell and press Cross to install it. A
   "Duke Nukem Advance" bubble appears on the home screen.
2. **Create the data folder** `ux0:data/dna/`. The game also creates it the
   first time it runs.
3. **Copy the game data** so the folder looks like this:

   ```
   ux0:data/dna/
   ├── DUKE3D.GRP
   └── DNA4PC/
       ├── EDUKE.CON
       ├── dna.def
       ├── maps/
       ├── music/
       ├── sounds/
       └── ... (the rest of the DNA4PC folder, unchanged)
   ```

   - Copy the `DNA4PC` folder itself, not the folder that contains it. You
     should see `ux0:data/dna/DNA4PC/EDUKE.CON`.
   - If it's easier, copy everything from the DNA4PC download (the `DNA4PC`
     folder and the files next to it) into `ux0:data/dna/` as it is. The
     Windows files that come with it, such as `eduke32.exe` and the PC
     `eduke32.cfg`, are ignored on the Vita.
   - To copy files, use VitaShell's FTP server (press Select in VitaShell) or
     its USB mode. File names are not case sensitive on the memory card.
4. **Launch the bubble.** The game skips the EDuke32 launcher and boots
   straight into Duke Nukem Advance. The first start takes about 13 seconds,
   and loading a level about 7 seconds.

## Controls

| Vita | Action |
| --- | --- |
| Left stick | Move and strafe |
| Right stick | Turn and look up/down |
| R | Fire |
| L | Jump |
| Rear touchpad, right half (or the front screen's top-right corner) | Alt fire (acts as R2) |
| Rear touchpad, left half (or the front screen's top-left corner) | Crouch (acts as L2) |
| Circle | Toggle crouch |
| Cross | Open / use, and confirm in menus |
| Square | Use inventory item |
| Triangle | Quick kick |
| D-pad up / down | Previous / next weapon |
| D-pad left / right | Previous / next inventory item |
| Select | DNA's mod menu (customize options in-game) |
| Tap the front screen | Map |
| Start | Main menu |
| Tilt and turn the Vita | Aim, when gyro aiming is on (off by default) |

Auto run is on by default. You can rebind everything under
**Options > Control Setup > Controller Setup**, and the mod's on-screen prompts
follow your bindings.

## Vita settings

These options are specific to the Vita build.

| Setting | Where | What it does |
| --- | --- | --- |
| **Resolution:** Half / Full | Options > Display Setup | Half (default) renders at 480x272 and the GPU scales it to the screen. Full renders at the Vita's native 960x544, which is sharper but slower. |
| **Show FPS:** Off / On | Options > Display Setup | Shows the frame rate in the corner, handy for comparing settings. |
| **VSync:** On / Off | Options > Display Setup > Video mode (then Apply) | On (default) avoids screen tearing. Off can raise the frame rate. |
| **Gyro aiming:** Off / On | Options > Control Setup > Controller Setup | Turning the Vita left or right turns the view, and tilting it looks up or down. Works together with the right stick. |
| **Gyro sens.:** 25% to 400% | Options > Control Setup > Controller Setup | How far the view turns for a given motion. At 100% the view turns twice as far as the Vita does. |

Settings are saved in `ux0:data/dna/eduke32-vita.cfg` and `settings.cfg`. The
gyro settings can also be set from the console as `in_gyro` and `in_gyrosens`.

## What this port adds for the Vita

On top of getting EDuke32 and DNA4PC running on the Vita at all, this port
adds:

**Controls and prompts**

- A control scheme made for the Vita (see [Controls](#controls)), with the
  rear touchpad and the front screen's top corners standing in for the L2/R2
  triggers the Vita doesn't have.
- **Select opens DNA's mod menu** and **a tap on the front screen opens the
  map**.
- Vita button names (Cross, Circle, Select and so on) everywhere the game names
  a button, including the controller setup menu.
- The mod's on-screen prompts show Vita buttons instead of keyboard keys. For
  example, the new game screens say `[CROSS]` and `[SELECT]` instead of
  `[ENTER]` and `[BACKSPACE]`, and the death screen says `PRESS CROSS TO
  RESTART LEVEL`. This is done in the engine, so the mod's files
  stay untouched.
- **Optional gyro aiming**, with its own sensitivity setting.

**System integration**

- **Pauses when you press the PS button.** Going to the LiveArea or opening the
  quick menu mid-level brings up the pause menu, so you don't come back to a
  game that kept running, or one that tries to catch up after a suspend.
- **Duke Nukem Advance LiveArea art**: icon, start gate and background, built
  from the mod's own graphics.
- Boots straight into the mod, with no launcher, and keeps all its files in
  `ux0:data/dna/`. The DNA4PC download can be copied as it is: the Vita uses
  its own `eduke32-vita.cfg`, so the Windows `eduke32.cfg` is ignored.

**Speed and display**

- **Faster loading.** Sounds load the first time they play instead of all up
  front (which took about 25 seconds at startup and again at every level), and
  the engine skips file checks for high-res textures the software renderer
  can't use. The game starts in about 13 seconds and levels load in about 7.
- **Native GXM rendering.** Frames go straight to the Vita's GPU, which scales
  them to the screen.
- **Frame presentation on a second CPU core.** The game runs on one core while
  another converts and shows the finished frame, which is what lets Full
  resolution run smoothly.
- **Full or Half resolution**, a **Show FPS** toggle, and a **VSync** option
  that works on the Vita.
- **No flash of the mission briefing during loading.** DNA hides the loading
  screen, which used to leave the briefing on screen at full brightness while a
  level loaded. The screen now goes black instead.

## Troubleshooting

- **You get plain Duke Nukem 3D instead of Duke Nukem Advance.** The
  `DNA4PC` folder is missing or in the wrong place. It must be at
  `ux0:data/dna/DNA4PC/`, with `EDUKE.CON` directly inside it.
- **The game can't find its data and quits.** Check that `DUKE3D.GRP` is
  directly in `ux0:data/dna/` and is the full 43 MB version, not shareware.
- **You want to reset all settings and controls.** Delete
  `ux0:data/dna/eduke32-vita.cfg` and `settings.cfg`. The game recreates them
  with the Vita defaults.
- **Anything else.** The game writes a log to `ux0:data/dna/eduke32.log` on
  every run. Check the end of it, or attach it to a bug report.

## Advanced: launch options

To pass your own EDuke32 command-line options, create `ux0:data/dna/args.txt`
with the options separated by spaces or new lines. When this file exists it
replaces the defaults, so include them if you still want them. The defaults
are:

```
-usecwd -nosetup -game_dir DNA4PC
```

## Building it yourself

Install [VitaSDK](https://vitasdk.org/) with its SDL2 package (`vdpm SDL2`),
set `VITASDK`, then run:

```sh
./platform/PSVita/build.sh
```

The VPK is written to `build/vita/dna-vita.vpk`. If the build fails, the full
log is in `build-vita.log`. GitHub Actions builds the VPK on every push (see
`.github/workflows/vita.yml`).

`platform/PSVita/make_livearea.py <path to the DNA4PC folder>` rebuilds the
LiveArea images from the mod's graphics (needs Python and Pillow).

All Vita-specific code is behind `__PSP2__`; most of it is in
`source/build/src/vitabits.cpp` and `source/build/src/sdlayer.cpp`.

## Credits

- [EDuke32](https://www.eduke32.com/) by the EDuke32 team (voidpoint).
- DNA4PC by branung, oasiz, Voxelvoid and contributors; see the mod's readme
  for the full credits.
- Duke Nukem Advance by Torus Games; Duke Nukem 3D by 3D Realms.
