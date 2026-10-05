#!/usr/bin/env bash
# Prepara el entorno de trabajo en una maquina nueva (p. ej. el Linux de compilacion).
# Uso, desde la raiz de este repositorio:   bash tools/preparar-entorno.sh
#
#  1. core/      -> NUESTRO fork de AzerothCore (rama Playerbot-SoD), repositorio independiente.
#  2. upstream/  -> proyectos de terceros, solo lectura, con los commits exactos con los que se
#                   trabaja. mod-playerbots se usa tal cual; los mod-sod son referencia de los
#                   forks propios que viven en server/.
#  3. core/modules/ -> enlaces simbolicos a los modulos que se compilan.
# Es idempotente: se puede relanzar sin romper lo que ya existe.
set -euo pipefail
cd "$(dirname "$0")/.."

CORE_URL=https://github.com/warcrafted-server/azerothcore-wotlk.git
CORE_BRANCH=Playerbot-SoD

if [ ! -d core/.git ]; then
  git clone --branch "$CORE_BRANCH" "$CORE_URL" core
fi
git -C core remote get-url playerbots >/dev/null 2>&1 || git -C core remote add playerbots https://github.com/mod-playerbots/azerothcore-wotlk.git
git -C core remote get-url acore      >/dev/null 2>&1 || git -C core remote add acore      https://github.com/azerothcore/azerothcore-wotlk.git
echo "core: $(git -C core rev-parse --abbrev-ref HEAD) @ $(git -C core rev-parse --short HEAD)"

clonar() {  # clonar <directorio> <url> <commit>
  local dir="upstream/$1" url="$2" sha="$3"
  if [ -d "$dir/.git" ]; then echo "ya existe: $dir"; return; fi
  mkdir -p "$dir" && git -C "$dir" init -q
  git -C "$dir" remote add origin "$url"
  git -C "$dir" fetch -q --depth 1 origin "$sha"
  git -C "$dir" checkout -q FETCH_HEAD
  echo "ok: $dir @ ${sha:0:7}"
}

clonar mod-playerbots/mod-playerbots                https://github.com/mod-playerbots/mod-playerbots.git           037c01418b5d01506917a3db9b44fd56ac5f965c
clonar azerothcore/mod-sod/mod-rune-engraving       https://github.com/mod-sod/mod-rune-engraving.git              f436ef64fcd656683a00ae9c913b6ba7ae910688
clonar azerothcore/mod-sod/mod-sod-mage             https://github.com/mod-sod/mod-sod-mage.git                    7fd10e20d4277bcc6ec5f6934b2ed1d2033e7335
clonar azerothcore/mod-sod/mod-sod-world            https://github.com/mod-sod/mod-sod-world.git                   6530bb56887c8749d5d7f615e2da2167d221c12a
clonar azerothcore/mod-sod/sod-client               https://github.com/mod-sod/sod-client.git                      204627b008b3299948b63876fa949588d9522089
clonar azerothcore/mod-sod/sod-class-templates      https://github.com/mod-sod/sod-class-templates.git             3727ea6f9658e8552bd13a139b23e4c48530aeb7
clonar azerothcore/mod-sod/sod-installer            https://github.com/mod-sod/sod-installer.git                   7d5d23ed5443d52fe5b2647b69798243971746b7
clonar azerothcore/mod-sod/RuneEngraver            https://github.com/mod-sod/RuneEngraver.git                    500f57e20d21309f89d7516da4eb22061f4e100a

# Modulos que se compilan dentro del core (core/modules/ esta ignorado por git en el core).
mkdir -p core/modules
ln -sfn "$PWD/upstream/mod-playerbots/mod-playerbots" core/modules/mod-playerbots
ln -sfn "$PWD/server/mod-rune-engraving"              core/modules/mod-rune-engraving
ln -sfn "$PWD/server/mod-sod-content"                 core/modules/mod-sod-content
echo "modulos enlazados en core/modules/:"; ls -l core/modules | grep -- '->' | awk '{print "  " $9 " -> " $11}'
