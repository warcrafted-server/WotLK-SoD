#!/usr/bin/env bash
# Genera y confirma la adquisición (objetos-runa, venta en el Grabador y botín real) de una clase ya completa.
# Uso: tools/sod-data/cerrar_adquisicion.sh <clase> <Clase en español, como en obtencion.md> <directorio del plan> [siguiente.json]
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT"
CLS=$1; ES=$2; PLAN=$3; SIG=${4:-}
[ -z "$(git status --short)" ] || { echo "El árbol no está limpio"; exit 1; }
F=server/mod-sod-content/data/sql/db-world/base/sod_${CLS}_acquisition.sql
[ ! -e "$F" ] || { echo "$F ya existe: no lo sobrescribo"; exit 1; }
python3 tools/sod-data/gen_rune_acquisition.py --class "$CLS"
python3 tools/sod-data/actualizar_obtencion.py "$CLS" "$ES"
python3 - "$CLS" "$ES" "$PLAN" <<'PY'
import collections, glob, json, re, sys
cls, es, plan = sys.argv[1:4]
c = collections.defaultdict(list)
for p in glob.glob('server/mod-sod-content/data/sql/db-world/base/sod_*_acquisition.sql'):
    s = open(p).read()
    i = s.index('REPLACE INTO `item_template`'); j = s.index(';', i)
    for e in re.findall(r"\n    \((\d{6}), 15, 0, ", s[i:j]):
        c[e].append(p)
dup = {k: v for k, v in c.items() if len(v) > 1}
assert not dup, f'objetos duplicados entre clases: {dup}'
d = json.load(open('server/mod-sod-content/tools/client_items.json'))
cc = collections.Counter(x['id'] for x in d)
assert not [k for k, v in cc.items() if v > 1], 'client_items.json con ids duplicados'
s = open(f'server/mod-sod-content/data/sql/db-world/base/sod_{cls}_acquisition.sql').read()
n_obj = len(re.findall(r"\n    \((\d{6}), 15, 0, ", s[s.index('REPLACE INTO `item_template`'):s.index(';', s.index('REPLACE INTO `item_template`'))]))
m = re.search(r"rune_item_unlock`[^']*VALUES ([^']+)", s)
n_run = len({r for _, r in re.findall(r'\((\d+), (\d+)\)', m.group(1))})
botin = sorted({int(x) for x in re.findall(r"\((\d+), \d+, 0, [\d.]+, 0, 1, 0, 1, 1, 'mod-sod-", s)})
cl = open('CHANGELOG.md').read(); marca = '## 2026-10-10\n\n'
linea = (f"- {es}: adquisición de {n_run} runas generada con `gen_rune_acquisition.py --class {cls}` ({n_obj} objetos con su id real de SoD, "
         f"venta en el Grabador y botín real de WotLK solo para esta clase en {len(botin)} criaturas). Sin aplicar ni probar.\n")
open('CHANGELOG.md', 'w').write(cl.replace(marca, marca + linea, 1))
pr = open('docs/PRUEBAS.md').read()
i = pr.index(f'### {es}'); j = pr.find('\n### ', i + 5)
sec = pr[i:j if j > 0 else len(pr)].rstrip('\n') + f"\n- [ ] Adquisición del {es.lower()}: las {n_run} runas se compran como objeto en `.rune summon` › «Comprar runas» (1 oro) y se aprenden al usarlo. Botín real solo para esta clase en {len(botin)} criaturas (ver `docs/runas/obtencion.md`).\n"
pr = pr[:i] + sec + (pr[j:] if j > 0 else '')
open('docs/PRUEBAS.md', 'w').write(pr)
p = f'.agents/plans/{plan}/{plan}.PLAN.md'
t = open(p).read()
t2 = re.sub(r'^(\| \d+ \| Adquisición.*?)\| pendiente \|$', r'\1| hecho (generada) |', t, count=1, flags=re.M)
open(p, 'w').write(t2)
print(f'{n_obj} objetos, {n_run} runas, {len(botin)} criaturas con botín')
PY
git add -A server docs CHANGELOG.md .agents tools
git commit -qm "Añade la adquisición de las runas de $ES"
git log --oneline -1
if [ -n "$SIG" ]; then
    LOG=/tmp/claude-1000/-home-stark-Repos-acore-sod/adc2de10-e3ee-409a-9ed7-87ea61b25db7/scratchpad/$(basename "$SIG" .json).log
    echo "lanzando $SIG"
    agentrelay run "$SIG" > "$LOG" 2>&1
fi
