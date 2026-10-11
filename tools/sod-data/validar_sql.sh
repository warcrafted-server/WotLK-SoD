#!/usr/bin/env bash
# Aplica el SQL de world de nuestros módulos sobre una instancia MySQL privada y desechable (datadir temporal,
# solo socket, sin red) con el esquema base y las actualizaciones de acore-test, en el mismo orden que el
# actualizador del worldserver (por nombre de archivo) y dos veces (el actualizador reaplica lo que cambia).
# No toca ninguna base del servidor. Uso: tools/sod-data/validar_sql.sh   (tarda ~2 min). Sale con 1 si algo falla.
set -uo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
ACORE_TEST=${ACORE_TEST:-$HOME/Repos/acore-test}
T=$(mktemp -d)
trap 'mysqladmin --no-defaults -uroot -S "$T/s.sock" shutdown >/dev/null 2>&1; sleep 2; rm -rf "$T"' EXIT
/usr/sbin/mysqld --no-defaults --initialize-insecure --datadir="$T/data" >/dev/null 2>&1
/usr/sbin/mysqld --no-defaults --datadir="$T/data" --socket="$T/s.sock" --skip-networking --mysqlx=OFF \
    --pid-file="$T/p.pid" >"$T/log" 2>&1 &
for _ in $(seq 40); do mysqladmin --no-defaults -uroot -S "$T/s.sock" ping >/dev/null 2>&1 && break; sleep 1; done
M="mysql --no-defaults -uroot -S $T/s.sock"
$M -e "create database w"
for f in "$ACORE_TEST"/data/sql/base/db_world/*.sql; do $M w <"$f" 2>/dev/null; done
for f in $(ls "$ACORE_TEST"/data/sql/updates/db_world/*.sql | sort); do $M w --force <"$f" >/dev/null 2>&1; done
mapfile -t files < <(find "$ROOT"/server/mod-rune-engraving/data/sql/db-world "$ROOT"/server/mod-sod-content/data/sql/db-world \
    -name '*.sql' | awk -F/ '{print $NF" "$0}' | sort | cut -d' ' -f2-)
fallo=0
for pasada in 1 2; do
    for f in "${files[@]}"; do
        out=$($M w <"$f" 2>&1) || { echo "FALLO (pasada $pasada) $(basename "$f"): $out"; fallo=1; }
    done
done
[ $fallo = 0 ] && echo "SQL de world: ${#files[@]} archivos aplicados dos veces sin errores"
exit $fallo
