#!/bin/sh
# Builds eduke32 for PS Vita and packages it as a VPK. Needs VITASDK set.
set -e

: "${VITASDK:?Please set VITASDK}"
export PATH="$VITASDK/bin:$PATH"

TITLE_ID=DNAV00001
TITLE="Duke Nukem Advance"
VERSION=00.01

cd "$(dirname "$0")/../.."

make PLATFORM=PSP2 LTO=0 -j"$(nproc)" eduke32.elf

out=build/vita
rm -rf "$out"
mkdir -p "$out"

vita-elf-create eduke32.elf "$out/eduke32.velf"
vita-make-fself -s -c "$out/eduke32.velf" "$out/eboot.bin"
vita-mksfoex -s TITLE_ID="$TITLE_ID" -s APP_VER="$VERSION" -d ATTRIBUTE2=12 "$TITLE" "$out/param.sfo"
vita-pack-vpk -s "$out/param.sfo" -b "$out/eboot.bin" \
    -a platform/PSVita/sce_sys/icon0.png=sce_sys/icon0.png \
    -a platform/PSVita/sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
    -a platform/PSVita/sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
    -a platform/PSVita/sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
    "$out/dna-vita.vpk"

echo "Built $out/dna-vita.vpk"
