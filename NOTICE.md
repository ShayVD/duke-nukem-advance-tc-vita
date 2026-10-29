# Licences and notices

Duke Nukem Advance for PS Vita is a port of EDuke32. It is made of code under
several licences, all kept as they came from upstream:

| Code | Licence | Text |
| --- | --- | --- |
| Game code (`source/duke3d`), audio (`source/audiolib`), MACT (`source/mact`), and the Vita port's own changes | GNU General Public License, version 2 | [`LICENSE`](LICENSE) (also `package/common/gpl-2.0.txt`) |
| Build engine (`source/build`) | Ken Silverman's BUILD source code licence | [`package/common/buildlic.txt`](package/common/buildlic.txt) |
| KPLIB (`source/build/src/kplib.cpp`) | Ken Silverman's licence in the file's header | the file itself |
| libxmp-lite (`source/libxmp-lite`) | MIT | the file headers and `source/libxmp-lite/README` |
| SDL2 and the VitaSDK libraries the VPK links with | their own licences (zlib, MIT and others) | see each project |

Build engine notice, as its licence requires:

    // "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
    // Ken Silverman's official web site: "http://www.advsys.net/ken"
    // See the included license file "BUILDLIC.TXT" for license info.

The BUILD licence allows distribution of derivative works only over the
internet and only free of charge. This port is and will stay free.

EDuke32 is copyright the EDuke32 developers and contributors (voidpoint.io),
JonoF (Jonathon Fowler) and others named in the file headers. Duke Nukem 3D's
game code is copyright 3D Realms and was released under the GPL in 2003.

The VPK also carries `LICENSE/gpl-2.0.txt`, `LICENSE/BUILDLIC.TXT` and
`LICENSE/NOTICE.md`, and the full source for every release is this
repository at the matching tag.

## Not included

This repository and the VPK contain no Duke Nukem 3D game data and no files
from the Duke Nukem Advance TC. Players supply `DUKE3D.GRP` from their own
copy of the game and download the TC from its authors.

Duke Nukem is a trademark of Gearbox Software. Duke Nukem Advance was made by
Torus Games. This project is not affiliated with or endorsed by Gearbox,
3D Realms, Torus Games, Take-Two Interactive, Sony, or the TC's authors.
