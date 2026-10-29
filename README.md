# Duke Nukem Advance for PS Vita

Play the whole Game Boy Advance campaign of Duke Nukem Advance on your PS Vita.

This is a PS Vita port of [EDuke32](https://www.eduke32.com/) built to run the
[Duke Nukem Advance TC (DNA4PC)](https://www.moddb.com/mods/duke-nukem-advance-tc)
by branung and oasiz, the total conversion that remakes Duke Nukem Advance in
the Duke Nukem 3D engine.

This repository and the VPK only contain the game engine. **No game data is
included.** You supply two things yourself: `DUKE3D.GRP` from your own copy of
Duke Nukem 3D, and the DNA4PC mod from its authors.

**Contents**

- [Features](#features)
- [Quick start](#quick-start)
- [What you need](#what-you-need)
- [Installing](#installing)
- [Controls](#controls)
- [Saving and loading](#saving-and-loading)
- [Vita settings](#vita-settings)
- [What this port adds for the Vita](#what-this-port-adds-for-the-vita)
- [Known issues](#known-issues)
- [Troubleshooting](#troubleshooting)
- [Advanced](#advanced)
- [Building it yourself](#building-it-yourself)
- [Credits](#credits)
- [AI use](#ai-use)
- [Licence](#licence)

## Features

- The full Duke Nukem Advance campaign (all 19 levels of DNA4PC 1.0) with the
  TC's options: PC Enhanced or GBA Original style, USA or EU script, and
  optional voiced cutscenes.
- Controls made for the Vita, with the rear touchpad as L2/R2, and Vita button
  names in every on-screen prompt.
- Optional gyro aiming.
- Native GPU output with Half (480x272, default) or Full (960x544)
  resolution, a VSync option and an FPS counter.
- Pauses when you press the PS button.
- A clear on-screen message if `DUKE3D.GRP` or the mod is missing.
- Boots straight into the game, with fast loading (about 7 seconds per level).

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
| `dna-vita.vpk` | This repository's Releases page |
| `DUKE3D.GRP` from the full game, about 43 MB | Your own copy of Duke Nukem 3D, see below |
| DNA4PC 1.0 (its `DNA4PC` folder, about 33 MB) | [ModDB](https://www.moddb.com/mods/duke-nukem-advance-tc) or [branung's GitHub](https://github.com/branung/DNA4PC) |

### Which Duke Nukem 3D works

| Edition | Works? | Where `DUKE3D.GRP` is |
| --- | --- | --- |
| Atomic Edition 1.4 / 1.5 (CD, or the GOG release) | Yes, recommended | The game folder |
| Megaton Edition (Steam, GOG) | Yes | The `gameroot` folder |
| 1.3D (original registered release) | Should work, not tested | The game folder |
| 20th Anniversary World Tour | Not tested | |
| Shareware (about 11 MB) | No. The game tells you if it finds it | |

The Atomic Edition `DUKE3D.GRP` is 44,356,548 bytes.

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

If a file is missing or in the wrong place, the game shows a message saying
which one and where it should go, then closes. The same message is saved to
`ux0:data/dna/error.txt`.

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

## Saving and loading

Press Start, choose **Save Game**, pick a slot and press Cross twice. The Vita
has no keyboard, so saves are named after the level. Load from **Load Game**
in the same menu. Checkpoint autosaves can be turned on or off under
**Options > Save Setup**.

Saves are kept in `ux0:data/dna/DNA4PC/` as `save0000.esv` and so on, so they
survive reinstalling or updating the VPK.

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
- **Duke Nukem Advance LiveArea art**: icon, start gate and background.
- Boots straight into the mod, with no launcher, and keeps all its files in
  `ux0:data/dna/`. The DNA4PC download can be copied as it is: the Vita uses
  its own `eduke32-vita.cfg`, so the Windows `eduke32.cfg` is ignored.
- **Checks the game data at startup** and explains on screen what is missing,
  instead of crashing or starting plain Duke Nukem 3D.

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

## Known issues

- No multiplayer. Network play is not built for the Vita.
- Save names can't be typed; saves are named after the level.
- Tapping anywhere on the front screen (outside its top corners) opens the
  map, so a stray touch can open it. You can unbind it under Controller Setup.
- Sounds load from the memory card the first time each one plays, which can
  cause a very short hitch the first time you hear a new sound.
- The TC's own known issues apply too (from its readme): the second page of
  its customize menu isn't functional yet, some later maps use masked walls
  for vines, and the freezer works differently from the GBA original.

Please report anything else on this repository's Issues page, with
`ux0:data/dna/eduke32.log` attached.

## Troubleshooting

- **A message says DUKE3D.GRP is missing or is the shareware version.** Put
  the full game's `DUKE3D.GRP` directly in `ux0:data/dna/` (see
  [Which Duke Nukem 3D works](#which-duke-nukem-3d-works)).
- **A message says DNA4PC is missing or one level too deep.** The game needs
  `ux0:data/dna/DNA4PC/EDUKE.CON`. If you have
  `ux0:data/dna/DNA4PC/DNA4PC/EDUKE.CON`, move the inner folder up one level.
- **You want to reset all settings and controls.** Delete
  `ux0:data/dna/eduke32-vita.cfg` and `settings.cfg`. The game recreates them
  with the Vita defaults.
- **Anything else.** The game writes a log to `ux0:data/dna/eduke32.log` on
  every run. Check the end of it, or attach it to a bug report.

## Advanced

### Launch options

To pass your own EDuke32 command-line options, create `ux0:data/dna/args.txt`
with the options separated by spaces or new lines. When this file exists it
replaces the defaults, and the startup data check is skipped. The defaults
are:

```
-usecwd -nosetup -game_dir DNA4PC
```

### All-in-one VPK for your own use

You can add your own game data to the VPK on your computer, so installing it
is the only step on the Vita:

```sh
./platform/PSVita/bundle_data.sh dna-vita.vpk <data folder>
```

`<data folder>` is a folder on your computer laid out like `ux0:data/dna/`
above, with `DUKE3D.GRP` and the `DNA4PC` folder in it. The script writes
`dna-vita-full.vpk` (about 80 MB) next to `dna-vita.vpk`. It only needs `zip`.

The data is installed with the app, read-only. Settings, saves and the log
still go to `ux0:data/dna/`, and anything you put in `ux0:data/dna/DNA4PC/`
takes priority over the bundled copy. **The result contains commercial game
data and the TC's files: keep it to yourself and don't share it.**

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

The port is based on EDuke32 r10652. All Vita-specific code is behind
`__PSP2__`; most of it is in `source/build/src/vitabits.cpp` and
`source/build/src/sdlayer.cpp`.

## Credits

**PS Vita port:** Shay (ShayVD), with the porting code written by Claude, an
AI assistant (see [AI use](#ai-use)).

**Duke Nukem Advance TC (DNA4PC)**, as credited in the mod's readme:

- branung: project lead, main code, art, mapping, design
- oasiz: map effects, editor support, additional code and design
- Voxelvoid: initial work, export of maps and texture assets
- Dzierzan: lead cannon HUD recreation art
- Jimmy Gnosis: pipebomb HUD tile fixes
- Hendricks266: GBA 3DR title graphics palette conversion assistance
- Gianni Matragrano: voice of Duke's lines in cutscenes, when enabled

**Engine**

- [EDuke32](https://www.eduke32.com/) by the EDuke32 team (voidpoint) and
  contributors, building on JonoF's JFBuild/JFDuke3D.
- Build engine by Ken Silverman.
- Duke Nukem 3D by 3D Realms, whose source was released under the GPL.
- [VitaSDK](https://vitasdk.org/) and its SDL2 port.

**Original game:** Duke Nukem Advance by Torus Games, published by Take-Two
Interactive in 2002. Duke Nukem is a trademark of Gearbox Software. This port
is not affiliated with or endorsed by any of them.

## AI use

This port was made with heavy use of AI. Claude, Anthropic's AI coding
assistant, wrote most of the Vita-specific code (the platform layer,
rendering, controls, prompts, menus and loading changes), the build scripts
and this README, working from Shay's requests and bug reports. Shay directed
the work, reviewed and merged every change, and tested the builds on real
Vita hardware. The engine itself is EDuke32 and the game content is the
DNA4PC mod; neither was written by AI. The full history is in this
repository's commits.

## Licence

The engine is EDuke32: its game code is under the GNU GPL version 2
([`LICENSE`](LICENSE)) and the Build engine core is under Ken Silverman's
BUILD licence ([`package/common/buildlic.txt`](package/common/buildlic.txt)).
See [`NOTICE.md`](NOTICE.md) for the details. The VPK includes these licence
texts in its `LICENSE` folder, and the full source for every release is this
repository at the matching tag.
