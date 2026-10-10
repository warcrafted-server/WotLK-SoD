#!/usr/bin/env python3
"""Revisión automática de las runas de una clase antes de aceptar el trabajo de un ejecutor.

Uso: python3 tools/sod-data/revisar_runas.py <clase> <familia> [--sin-mysql]
  <clase>    nombre del módulo: druid, paladin, shaman, warlock...
  <familia>  SpellClassSet de WotLK de la clase (paladín 10, chamán 11, brujo 5, druida 7, mago 3...)

Comprueba, sobre sod_spells_<clase>.py y sod_<clase>_runes.sql:
  - iconos de las runas que no existen en el SpellIcon.dbc del cliente;
  - auras fuera de 0-316 (3.3.5a no tiene más; las de SoD moderno se ignoran en silencio);
  - plantillas inexistentes y clones que heredan la familia de otra clase;
  - claves de 'overrides' que no son columnas de spell_dbc (el generador las descarta sin avisar);
  - clones con DieSides 0 en la plantilla y puntos base sin +1;
  - scripts del spec sin RegisterSpellScript;
  - scripts y spell_proc del core ligados al id de la plantilla que el clon no copia (necesita mysql);
  - ids de hechizo y rune_id duplicados entre clases.
Imprime solo los problemas; sin salida de avisos significa que no ha encontrado nada.
"""
import collections
import glob
import re
import struct
import subprocess
import sys
from pathlib import Path

R = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(R / 'tools' / 'sod-client'))
import sod_dbc  # noqa: E402

TABLE_SQL = Path.home() / 'Repos/acore-test/data/sql/base/db_world/spell_dbc.sql'
MAX_AURA = 316
# Rejuvenecimiento: base genérica para auras auxiliares; sus scripts del core no se aplican a los clones.
GENERIC_TEMPLATES = {774}


def read_dbc(name):
    data = (R / 'tools/sod-client/_work' / name).read_bytes()
    _, n, _, rec, _ = struct.unpack('<4s4I', data[:20])
    return data, n, rec, data[20 + n * rec:]


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    cls, fam = sys.argv[1], int(sys.argv[2])
    use_mysql = '--sin-mysql' not in sys.argv

    cols = sod_dbc.load_columns(str(TABLE_SQL))
    fi = {c: i for i, c in enumerate(cols)}
    data, n, rs, _ = read_dbc('Spell.dbc')
    rows = {}
    for i in range(n):
        rec = data[20 + i * rs:20 + (i + 1) * rs]
        rows[struct.unpack('<I', rec[:4])[0]] = rec

    def col(sid, name, signed=True):
        pos = fi[name] * 4
        return struct.unpack('<i' if signed else '<I', rows[sid][pos:pos + 4])[0]

    base = R / 'server/mod-sod-content'
    spec = (base / 'tools' / f'sod_spells_{cls}.py').read_text()
    runes_sql = (base / 'data/sql/db-world/base' / f'sod_{cls}_runes.sql').read_text()

    # 1. Iconos de la tabla de runas.
    idata, m, irs, ist = read_dbc('SpellIcon.dbc')
    icons = set()
    for i in range(m):
        off = struct.unpack('<I', idata[20 + i * irs + 4:20 + i * irs + 8])[0]
        icons.add(ist[off:ist.find(b'\0', off)].decode().split('\\')[-1].lower())
    for rid, icon in re.findall(r"\((70\d{5}), \d+, \d+, \d+, ''.*?'', ''([^']*)''", runes_sql):
        if icon not in icons:
            print('ICONO NO EXISTE', rid, icon)

    # 2. Auras fuera de rango.
    consts = dict(re.findall(r'^(\w+) = (\d+)', spec, re.M))
    for a in re.findall(r'"EffectAura_\d": (\w+)', spec):
        v = int(consts.get(a, a)) if (a.isdigit() or a in consts) else None
        if v is not None and v > MAX_AURA:
            print('AURA FUERA DE RANGO', a, v)

    # Un bloque por hechizo: desde su "id" hasta el siguiente.
    blocks = []
    for mm in re.finditer(r'"id": (\d+),\s*"client": \w+,\s*"template": (\w+)', spec):
        nxt = spec.find('"id": ', mm.end())
        blocks.append((int(mm.group(1)), mm.group(2), spec[mm.end():nxt if nxt > 0 else len(spec)]))

    # 3 y 5. Plantillas, familia heredada, DieSides.
    for sid, tpl, blk in blocks:
        if not tpl.isdigit():
            continue
        tpl = int(tpl)
        if tpl not in rows:
            print('PLANTILLA NO EXISTE', sid, tpl)
            continue
        tfam = col(tpl, 'SpellClassSet', False)
        if tfam not in (0, fam) and '"SpellClassSet"' not in blk:
            print('FAMILIA HEREDADA', sid, 'plantilla', tpl, 'familia', tfam)
        for k in (1, 2, 3):
            b = re.search(r'"EffectBasePoints_%d": (-?\d+)' % k, blk)
            if (b and '"EffectDieSides_%d"' % k not in blk and col(tpl, 'EffectDieSides_%d' % k) == 0
                    and '"EffectAura_%d"' % k in blk):
                print('REVISAR DieSides 0 (el valor es la base, sin +1)', sid, 'efecto', k, 'base', b.group(1))

    # 4. Claves de overrides que no son columnas, en todos los specs del módulo.
    colset = set(cols)
    for path in glob.glob(str(base / 'tools/sod_spells_*.py')):
        txt = Path(path).read_text()
        for blk in re.findall(r'"(?:client_)?overrides(?:_float)?": \{(.*?)\}', txt, re.S):
            for k in re.findall(r'"(\w+)":', blk):
                if k not in colset:
                    print('COLUMNA INEXISTENTE (se descarta en silencio)', Path(path).name, k)

    # 6. Scripts del spec y del SQL sin registrar.
    names = set(re.findall(r'"script": "([^"]+)"', spec))
    names |= set(re.findall(rf"'(spell_sod_{cls}_[a-z_]+)'", runes_sql))
    cpp = ''.join(Path(x).read_text() for x in glob.glob(str(base / 'src' / cls / '*.cpp')))
    reg = set(re.findall(r'Register(?:Spell|Aura|Spell\w*Script\w*)\((\w+)', cpp))
    reg |= set(re.findall(r'RegisterSpellScript\((\w+)\)', cpp))
    reg |= set(re.findall(r'RegisterSpellAndAuraScriptPair\((\w+),', cpp))
    for nm in sorted(names - reg):
        core = subprocess.run(['grep', '-rlq', 'class ' + nm, str(R / 'core/src/server/scripts')])
        if core.returncode:
            print('SCRIPT SIN REGISTRAR', nm)

    # 7. Scripts y spell_proc del core que la plantilla tiene y el clon no copia.
    if use_mysql:
        tpls = sorted({int(t) for _, t, _ in blocks if t.isdigit()})
        if tpls:
            def mysql(sql):
                out = subprocess.run(['mysql', '-N', 'acore_world', '-e', sql], capture_output=True, text=True).stdout
                return [line.split('\t') for line in out.split('\n') if line]
            q = ','.join(map(str, tpls))
            # El core ata scripts y spell_proc al primer rango de la cadena (id negativo): seguirla.
            first = {int(a): int(b) for a, b in mysql(
                f"select spell_id, first_spell_id from spell_ranks where spell_id in ({q})")}
            # Talentos: no están en spell_ranks; el primer rango es el de igual nombre y familia con «Rango 1».
            name_col, sub_col = fi['Name_Lang_enUS'] + 6, fi['NameSubtext_Lang_enUS'] + 6
            strs = data[20 + n * rs:]

            def text(sid, c):
                off = struct.unpack('<I', rows[sid][c * 4:c * 4 + 4])[0]
                return strs[off:strs.find(b'\0', off)].decode('utf-8', 'replace')
            first_rank = {}
            for sid in rows:
                if col(sid, 'SpellClassSet', False) and text(sid, sub_col) == 'Rango 1':
                    first_rank[(text(sid, name_col), col(sid, 'SpellClassSet', False))] = sid
            for t in tpls:
                if t not in first and t in rows and text(t, sub_col).startswith('Rango'):
                    f1 = first_rank.get((text(t, name_col), col(t, 'SpellClassSet', False)))
                    if f1 and f1 != t:
                        first[t] = f1
            ids = sorted(set(tpls) | set(first.values()))
            qi = ','.join(map(str, ids))
            have = collections.defaultdict(set)
            for a, b in mysql(f"select abs(spell_id),'S' from spell_script_names where abs(spell_id) in ({qi}) "
                              f"union all select abs(SpellId),'P' from spell_proc where abs(SpellId) in ({qi})"):
                have[int(a)].add(b)
            sql_scripts = {int(a) for a in re.findall(r"\((-?\d+), 'spell_", runes_sql)}
            for sid, tpl, blk in blocks:
                if not tpl.isdigit() or int(tpl) in GENERIC_TEMPLATES:
                    continue
                h = have.get(int(tpl), set()) | have.get(first.get(int(tpl), -1), set())
                falta = [x for x, hit in (('script', 'S' in h and '"script"' not in blk
                                           and sid not in sql_scripts and -sid not in sql_scripts),
                                          ('proc', 'P' in h and '"proc"' not in blk)) if hit]
                if falta:
                    print('PLANTILLA CON', ' Y '.join(falta), 'DEL CORE NO COPIADA', sid, 'plantilla', tpl)

    # 8. Ids duplicados entre clases.
    ids = collections.defaultdict(list)
    for path in glob.glob(str(base / 'tools/sod_spells_*.py')):
        for mm in re.finditer(r'"id": (\d+),', Path(path).read_text()):
            ids[mm.group(1)].append(Path(path).name)
    for k, v in ids.items():
        if len(v) > 1:
            print('ID DE HECHIZO DUPLICADO', k, v)
    sqls = ''.join(Path(x).read_text() for x in glob.glob(str(base / 'data/sql/db-world/base/sod_*_runes.sql')))
    for k, v in collections.Counter(re.findall(r"\((70\d{5}), \d+, \d+, \d+, ''", sqls)).items():
        if v > 1:
            print('RUNE_ID DUPLICADO', k)

    print('revisión hecha')


if __name__ == '__main__':
    main()
