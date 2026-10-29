# Duke Nukem Advance for PS Vita

A PS Vita port of [EDuke32](https://www.eduke32.com/) that runs
[Duke Nukem Advance TC (DNA4PC)](https://www.moddb.com/mods/duke-nukem-advance-tc),
the total conversion that brings the whole Game Boy Advance campaign of
Duke Nukem Advance to the Duke Nukem 3D engine.

This repository only contains the engine. You supply the game data yourself:
the Duke Nukem 3D data file and the DNA4PC mod.

## What you need

- A PS Vita or PS TV with homebrew enabled (HENkaku/h-encore/Ensō) and
  [VitaShell](https://github.com/TheOfficialFloW/VitaShell).
- `dna-vita.vpk` (see [Getting the VPK](#getting-the-vpk)).
- `DUKE3D.GRP` from Duke Nukem 3D version 1.4/1.5 (Atomic Edition), about
  43 MB. It comes with the GOG release of Atomic Edition and the Steam/GOG
  Megaton Edition (in its `gameroot` folder). The shareware `DUKE3D.GRP` will
  not work, and the 20th Anniversary World Tour data has not been tested.
- DNA4PC 1.0, from [ModDB](https://www.moddb.com/mods/duke-nukem-advance-tc)
  or [GitHub](https://github.com/branung/DNA4PC). You only need its `DNA4PC`
  folder (about 33 MB).

## Installing

1. **Install the VPK.** Copy `dna-vita.vpk` to the Vita (for example to
   `ux0:VPK/`), open it in VitaShell and install it. A "Duke Nukem Advance"
   bubble appears on the home screen.
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

   Copy the `DNA4PC` folder itself, not its parent. If you downloaded the full
   DNA4PC package, leave out its `eduke32.exe`, `mapster32.exe` and
   `eduke32.cfg`: they are for Windows, and the PC `eduke32.cfg` sets a
   1920x1080 screen and keyboard controls that the Vita can't use.

   To copy files you can use VitaShell's FTP server (press Select) or its USB
   mode. File names are not case sensitive on the memory card.
4. **Launch the bubble.** The game skips the launcher and boots straight into
   DNA4PC. The first start takes about 13 seconds and loading a level about 7
   seconds. If the `DNA4PC` folder is missing, you get plain Duke Nukem 3D
   instead, which is a quick way to tell the folder is in the wrong place.

## Controls

| Vita | Action |
| --- | --- |
| Left stick | Move and strafe |
| Right stick | Turn and look up/down |
| R | Fire |
| L | Jump |
| Rear touchpad, right half (or the front screen's top-right corner) | Alt fire (R2) |
| Rear touchpad, left half (or the front screen's top-left corner) | Crouch (L2) |
| Circle | Toggle crouch |
| Cross | Open / use |
| Square | Use inventory item |
| Triangle | Quick kick |
| D-pad up / down | Previous / next weapon |
| D-pad left / right | Previous / next inventory item |
| Select | DNA's mod menu |
| Tap the front screen | Map |
| Start | Main menu |

Auto run is on by default. All of these can be changed in the in-game
controller settings.

## Your files on the Vita

Everything the game writes lives in `ux0:data/dna/`: `eduke32.cfg` for your
settings and controls, saved games, and `eduke32.log`, which is the first thing
to check (or attach to a bug report) if something goes wrong. Deleting
`eduke32.cfg` resets settings and controls to the Vita defaults.

## Advanced: launch options

To pass your own EDuke32 command-line options, create `ux0:data/dna/args.txt`
with the options separated by spaces or new lines. When this file exists it
replaces the defaults, so include them if you still want them. The defaults
are:

```
-usecwd -nosetup -game_dir DNA4PC
```

## Getting the VPK

Download `dna-vita.vpk` from the latest release on this repository's Releases
page. Until there is a release, open the latest successful **Vita build** run
under the repository's Actions tab and download the `dna-vita` artifact (you
need to be signed in to GitHub). It's a zip that holds `dna-vita.vpk` and
`eduke32.elf`, which is only used to read crash dumps.

## Building it yourself

Install [VitaSDK](https://vitasdk.org/) with its SDL2 package (`vdpm SDL2`),
set `VITASDK`, then run:

```sh
./platform/PSVita/build.sh
```

The VPK is written to `build/vita/dna-vita.vpk`. If the build fails, the full
log is in `build-vita.log`.

## Credits

- [EDuke32](https://www.eduke32.com/) by the EDuke32 team (voidpoint).
- DNA4PC by branung, oasiz, Voxelvoid and contributors; see the mod's readme
  for the full credits.
- Duke Nukem Advance by Torus Games; Duke Nukem 3D by 3D Realms.
