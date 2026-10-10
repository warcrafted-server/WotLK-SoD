#!/usr/bin/env python3
"""Reescribe en docs/runas/obtencion.md la columna «Cómo se consigue aquí» de una clase a partir de su SQL de adquisición.

Uso: python3 tools/sod-data/actualizar_obtencion.py <clase> <nombre en español de la columna Clase>
Lee sod_<clase>_acquisition.sql (objetos, desbloqueos y botín) y los nombres de criatura de acore_world (solo lectura).
"""
import re
import subprocess
import sys
from pathlib import Path

R = Path(__file__).resolve().parents[2]


def main():
    cls, clase_es = sys.argv[1], sys.argv[2]
    s = (R / f'server/mod-sod-content/data/sql/db-world/base/sod_{cls}_acquisition.sql').read_text()
    cuerpo = s[s.index('REPLACE INTO `item_template`'):]
    cuerpo = cuerpo[:cuerpo.index(';')]
    nombres = {int(a): b for a, b in re.findall(r"\n    \((\d{6}), 15, 0, '((?:[^']|'')*)'", cuerpo)}
    m = re.search(r"rune_item_unlock`[^']*VALUES ([^']+)", s)
    items = {}  # runa -> [objetos]
    for it, rune in re.findall(r'\((\d+), (\d+)\)', m.group(1)):
        items.setdefault(int(rune), []).append(int(it))
    botin = {}
    for ent, it, ch in re.findall(r"\((\d+), (\d+), 0, ([\d.]+), 0, 1, 0, 1, 1, 'mod-sod-", s):
        botin.setdefault(int(it), []).append((int(ent), ch))
    ents = sorted({e for v in botin.values() for e, _ in v})
    crea = {}
    if ents:
        out = subprocess.run(['mysql', '-N', 'acore_world', '-e',
                              f"select entry,name from creature_template where entry in ({','.join(map(str, ents))})"],
                             capture_output=True, text=True).stdout
        crea = {int(a): b for a, b in (l.split('\t') for l in out.split('\n') if l)}
    ruta = R / 'docs/runas/obtencion.md'
    lineas = ruta.read_text().split('\n')
    cambiadas = 0
    for n, l in enumerate(lineas):
        c = l.split(' | ')
        if len(c) == 7 and re.match(r'\| 70\d{5}$', c[0]) and c[1] == clase_es and int(c[0][2:]) in items:
            partes = []
            for it in items[int(c[0][2:])]:
                nm = nombres.get(it, '?').replace("''", "'")
                t = f'Objeto «{nm}» ({it}): compra al Grabador (1 oro)'
                if it in botin:
                    t += '; botín de ' + ', '.join(f'{crea.get(e, e)} ({e}) {ch} %' for e, ch in botin[it])
                partes.append(t)
            c[5] = '. '.join(partes) + '.'
            lineas[n] = ' | '.join(c)
            cambiadas += 1
    ruta.write_text('\n'.join(lineas))
    print(f'{cambiadas} filas de {clase_es} actualizadas')


if __name__ == '__main__':
    main()
