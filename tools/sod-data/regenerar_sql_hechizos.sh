#!/usr/bin/env bash
# Regenera server/mod-sod-content/data/sql/db-world/base/sod_content_spell_dbc.sql con build_patch.py --dry-run.
# Monta una raíz de servidor temporal con enlaces a nuestros módulos y a las tablas base de acore-test (solo
# lectura), para no tocar acore-test/modules. No escribe ningún MPQ.
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
ACORE_TEST=${ACORE_TEST:-$HOME/Repos/acore-test}
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$TMP/modules" "$TMP/data/sql/base"
ln -s "$ROOT/server/mod-sod-content" "$TMP/modules/mod-sod-content"
ln -s "$ROOT/server/mod-rune-engraving" "$TMP/modules/mod-rune-engraving"
ln -s "$ACORE_TEST/data/sql/base/db_world" "$TMP/data/sql/base/db_world"
python3 "$ROOT/tools/sod-client/build_patch.py" --server "$TMP" --client "$ROOT/datos/cliente-sod" \
    --locale esES --dry-run
