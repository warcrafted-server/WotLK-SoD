#!/usr/bin/env bash
# Cierra una tarea de runas ya revisada: acepta la ejecución, anota el CHANGELOG, marca el paso en el plan,
# hace el commit y, si se indica, lanza la tarea siguiente en segundo plano (registro en /tmp).
# Uso: tools/sod-data/cerrar_tarea.sh <clase> <nombre en español> <directorio del plan> <N> <id de ejecución> [nota] [siguiente.json]
# El paso N es el de .agents/plans/<plan>/tareas/<clase>N.json.
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT"
CLS=$1; ES=$2; PLAN=$3; N=$4; RUN=$5; NOTA=${6:-}; SIG=${7:-}
TAREA=.agents/plans/$PLAN/tareas/$CLS$N.json
python3 - "$CLS" "$ES" "$PLAN" "$N" "$NOTA" "$TAREA" <<'PY'
import json, re, sys
cls, es, plan, n, nota, tarea = sys.argv[1:7]
obj = json.load(open(tarea))['objective']
runas = obj.split(': ', 1)[1].rstrip('.')
nombres = re.sub(r' \(\d+\)', '', runas)
ids = re.findall(r'\((\d{7})\)', runas)
cl = open('CHANGELOG.md').read()
import datetime
hoy = datetime.date.today().isoformat()
cl = open('CHANGELOG.md').read()
marca = f'## {hoy}\n\n'
if marca not in cl:
    cl = cl.replace('\n## ', f'\n## {hoy}\n\n\n## ', 1)
linea = f"- {es.capitalize()}: runas {', '.join(re.findall(r'(.+?) \((\d{7})\)(?:, |$)', runas) and [f'{a} `{b}`' for a, b in re.findall(r'(?:^|, )(.+?) \((\d{7})\)', runas)])} (tanda {n} de `.agents/plans/{plan}/`). {nota + ' ' if nota else ''}Sin compilar ni probar.\n"
assert marca in cl
open('CHANGELOG.md', 'w').write(cl.replace(marca, marca + linea, 1))
p = f'.agents/plans/{plan}/{plan}.PLAN.md'
t = open(p).read()
t2 = re.sub(rf'^(\| {n} \|.*?)\| pendiente \|$', r'\1| hecho |', t, count=1, flags=re.M)
assert t2 != t, 'no se encontró el paso en el plan'
open(p, 'w').write(t2)
open('/tmp/cerrar_msg', 'w').write(f"Añade {len(ids)} runas de {es} ({nombres})")
PY
agentrelay review "$RUN" --decision accept --force 2>&1 | tail -1
git add -A server docs TODO.md CHANGELOG.md .agents tools
git commit -qm "$(cat /tmp/cerrar_msg)"
git log --oneline -1
git status --short
if [ -n "$SIG" ]; then
    LOG=${SCRATCH:-/tmp}/$(basename "$SIG" .json).log
    echo "lanzando $SIG"
    agentrelay run "$SIG" > "$LOG" 2>&1
fi
