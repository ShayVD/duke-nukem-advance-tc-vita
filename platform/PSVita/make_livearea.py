#!/usr/bin/env python3
"""Build the Vita LiveArea art (icon0, bg, startup) from the mod's own title tiles.

Usage: make_livearea.py <path to DNA4PC mod folder> [output sce_sys folder]

Needs Pillow. The gate image and icon are composed from the title screen tiles
the mod draws in scripts/screens.con (TITLE_BACKGROUND, TITLE_DUKE, TITLE_NUKEM,
TITLE_ADVANCE), and the background from the Egypt and Sydney skies. All three
are saved as 8-bit indexed PNGs, which the Vita requires for sce_sys images.
"""

import os
import sys

from PIL import Image, ImageEnhance

TITLE_BACKGROUND = 5740
TITLE_ADVANCE = 5741
TITLE_DUKE = 5754
TITLE_NUKEM = 5755
SKY_EGYPT = 3699
SKY_SYDNEY = 3914

# Final title positions from scripts/dnadef.con, in 320x200 screen space.
# rotatesprite draws each tile centred on its position.
TITLE_DUKE_POS = (78, 70)
TITLE_NUKEM_POS = (224, 70)
TITLE_ADVANCE_POS = (160, 127)
TITLE_SCALE = 81935 / 65536
LOGO_SCALE = 95535 / 65536


def tile(mod, num):
    tiles = os.path.join(mod, "tiles")
    for name in os.listdir(tiles):
        if os.path.splitext(name)[0] == str(num):
            return Image.open(os.path.join(tiles, name)).convert("RGBA")
    raise FileNotFoundError("tile %d not found in %s" % (num, tiles))


def upscale(im, factor):
    """Pixel-double first so the GBA art stays crisp, then smooth to size."""
    w, h = im.size
    k = max(1, int(factor))
    im = im.resize((w * k, h * k), Image.NEAREST)
    return im.resize((round(w * factor), round(h * factor)), Image.LANCZOS)


def paste_centred(canvas, im, centre):
    canvas.alpha_composite(im, (round(centre[0] - im.width / 2), round(centre[1] - im.height / 2)))


def title_screen(mod, scale):
    """The mod's final title screen, rendered at 320x200 * scale."""
    canvas = Image.new("RGBA", (round(320 * scale), round(200 * scale)), (0, 0, 0, 255))
    paste_centred(canvas, upscale(tile(mod, TITLE_BACKGROUND), LOGO_SCALE * scale), (160 * scale, 100 * scale))
    for num, pos in ((TITLE_DUKE, TITLE_DUKE_POS), (TITLE_NUKEM, TITLE_NUKEM_POS), (TITLE_ADVANCE, TITLE_ADVANCE_POS)):
        paste_centred(canvas, upscale(tile(mod, num), TITLE_SCALE * scale), (pos[0] * scale, pos[1] * scale))
    return canvas


def crop_centre(im, size, yshift=0):
    x = (im.width - size[0]) // 2
    y = (im.height - size[1]) // 2 + yshift
    return im.crop((x, y, x + size[0], y + size[1]))


def cover(im, size):
    factor = max(size[0] / im.width, size[1] / im.height)
    return crop_centre(upscale(im, factor), size)


def make_startup(mod):
    # 280x158 gate image: the title screen, trimmed top and bottom to fit.
    return crop_centre(title_screen(mod, 280 / 320), (280, 158), yshift=4)


def make_icon(mod):
    # 128x128: radiation emblem with the DUKE NUKEM / ADVANCE logo stacked on it.
    bg = tile(mod, TITLE_BACKGROUND)
    bg = bg.crop((40, 0, 200, 160))
    icon = upscale(bg, 128 / 160)
    icon = ImageEnhance.Brightness(icon).enhance(0.55)
    duke = upscale(tile(mod, TITLE_DUKE), 0.92)
    nukem = upscale(tile(mod, TITLE_NUKEM), 0.92)
    advance = tile(mod, TITLE_ADVANCE)
    advance = advance.crop(advance.getbbox())
    advance = upscale(advance, 122 / advance.width)
    paste_centred(icon, duke, (64, 26))
    paste_centred(icon, nukem, (64, 64))
    paste_centred(icon, advance, (64, 104))
    return icon


def make_bg(mod):
    # 840x500: Egypt and Sydney skies from the campaign joined into one
    # panorama, with a soft blend where they meet. The gate in the middle
    # carries the title, so the background stays free of text.
    egypt = tile(mod, SKY_EGYPT)
    sydney = tile(mod, SKY_SYDNEY)
    blend = 96
    pano = Image.new("RGBA", (egypt.width + sydney.width - blend, egypt.height), (0, 0, 0, 255))
    pano.alpha_composite(egypt, (0, 0))
    mask = Image.linear_gradient("L").rotate(90).resize((blend, sydney.height))
    right = sydney.copy()
    edge = right.crop((0, 0, blend, right.height))
    edge.putalpha(mask)
    right.paste(edge, (0, 0))
    pano.alpha_composite(right, (egypt.width - blend, 0))
    bg = cover(pano, (840, 500))
    return ImageEnhance.Brightness(bg).enhance(0.85)


def save_indexed(im, path):
    im.convert("RGB").quantize(colors=256, method=Image.MEDIANCUT, dither=Image.FLOYDSTEINBERG).save(path, optimize=True)
    print("wrote", path)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    mod = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else os.path.join(os.path.dirname(os.path.abspath(__file__)), "sce_sys")
    save_indexed(make_icon(mod), os.path.join(out, "icon0.png"))
    save_indexed(make_bg(mod), os.path.join(out, "livearea", "contents", "bg.png"))
    save_indexed(make_startup(mod), os.path.join(out, "livearea", "contents", "startup.png"))


if __name__ == "__main__":
    main()
