#!/bin/sh
# Makes an all-in-one VPK by adding your own DUKE3D.GRP and DNA4PC folder to a built dna-vita.vpk.
# The data is installed read-only with the app; settings and saves still go to ux0:data/dna/.
# Only needs sh and zip (both come with macOS and most Linux systems), not VitaSDK.
#
# Usage: bundle_data.sh <dna-vita.vpk> <data folder> [output.vpk]
#   <data folder> holds DUKE3D.GRP and the DNA4PC folder, laid out like ux0:data/dna/.
#
# The result contains commercial game data: keep it for yourself, don't share it.
set -e

if [ $# -lt 2 ]; then
    echo "Usage: $0 <dna-vita.vpk> <data folder> [output.vpk]" >&2
    exit 1
fi

vpk=$1
data=$2
out=${3:-$(dirname "$vpk")/dna-vita-full.vpk}

[ -f "$vpk" ] || { echo "No VPK at $vpk" >&2; exit 1; }
command -v zip >/dev/null || { echo "zip is not installed" >&2; exit 1; }

grp=$(find "$data" -maxdepth 1 -type f -iname duke3d.grp | head -n 1)
mod=$(find "$data" -maxdepth 1 -type d -iname dna4pc | head -n 1)

[ -n "$grp" ] || { echo "No DUKE3D.GRP in $data" >&2; exit 1; }
[ -n "$mod" ] || { echo "No DNA4PC folder in $data" >&2; exit 1; }
[ -f "$mod/EDUKE.CON" ] || [ -f "$mod/eduke.con" ] ||
    echo "Warning: $mod has no EDUKE.CON; is it the right DNA4PC folder?" >&2

stage=$(mktemp -d)
trap 'rm -rf "$stage"' EXIT

mkdir "$stage/data"
cp "$grp" "$stage/data/DUKE3D.GRP"
cp -R "$mod" "$stage/data/DNA4PC"

case $out in
    /*) ;;
    *) out=$(pwd)/$out ;;
esac

cp "$vpk" "$out"
(cd "$stage" && zip -q -r "$out" data -x '*.DS_Store' -x '*/._*')

echo "Built $out"
