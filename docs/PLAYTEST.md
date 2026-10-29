# Playtest checklist

A full playthrough of the Duke Nukem Advance campaign on real hardware, for the
1.0 release. Tick each box, and write the build (commit or VPK date), the
device (Vita 1000/2000/PS TV) and any problem next to it. Attach
`ux0:data/dna/eduke32.log` to any bug report.

Test with **Half** resolution and VSync on (the defaults) unless a line says
otherwise. Do at least one chapter at **Full** resolution.

Build: ________  Device / firmware: ________  Tester: ________

## Before you start

- [ ] Fresh install: delete `ux0:data/dna/eduke32-vita.cfg`, `settings.cfg` and saves, install the VPK, launch.
- [ ] No `DUKE3D.GRP`: the game shows the "DUKE3D.GRP is missing" message and closes cleanly, and `error.txt` has the same text.
- [ ] Shareware `DUKE3D.GRP`: the "shareware version" message appears.
- [ ] No `DNA4PC` folder: the "DNA4PC is missing" message appears (it must not start plain Duke 3D).
- [ ] `DNA4PC/DNA4PC/` nested: the "one level too deep" message appears.
- [ ] With everything in place: boots to the DNA title in about 13 s, no launcher.
- [ ] Megaton Edition `DUKE3D.GRP` also boots (if available).
- [ ] New campaign screens: style, script region, voicing and skill all show Vita button names (`[CROSS]`, `[SELECT]`).
- [ ] LiveArea: icon, start gate and background show correctly.

## Every level

For each level, check:

- **Load**: the level loads in about 7 s with a black screen (no briefing flash), music starts.
- **Play**: no crash, freeze, missing textures, sound dropouts or long hitches. Note the lowest FPS seen (turn on Show FPS).
- **Finish**: all objectives, scripted events, cutscenes and bosses work, the exit works and the level-complete screen shows.
- **Save/load**: save mid-level, quit to the title, load: you are back in the same place with the same health, weapons and objectives.

| Level | Map | Load | Play | Finish | Save/load | Lowest FPS | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1A | MAP01 | [ ] | [ ] | [ ] | [ ] | | |
| 1B | MAP02 | [ ] | [ ] | [ ] | [ ] | | |
| 1C | MAP03 | [ ] | [ ] | [ ] | [ ] | | |
| 2A | MAP04 | [ ] | [ ] | [ ] | [ ] | | |
| 2B | MAP05 | [ ] | [ ] | [ ] | [ ] | | |
| 2C | MAP06 | [ ] | [ ] | [ ] | [ ] | | |
| 2D | MAP07 | [ ] | [ ] | [ ] | [ ] | | |
| 3A | MAP08 | [ ] | [ ] | [ ] | [ ] | | |
| 3B | MAP09 | [ ] | [ ] | [ ] | [ ] | | |
| 3C | MAP10 | [ ] | [ ] | [ ] | [ ] | | |
| 3D | MAP11 | [ ] | [ ] | [ ] | [ ] | | |
| 4A | MAP12 | [ ] | [ ] | [ ] | [ ] | | |
| 4B | MAP13 | [ ] | [ ] | [ ] | [ ] | | |
| 4C | MAP14 | [ ] | [ ] | [ ] | [ ] | | |
| 4D | MAP15 | [ ] | [ ] | [ ] | [ ] | | |
| 4E | MAP16 | [ ] | [ ] | [ ] | [ ] | | |
| 4F | MAP17 | [ ] | [ ] | [ ] | [ ] | | |
| 4G | MAP18 | [ ] | [ ] | [ ] | [ ] | | |
| 4H | MAP19 | [ ] | [ ] | [ ] | [ ] | | |

Also check:

- [ ] Each boss fight (the Controller, the Spider Lord and the Alien Lord, among others) from start to finish, and dying and restarting during it.
- [ ] Every cutscene, with each voicing option (none, oneliners, fully voiced) at least once.
- [ ] Both styles (PC Enhanced, GBA Original) for at least one level each.
- [ ] Chapter select from the main menu, if unlocked.
- [ ] Ending and credits after 4H, then back to the title without a crash.

## Controls

- [ ] Left stick moves and strafes, right stick turns and looks, with no drift at rest.
- [ ] R fires, L jumps, Circle toggles crouch, Cross opens/uses, Square uses the item, Triangle kicks.
- [ ] D-pad up/down changes weapon, left/right changes inventory item.
- [ ] Rear touchpad right half = alt fire, left half = crouch; the front screen's top corners do the same.
- [ ] A tap elsewhere on the front screen opens the map, and holding the Vita normally doesn't open it by accident.
- [ ] Select opens DNA's mod menu, Start opens the main menu.
- [ ] Death screen says "PRESS CROSS TO RESTART LEVEL" and Cross restarts.
- [ ] Rebinding a button in Controller Setup works and the prompts follow it; "Reset to defaults" restores the Vita layout.
- [ ] Gyro aiming on: turning and tilting aim correctly, sensitivity slider works, no drift when the Vita is still. Off by default.

## Saving, settings and system

- [ ] Save into a new slot and overwrite an old slot; both load.
- [ ] Checkpoint autosaves are created and load.
- [ ] Saves and settings survive quitting, rebooting the Vita, and reinstalling or updating the VPK.
- [ ] Resolution Half/Full, Show FPS and VSync change at once and are remembered after a restart.
- [ ] PS button mid-level: the game pauses; resuming continues correctly. Same after putting the Vita to sleep and waking it.
- [ ] Quit from the main menu returns to the LiveArea cleanly.
- [ ] Play for at least an hour in one session with no slowdown, crash or audio breakup.
- [ ] Low battery warning and other system notifications don't break the game.

## Performance notes

| Level | Half FPS (typical / lowest) | Full FPS (typical / lowest) | Notes |
| --- | --- | --- | --- |
| | | | |
