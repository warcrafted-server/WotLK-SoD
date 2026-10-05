#!/usr/bin/env bash
# Reproduce upstream/ con los commits exactos con los que se auditó y se trabaja.
# upstream/ no se versiona, así que en otra máquina (p. ej. el Linux de compilación) se
# reconstruye con este script. Uso, desde la raíz del repo:  bash tools/clonar-upstream.sh
set -euo pipefail
cd "$(dirname "$0")/.."

clonar() {  # clonar <directorio> <url> <commit>
  local dir="upstream/$1" url="$2" sha="$3"
  if [ -d "$dir/.git" ]; then echo "ya existe: $dir"; return; fi
  mkdir -p "$dir" && git -C "$dir" init -q
  git -C "$dir" remote add origin "$url"
  git -C "$dir" fetch -q --depth 1 origin "$sha"
  git -C "$dir" checkout -q FETCH_HEAD
  echo "ok: $dir @ ${sha:0:7}"
}

clonar azerothcore/azerothcore-wotlk        https://github.com/azerothcore/azerothcore-wotlk.git   1b4717c9310a1e686064e63ebed1e80f1c61ced7
clonar azerothcore/mod-sod/mod-rune-engraving https://github.com/mod-sod/mod-rune-engraving.git   f436ef64fcd656683a00ae9c913b6ba7ae910688
clonar azerothcore/mod-sod/mod-sod-mage     https://github.com/mod-sod/mod-sod-mage.git           7fd10e20d4277bcc6ec5f6934b2ed1d2033e7335
clonar azerothcore/mod-sod/mod-sod-world    https://github.com/mod-sod/mod-sod-world.git          6530bb56887c8749d5d7f615e2da2167d221c12a
clonar azerothcore/mod-sod/sod-client       https://github.com/mod-sod/sod-client.git             204627b008b3299948b63876fa949588d9522089
clonar azerothcore/mod-sod/sod-class-templates https://github.com/mod-sod/sod-class-templates.git 3727ea6f9658e8552bd13a139b23e4c48530aeb7
clonar azerothcore/mod-sod/sod-installer    https://github.com/mod-sod/sod-installer.git          7d5d23ed5443d52fe5b2647b69798243971746b7
