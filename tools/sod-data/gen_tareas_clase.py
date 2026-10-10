#!/usr/bin/env python3
"""Genera los encargos de AgentRelay para las runas base pendientes de una clase.

Uso: python3 tools/sod-data/gen_tareas_clase.py <clase> <directorio_salida> [tamaño_lote]
Cruza el catálogo de SoD con el Spell.dbc/Talent.dbc de 3.3.5a, los instructores y los scripts/spell_proc del core
(mysql de solo lectura) para que el ejecutor no tenga que consultar nada.
"""
import collections, glob, json, re, subprocess, sys
from pathlib import Path

R = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(R / 'tools/sod-client'))
import sod_dbc  # noqa: E402

DBC = Path('/home/stark/Servers/acore-test/data/dbc')
TABLE = Path('/home/stark/Repos/acore-test/data/sql/base/db_world/spell_dbc.sql')
CLASES = {  # es, familia WotLK, class_mask, id de clase del instructor, banda de rune_id, directorio del plan, prefijo de configuración
    'warrior': ('guerrero', 4, 1, 1, 7001000, 'guerrero', 'Warrior'),
    'paladin': ('paladín', 10, 2, 2, 7002000, 'paladin', 'Paladin'),
    'hunter': ('cazador', 9, 4, 3, 7003000, 'cazador', 'Hunter'),
    'rogue': ('pícaro', 8, 8, 4, 7004000, 'picaro', 'Rogue'),
    'priest': ('sacerdote', 6, 16, 5, 7005000, 'sacerdote', 'Priest'),
    'shaman': ('chamán', 11, 64, 7, 7007000, 'chaman', 'Shaman'),
    'mage': ('mago', 3, 128, 8, 7000000, 'mago', 'Mage'),
    'warlock': ('brujo', 5, 256, 9, 7008000, 'brujo', 'Warlock'),
    'druid': ('druida', 7, 1024, 11, 7009000, 'druida', 'Druid'),
}
SLOTS = {'Chest': ('Pecho', 16), 'Legs': ('Piernas', 256), 'Hands': ('Manos', 64), 'slot_415449': ('Cintura', 128),
         'slot_415450': ('Pies', 512), 'slot_417345': ('Cabeza', 1), 'slot_417346': ('Muñecas', 32),
         'slot_417347': ('Espalda', 8)}
ORDEN = list(SLOTS)


def mysql(sql):
    out = subprocess.run(['mysql', '-N', 'acore_world', '-e', sql], capture_output=True, text=True).stdout
    return [l.split('\t') for l in out.split('\n') if l]


def cargar_dbc(fam, cmask):
    cols = sod_dbc.load_columns(str(TABLE))
    fi = {c: i for i, c in enumerate(cols)}
    spell = sod_dbc.WDBC.load(str(DBC / 'Spell.dbc'))

    def s(rec, c):
        off = spell.get_int(rec, fi[c])
        end = spell.strings.find(b'\0', off)
        return bytes(spell.strings[off:end]).decode('utf-8', 'replace') if off >= 0 else ''
    grupos = collections.defaultdict(list)
    info = {}
    for rec in spell.records:
        if spell.get_int(rec, fi['SpellClassSet']) != fam:
            continue
        sid = spell.get_int(rec, 0)
        nm, rk = s(rec, 'Name_Lang_enUS'), s(rec, 'NameSubtext_Lang_enUS')
        if not nm:
            continue
        m = re.match(r'Rank (\d+)', rk)
        masks = [spell.get_int(rec, fi['SpellClassMask_%d' % k]) & 0xFFFFFFFF for k in (1, 2, 3)]
        info[sid] = dict(name=nm, rank=int(m.group(1)) if m else 0, level=spell.get_int(rec, fi['SpellLevel']), masks=masks)
        grupos[nm.lower()].append(sid)
    tal = sod_dbc.WDBC.load(str(DBC / 'Talent.dbc'))
    tab = sod_dbc.WDBC.load(str(DBC / 'TalentTab.dbc'))
    tabs = {tab.get_int(r, 0) for r in tab.records if tab.get_int(r, 20) & cmask}
    talentos = {}
    for r in tal.records:
        if tal.get_int(r, 1) in tabs:
            for k in range(4, 13):
                sp = tal.get_int(r, k)
                if sp:
                    talentos[sp] = k - 3
    return info, grupos, talentos


def describir(nombre_grupo, grupos, info, talentos, instructor):
    ids = sorted(grupos[nombre_grupo], key=lambda i: (info[i]['rank'], i))
    ids = [i for i in ids if info[i]['rank'] > 0] or ids
    primero, ultimo = ids[0], ids[-1]
    m = info[ultimo]['masks']
    txt = f"{info[ultimo]['name']} {primero}..{ultimo}" if primero != ultimo else f"{info[ultimo]['name']} {ultimo}"
    extras = []
    if any(i in talentos for i in ids):
        extras.append('talento')
    nivel = [instructor[i] for i in ids if i in instructor]
    if nivel:
        extras.append(f'instructor nivel {min(nivel)}')
    if extras:
        txt += f" ({', '.join(extras)})"
    masc = [f'{n}{v:#x}' for n, v in zip('ABC', m) if v]
    if masc:
        txt += f" [máscara {' '.join(masc)}]"
    return txt, ids


def main():
    cls, salida = sys.argv[1], Path(sys.argv[2])
    lote = int(sys.argv[3]) if len(sys.argv) > 3 else 5
    es, fam, cmask, trainer_cls, banda, plan, pref = CLASES[cls]
    info, grupos, talentos = cargar_dbc(fam, cmask)
    instructor = {int(a): int(b) for a, b in mysql(
        f"select ts.SpellId, ts.ReqLevel from trainer t join trainer_spell ts on ts.TrainerId=t.Id where t.Type=0 and t.Requirement={trainer_cls}")}

    cat = json.load(open(R / 'docs/runas/catalogo-sod.json'))['runas']
    sql_all = ''.join(Path(p).read_text() for p in glob.glob(str(R / 'server/mod-sod-content/data/sql/db-world/base/sod_*_runes.sql')))
    impl = {int(x) for x in re.findall(r"\(70\d{5}, (\d+),", sql_all)}
    propio = (R / f'server/mod-sod-content/data/sql/db-world/base/sod_{cls}_runes.sql')
    propios = [int(x) for x in re.findall(r"\((70\d{5}), \d+, \d+, \d+, ''", propio.read_text())] if propio.exists() else []
    siguiente = max(propios + [banda]) + 1
    pend = {}
    for r in cat:
        if r['clase'] == cls and r['slot'] in SLOTS and r['taught_spell_id'] not in impl and r['name_en']:
            pend.setdefault(r['name_en'], r)
    runas = sorted(pend.values(), key=lambda r: (ORDEN.index(r['slot']), r['name_en']))
    maxaux = max([int(x) for x in re.findall(r'"id": (9000\d\d)', ''.join(
        Path(p).read_text() for p in glob.glob(str(R / 'server/mod-sod-content/tools/sod_spells*.py'))))] + [900000])

    nombres_clase = sorted((n for n in grupos if len(n) >= 5), key=len, reverse=True)
    tareas = []
    for k in range(0, len(runas), lote):
        tanda = runas[k:k + lote]
        items, mencionadas, ids_core = [], collections.OrderedDict(), set()
        for j, r in enumerate(tanda):
            rid = siguiente + k + j
            sl, mask = SLOTS[r['slot']]
            eq = ''
            g = r['name_en'].lower()
            if g in grupos:
                txt, ids = describir(g, grupos, info, talentos, instructor)
                eq = f' Equivalente en WotLK por nombre: {txt}.'
                ids_core.update(ids)
            desc = (r['desc_en'] or '').replace('\n', ' ')
            for n in nombres_clase:
                if n != g and re.search(r'\b' + re.escape(n) + r'\b', desc.lower()) and n not in mencionadas:
                    t2, ids2 = describir(n, grupos, info, talentos, instructor)
                    mencionadas[n] = t2
                    ids_core.update(ids2)
            efectos = [(e['effect'], e['effect_aura'], e['effect_base_points'], e['effect_trigger_spell'], e['effect_misc_value_0']) for e in r['effects']]
            items.append(f"- {r['name_en']} (rune_id {rid}, hechizo SoD {r['taught_spell_id']}, {sl}, slot_mask {mask}): '{desc}' "
                         f"Efectos del catálogo (efecto, aura, puntos base, disparo, misc): {efectos}; enfriamiento {r['cooldown_ms']} ms, "
                         f"coste {r['mana_pct']} %, duración {r['duration_ms']} ms, probabilidad de proc {r['proc_chance']}.{eq}\n")
        core = ''
        if ids_core:
            q = ','.join(map(str, sorted(ids_core)))
            sc = mysql(f"select spell_id,ScriptName from spell_script_names where abs(spell_id) in ({q})")
            pr = mysql(f"select SpellId,SpellFamilyName,SpellFamilyMask0,SpellFamilyMask1,SpellFamilyMask2,ProcFlags,SpellTypeMask,SpellPhaseMask,HitMask,AttributesMask,Chance,Cooldown,Charges from spell_proc where abs(SpellId) in ({q})")
            core = ('\nSCRIPTS Y SPELL_PROC DEL CORE consultados por el orquestador (los ligados a un id negativo valen para toda la cadena de rangos; '
                    'cópialos en el spec con las claves script y proc cuando clones esa plantilla): spell_script_names: '
                    + ('; '.join(f'{a} {b}' for a, b in sc) or 'ninguno')
                    + '. spell_proc (SpellId, familia, máscaras 0/1/2, ProcFlags, SpellTypeMask, SpellPhaseMask, HitMask, AttributesMask, Chance, Cooldown, Charges): '
                    + ('; '.join('(' + ', '.join(x) + ')' for x in pr) or 'ninguno') + '.')
        wot = ''
        if mencionadas:
            wot = ('\nHechizos de WotLK que nombran las descripciones (familia %d; cadena de rangos primero..último y máscara de familia): ' % fam
                   + '; '.join(mencionadas.values()) + '.')
        rids = [siguiente + k + j for j in range(len(tanda))]
        nombres = [r['name_en'] for r in tanda]
        cabeza = (f"Proyecto: SoD sobre AzerothCore 3.3.5a (core propio en core/, NO el oficial: comprueba firmas allí). Del {es} ya hay {len(propios)} runas "
                  f"en server/mod-sod-content/tools/sod_spells_{cls}.py y data/sql/db-world/base/sod_{cls}_runes.sql. Sigue EXACTAMENTE el patrón del chamán y del brujo, "
                  f"ya revisados: server/mod-sod-content/tools/sod_spells_shaman.py, sod_shaman_runes.sql, src/shaman/ (cabecera spell_sod_shaman.h con enum de ids y "
                  f"funciones SodShaman*, un .cpp por runa, registro en src/sod_content_loader.cpp, scripts sobre hechizos de WotLK vía spell_script_names con ids negativos "
                  f"para todos los rangos). Para el {es} usa src/{cls}/spell_sod_{cls}.h (créala si no existe) y los .cpp en src/{cls}/, con las funciones "
                  f"Sod{pref}*() y Sod{pref}Enabled() que leen 'Sod{pref}.Enable' (sección '# {pref.upper()}' en conf/mod_sod_content.conf.dist, si no existe). "
                  f"Plan: .agents/plans/{plan}/{plan}.PLAN.md. ")
        reglas = ("Reglas aprendidas al revisar otras clases (cúmplelas): (a) slot_mask = 1<<ranura; class_mask del %s = %d. "
                  "(b) Un clon hereda la familia (SpellClassSet) y las máscaras de su plantilla: si clonas un hechizo de otra clase o genérico (p. ej. Rejuvenecimiento 774), "
                  "pon 'SpellClassSet': %d y máscaras a 0 salvo que necesites otras. (c) El campo icon de la fila de rune_template debe ser un icono que EXISTA en el cliente 3.3.5a "
                  "(minúsculas, como los de las plantillas WotLK); si dudas, usa el icono de la plantilla de WotLK. (d) Los tipos de aura válidos van de 0 a 316 (TOTAL_AURAS 317): el catálogo "
                  "de SoD usa auras modernas (p. ej. 332, 561) que NO existen; sustitúyelas por script o por auras de 3.3.5a. (e) Comprueba que el hechizo de WotLK que enlaces o clones existe y hace "
                  "lo que crees; si el comportamiento ya existe igual en WotLK, no lo dupliques. (f) Todo hechizo que un script lance (CastSpell/CastCustomSpell) debe estar definido en el spec o existir en WotLK. "
                  "(g) Cada 'script' del spec debe tener su RegisterSpellScript; si enganchas un script a un hechizo de WotLK existente, añade la fila a spell_script_names con INSERT IGNORE en sod_%s_runes.sql. "
                  "(h) Hechizos auxiliares nuevos sin id de SoD: usa ids libres a partir de %d (el mayor 9000xx usado hoy es %d; comprueba con grep antes de usar uno). "
                  "(j) Los scripts del core y las filas de spell_proc van ligados al id de WotLK (a menudo negativo: todos los rangos): un clon con id nuevo NO los hereda; se te dan abajo los de las plantillas, "
                  "cópialos con las claves 'script' y 'proc' del spec (ejemplos en sod_spells_shaman.py: Tidal Waves, Ancestral Awakening, Static Shock, Earth Shield). "
                  "(k) Las claves de 'overrides' deben ser columnas reales de spell_dbc (lista en /home/stark/Repos/acore-test/data/sql/base/db_world/spell_dbc.sql): el generador descarta en silencio las que no lo son. "
                  "Para acumulaciones usa 'CumulativeAura' (no 'StackAmount'), para objetivos 'MaxTargets', y los coeficientes de poder con hechizos van en la clave 'bonus' del spec ({'direct','dot','ap','ap_dot'}). "
                  "(l) Si un clon de una plantilla con EffectDieSides 0 usa puntos base, el valor es la base exacta; con DieSides 1 es base+1. "
                  "(m) No tienes acceso a MySQL ni a Wowhead desde tu entorno: no lo intentes; el orquestador ya verificó los ids que se te dan. (n) Nada de topes de nivel como constantes. ") % (es, cmask, fam, cls, maxaux + 1, maxaux)
        datos = ("Datos de SoD (build 1.15.9, docs/runas/catalogo-sod.json). Los nombres de WotLK vienen del Spell.dbc 3.3.5a del servidor.\nRunas de esta tarea:\n")
        cola = (f"\nTextos esES en tools/sod_spells_es.json (nombres oficiales en docs/runas/{cls}.md). Filas nuevas en docs/runas/obtencion.md (adquisición provisional: compra en el Grabador). "
                f"Casillas de prueba en docs/PRUEBAS.md, sección '### {es.capitalize()}' (créala antes de '### Druida feral' si no existe), con lo que debe comprobar el usuario y las diferencias conocidas. "
                f"Simplificaciones: TODO.md, sección '## {es.capitalize()}' (créala antes de '## Otras clases'). Si una runa no se puede hacer sin parchear el core o sin un dato que no tienes, "
                f"impleméntala hasta donde se pueda y documenta la parte que falta en TODO.md; no dejes la tarea a medias sin informar.")
        t = {
            'objective': f"Añadir {len(tanda)} runas de {es} de SoD: " + ', '.join(f'{n} ({r})' for n, r in zip(nombres, rids)) + '.',
            'effort': 'high',
            'context': cabeza + reglas + datos + ''.join(items) + wot + core + cola,
            'files': [f'server/mod-sod-content/tools/sod_spells_{cls}.py', 'server/mod-sod-content/tools/sod_spells_es.json',
                      f'server/mod-sod-content/data/sql/db-world/base/sod_{cls}_runes.sql', f'server/mod-sod-content/src/{cls}/spell_sod_{cls}.h',
                      f'server/mod-sod-content/src/{cls}/', 'server/mod-sod-content/src/sod_content_loader.cpp',
                      'server/mod-sod-content/conf/mod_sod_content.conf.dist', 'docs/runas/obtencion.md', 'docs/PRUEBAS.md', 'TODO.md'],
            'constraints': [
                'Informe, comentarios y documentación en castellano; identificadores en inglés.',
                'No toques runas ya existentes ni otras clases.',
                'Solo clang -fsyntax-only mediante tools/sod-data/check_syntax.py; nada de cmake ni make.',
                'No parchees core/: si algo exige cambiar el core, documéntalo en TODO.md y en el informe.',
                'No inventes valores: si no puedes verificar uno, usa el del catálogo y dilo en el informe.',
                'Eres SOLO el ejecutor de esta tarea. Ignora las partes de AGENTS.md que describen al orquestador (ponerse al día, delegar, mantener ESTADO.md, hacer commits): no las sigas.',
                'No ejecutes ningún comando de git que escriba (add, commit, stash, checkout, reset, push...). El orquestador hace los commits.',
                'No crees carpetas en datos/parche-cliente ni archivos LISTO o PUBLICADO, no ejecutes nada del repositorio ~/Repos/launcher, ni tools/sod-client/build_patch.py ni tools/sod-data/regenerar_sql_hechizos.sh, y no edites sod_content_spell_dbc.sql: lo regenera el orquestador.',
                'No edites CHANGELOG.md, docs/ESTADO.md, .agents/ ni AGENTS.md.',
                f'Antes de terminar ejecuta python3 tools/sod-data/revisar_runas.py {cls} {fam} --sin-mysql y corrige lo que señale en TUS runas (los avisos de runas anteriores no son tuyos); deja el resultado en el informe.',
            ],
            'acceptanceCriteria': [f'Las runas {rids[0]}-{rids[-1]} existen en sod_spells_{cls}.py y sod_{cls}_runes.sql con el slot_mask y el icono indicados.',
                                   f'Cada script C++ nuevo está declarado en spell_sod_{cls}.h y registrado en sod_content_loader.cpp; ningún aura fuera de 0-316.',
                                   'python3 tools/sod-data/check_syntax.py termina sin errores.',
                                   'docs/runas/obtencion.md, docs/PRUEBAS.md y TODO.md actualizados.'],
            'validation': [f"python3 -c \"import ast; ast.parse(open('server/mod-sod-content/tools/sod_spells_{cls}.py').read()); print('ok')\""],
            'doNotModify': ['core', 'upstream', 'datos', 'AGENTS.md', 'CHANGELOG.md', 'docs/ESTADO.md', '.agents', 'tools/sod-client',
                            'server/mod-sod-content/data/sql/db-world/base/sod_content_spell_dbc.sql'],
        }
        salida.mkdir(parents=True, exist_ok=True)
        (salida / f'{cls}{k // lote + 1}.json').write_text(json.dumps(t, ensure_ascii=False, indent=1))
        tareas.append((rids, nombres))
    for i, (rids, nombres) in enumerate(tareas, 1):
        print(f'{cls}{i}: {rids[0]}-{rids[-1]} {", ".join(nombres)}')


if __name__ == '__main__':
    main()
