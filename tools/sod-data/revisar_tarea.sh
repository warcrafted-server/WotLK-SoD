#!/usr/bin/env bash
# Revisión estándar del trabajo de un ejecutor sobre las runas de una clase.
# Uso: tools/sod-data/revisar_tarea.sh <clase> <familia WotLK> [id de ejecución de AgentRelay]
# No acepta ni hace commit: solo informa. Sale con error si el ejecutor se ha saltado las restricciones.
set -uo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT"
CLS=$1; FAM=$2; RUN=${3:-}
FLAGS=$HOME/Repos/acore-test/build/modules/CMakeFiles/modules.dir/flags.make
fallo=0

if [ -n "$RUN" ]; then
    agentrelay show "$RUN" 2>&1 | sed -n '/Informe del ejecutor/,/## Archivos/p' | head -40
fi

echo "== Restricciones"
base=$(git log -1 --format=%h)
[ "$(git log origin/main..HEAD --oneline | wc -l)" -ge 0 ] || true
for d in datos/parche-cliente/*/; do
    [ -e "$d/LISTO" ] && [ ! -e "$d/PUBLICADO" ] && { echo "LISTO sin PUBLICADO en $d (¿lo ha creado el ejecutor?)"; fallo=1; }
done
git status --short | grep -E "CHANGELOG|ESTADO|\.agents/|AGENTS|sod_content_spell_dbc|datos/" && { echo "Ha tocado archivos prohibidos (arriba)"; fallo=1; }
echo "último commit: $base (debe ser el del orquestador)"

echo "== Revisor de runas"
python3 tools/sod-data/revisar_runas.py "$CLS" "$FAM"

echo "== Regeneración del SQL de hechizos"
tools/sod-data/regenerar_sql_hechizos.sh 2>&1 | grep -iE "error|Traceback|wrote SQL|KeyError|NameError"

echo "== Sintaxis con los flags reales"
cd "$(dirname "$FLAGS")"
D=$(sed -n 's/^CXX_DEFINES = //p' flags.make); I=$(sed -n 's/^CXX_INCLUDES = //p' flags.make); X=$(sed -n 's/^CXX_FLAGS = //p' flags.make)
malos=0
for f in "$ROOT"/server/mod-sod-content/src/"$CLS"/*.cpp "$ROOT"/server/mod-sod-content/src/sod_content_loader.cpp; do
    [ -e "$f" ] || continue
    out=$(eval clang++ $D $I $X -fsyntax-only "$f" 2>&1 | grep "error:" | head -3)
    [ -n "$out" ] && { echo "$(basename "$f"): $out"; malos=1; }
done
[ $malos = 0 ] && echo "sintaxis OK"
sql=$("$ROOT"/tools/sod-data/validar_sql.sh 2>&1 | tail -6); echo "== Validación real del SQL (MySQL privada)"; echo "$sql"
echo "$sql" | grep -q FALLO && fallo=1
exit $((fallo + malos))
