#!/usr/bin/env python3
"""Classify catalogued SoD runes by implementation difficulty."""

import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.dont_write_bytecode = True
sys.path.insert(0, str(ROOT / "tools" / "sod-data"))
import match_wotlk


CATALOG_PATH = ROOT / "docs" / "runas" / "catalogo-sod.json"
EQUIVALENCES_PATH = ROOT / "docs" / "runas" / "equivalencias-wotlk.json"
JSON_PATH = ROOT / "docs" / "runas" / "plan-implementacion.json"
MARKDOWN_PATH = ROOT / "docs" / "runas" / "plan-implementacion.md"
SUMMARY_PATH = ROOT / "docs" / "runas" / "plan-implementacion-resumen.md"
SPELL_SQL = Path("/home/stark/Repos/acore-test/data/sql/base/db_world/spell_dbc.sql")
DBC_ROOT = Path("/home/stark/Servers/acore-test/data/dbc")
SPEC_ROOT = ROOT / "server" / "mod-sod-content" / "tools"
RUNE_SQL_ROOT = ROOT / "server" / "mod-sod-content" / "data" / "sql" / "db-world" / "base"

TRIGGER_AURAS = {4, 226, 231, 232, 23, 24}
FORBIDDEN_PASSIVE_AURAS = {4, 226, 231, 232}
CLASS_NAMES = {
    "druid": "Druida", "hunter": "Cazador", "mage": "Mago",
    "paladin": "Paladín", "priest": "Sacerdote", "rogue": "Pícaro",
    "shaman": "Chamán", "warlock": "Brujo", "warrior": "Guerrero",
    "deathknight": "Caballero de la Muerte", "desconocida": "Desconocida",
}
SLOT_NAMES = {
    "Chest": "Pecho", "Legs": "Piernas", "Hands": "Manos",
    "Wrist": "Muñecas", "Waist": "Cintura", "Feet": "Pies",
    "Head": "Cabeza", "Neck": "Cuello", "Shoulder": "Hombros",
    "Cloak": "Capa", "Ring": "Anillo",
}
SLOT_PHASES = {
    "chest": "Fase 1", "legs": "Fase 1", "hands": "Fase 1",
    "wrist": "Fase 2", "waist": "Fase 2", "feet": "Fase 2",
    "head": "Fase 3",
}
TYPE_NAMES = {
    "talento": "Talento", "sin_equivalente": "Sin equivalente",
    "activo": "Activo", "pasivo": "Pasivo", "sin_clasificar": "Sin clasificar",
}
LEVEL_ORDER = {"P": 0, "T": 1, "C": 2, "R": 3, None: 4}
PHASE_ORDER = {"Fase 1": 1, "Fase 2": 2, "Fase 3": 3, "Fase 4": 4, "desconocida": 5}
SLOT_ORDER = {name.casefold(): index for index, name in enumerate(SLOT_NAMES)}


def number(value):
    """Parse an optional numeric catalog value."""
    if value is None or value == "":
        return None
    try:
        return float(value)
    except (TypeError, ValueError):
        return None


def is_positive(value):
    parsed = number(value)
    return parsed is not None and parsed > 0


def classify(rune, rune_type):
    """Return a conservative level and a concise Spanish explanation."""
    effects = rune.get("effects") or []
    description = (rune.get("desc_en") or "").casefold()
    keywords = ("transform", "metamorphosis", "summon", "taunt", "stance")

    if any(number(effect.get("effect")) == 3 for effect in effects):
        return "C", "Incluye un efecto DUMMY y requiere lógica propia en C++."
    if any(number(effect.get("effect_aura")) == 4 for effect in effects):
        return "C", "Incluye un aura DUMMY y requiere lógica propia en C++."
    keyword = next((word for word in keywords if word in description), None)
    if keyword:
        return "C", "La descripción indica una mecánica compleja («{}»).".format(keyword)
    if rune_type == "sin_equivalente" and (
        is_positive(rune.get("cast_ms")) or is_positive(rune.get("cooldown_ms"))
    ):
        return "C", "Es una habilidad activa nueva sin equivalente en WotLK."

    if is_positive(rune.get("proc_chance")):
        return "T", "Tiene una probabilidad de proc configurada."
    if any(is_positive(effect.get("effect_trigger_spell")) for effect in effects):
        return "T", "Uno de sus efectos dispara otro hechizo."
    if any(number(effect.get("effect_aura")) in TRIGGER_AURAS for effect in effects):
        return "T", "Usa un aura asociada a proc o activación."

    has_aura = any(number(effect.get("effect")) == 6 for effect in effects)
    has_trigger = any(
        is_positive(effect.get("effect_trigger_spell"))
        or number(effect.get("effect")) == 3
        or number(effect.get("effect_aura")) in FORBIDDEN_PASSIVE_AURAS
        for effect in effects
    )
    if (
        has_aura
        and not has_trigger
        and not is_positive(rune.get("cast_ms"))
        and not is_positive(rune.get("cooldown_ms"))
    ):
        return "P", "Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización."

    return "C", "Los datos no encajan en las reglas simples; se asigna C por prudencia."


def template_ids(equivalence):
    """Return the highest WotLK template spell id when it has one."""
    highest = equivalence.get("rango_mas_alto")
    spell_id = highest.get("id") if isinstance(highest, dict) else None
    return [spell_id] if spell_id is not None else []


def load_wotlk_spells():
    """Build the exact-name WotLK index using the local DBC and schema."""
    columns = match_wotlk.sod_dbc.load_columns(str(SPELL_SQL))
    column_map = {name: index for index, name in enumerate(columns)}
    spell_dbc = match_wotlk.sod_dbc.WDBC.load(str(DBC_ROOT / "Spell.dbc"))
    if spell_dbc.nfield != len(columns):
        raise RuntimeError(
            "Spell.dbc tiene {} campos y spell_dbc define {}".format(
                spell_dbc.nfield, len(columns)
            )
        )
    talent_dbc = match_wotlk.sod_dbc.WDBC.load(str(DBC_ROOT / "Talent.dbc"))
    talent_by_spell = match_wotlk.load_talents(talent_dbc)
    return match_wotlk.index_spells(spell_dbc, column_map, talent_by_spell, {})


def infer_equivalence(rune, stored_by_id, spells_by_name):
    """Use stored reviewed matches first, then exact WotLK name matches."""
    spell_id = rune.get("taught_spell_id")
    stored = stored_by_id.get(spell_id)
    if stored is not None:
        return stored.get("tipo"), template_ids(stored)

    candidates = spells_by_name.get((rune.get("name_en") or "").casefold(), [])
    if not candidates:
        return "sin_equivalente", []
    if any(candidate["es_rango_talento"] for candidate in candidates):
        kind = "talento"
    elif all(candidate["pasivo"] for candidate in candidates):
        kind = "pasivo"
    else:
        kind = "activo"
    highest = max(candidates, key=lambda spell: (spell["nivel"] or 0, spell["id"]))
    return kind, [highest["id"]]


def implemented_spell_ids(catalog_ids):
    """Read taught spell ids from specs and rune_template SQL rows."""
    found = set()
    for path in sorted(SPEC_ROOT.glob("sod_spells*.py")):
        text = path.read_text(encoding="utf-8")
        found.update(int(value) for value in re.findall(r'"id"\s*:\s*(\d+)', text))

    sql_paths = set(RUNE_SQL_ROOT.glob("sod_*_runes.sql"))
    sql_paths.update(RUNE_SQL_ROOT.glob("sod_mage_*.sql"))
    integer = r"(?:-?\d+|NULL)"
    for path in sorted(sql_paths):
        text = path.read_text(encoding="utf-8")
        blocks = re.finditer(
            r"INSERT\s+INTO\s+`rune_template`\s*\((.*?)\)\s*VALUES(.*?)"
            r"ON\s+DUPLICATE\s+KEY\s+UPDATE",
            text, re.IGNORECASE | re.DOTALL,
        )
        for block in blocks:
            columns = re.findall(r"`([A-Za-z0-9_]+)`", block.group(1))
            if "spell_id" not in columns:
                continue
            spell_column = columns.index("spell_id")
            tuple_pattern = (
                r"\(\s*(?:" + integer + r"\s*,\s*){" + str(spell_column)
                + r"}(" + integer + r")\s*,"
            )
            found.update(
                int(value) for value in re.findall(tuple_pattern, block.group(2))
                if value != "NULL"
            )
    return found & catalog_ids


def phase_for_slot(slot):
    """Return only phases supported by an explicit catalog slot name."""
    return SLOT_PHASES.get((slot or "").casefold(), "desconocida")


def display_slot(slot):
    if not slot:
        return "desconocida"
    return SLOT_NAMES.get(slot, slot)


def build_plan(catalog, stored_equivalences, implemented_ids, spells_by_name):
    stored_by_id = {
        item.get("taught_spell_id"): item for item in stored_equivalences
    }
    plan = []
    for rune in catalog:
        spell_id = rune.get("taught_spell_id")
        class_name = rune.get("clase") or "desconocida"
        slot = rune.get("slot") or "desconocida"
        implemented = spell_id in implemented_ids

        if class_name == "desconocida" or class_name not in CLASS_NAMES:
            rune_type = "sin_clasificar"
            level = None
            reason = "El catálogo no aporta una clase que permita clasificar esta runa."
            templates = []
            redundant = False
        else:
            rune_type, templates = infer_equivalence(rune, stored_by_id, spells_by_name)
            redundant = rune_type == "activo" and bool(templates)
            if redundant:
                level = "R"
                reason = (
                    "Tiene un hechizo WotLK con el mismo nombre exacto; se marca como "
                    "redundante para decisión del usuario."
                )
            else:
                level, reason = classify(rune, rune_type)

        plan.append({
            "taught_spell_id": spell_id,
            "name_en": rune.get("name_en"),
            "clase": class_name,
            "slot": slot,
            "ranura": display_slot(slot),
            "fase": phase_for_slot(slot),
            "tipo": rune_type,
            "nivel": level,
            "implementada": implemented,
            "redundante_wotlk": redundant,
            "razon": reason,
            "riesgo_hueco": rune_type == "talento" and level in {"P", "T"},
            "plantilla_wotlk": templates,
        })

    plan.sort(key=lambda item: (
        LEVEL_ORDER[item["nivel"]],
        CLASS_NAMES.get(item["clase"], item["clase"] or ""),
        PHASE_ORDER.get(item["fase"], 99),
        SLOT_ORDER.get(item["slot"].casefold(), 99),
        item["slot"],
        (item["name_en"] or "").casefold(),
        item["taught_spell_id"] or 0,
    ))
    return plan


def escape_cell(value):
    return str(value if value not in (None, "") else "—").replace("|", "\\|").replace("\n", " ")


def pending_rows(plan):
    return [item for item in plan if not item["implementada"]]


def markdown_report(plan):
    """Render summaries, slot counts and pending tables in Spanish."""
    pending = pending_rows(plan)
    by_level = Counter(item["nivel"] for item in pending)
    by_phase = defaultdict(Counter)
    by_class_level = defaultdict(Counter)
    by_class = Counter()
    by_slot_class = Counter()
    implemented_by_class = Counter()
    for item in plan:
        by_phase[item["fase"]]["implementadas" if item["implementada"] else "pendientes"] += 1
        by_class[item["clase"]] += 1
        if item["implementada"]:
            implemented_by_class[item["clase"]] += 1
        else:
            by_class_level[item["clase"]][item["nivel"] or "?"] += 1
        by_slot_class[(item["slot"], item["fase"], item["clase"])] += 1

    lines = [
        "# Plan de implementación de runas de SoD",
        "",
        "El plan incluye las filas del catálogo de todas las clases y ranuras. "
        "Los emparejamientos nuevos usan el nombre inglés exacto en los DBC locales; "
        "las coincidencias ya documentadas se conservan.",
        "",
        "P = pasiva sencilla; T = proc o disparo; C = requiere C++ o no encaja en las reglas; "
        "R = equivalente activo por nombre en WotLK, pendiente de decisión. "
        "Las filas de clase desconocida quedan sin clasificar.",
        "",
        "Las fases solo se asignan cuando el nombre de ranura del catálogo lo permite: "
        "pecho, piernas y manos = fase 1; muñecas, cintura y pies = fase 2; cabeza = fase 3. "
        "No se deduce una fase para cuello ni para identificadores `slot_<id>`. ",
        "",
        "## Resumen por fase",
        "",
        "| Fase | Pendientes | Implementadas | Total |",
        "|---|---:|---:|---:|",
    ]
    phases = sorted(by_phase, key=lambda phase: PHASE_ORDER.get(phase, 99))
    for phase in phases:
        counts = by_phase[phase]
        lines.append("| {} | {} | {} | {} |".format(
            phase, counts["pendientes"], counts["implementadas"],
            counts["pendientes"] + counts["implementadas"],
        ))
    lines.extend([
        "",
        "## Resumen por clase",
        "",
        "| Clase | P | T | C | R | Sin clasificar | Implementadas | Total |",
        "|---|---:|---:|---:|---:|---:|---:|---:|",
    ])
    classes = sorted(
        set(by_class) | {"deathknight"},
        key=lambda name: (name == "desconocida", CLASS_NAMES.get(name, name)),
    )
    for class_name in classes:
        counts = by_class_level[class_name]
        lines.append("| {} | {} | {} | {} | {} | {} | {} | {} |".format(
            CLASS_NAMES.get(class_name, class_name),
            counts["P"], counts["T"], counts["C"], counts["R"], counts["?"],
            implemented_by_class[class_name], by_class[class_name],
        ))
    lines.extend([
        "",
        "## Ranuras encontradas por clase",
        "",
        "Se conserva el identificador `slot_<id>` cuando el catálogo no proporciona un nombre.",
        "",
        "| Ranura | Fase | Clase | Runas |",
        "|---|---|---|---:|",
    ])
    slot_rows = sorted(by_slot_class.items(), key=lambda entry: (
        PHASE_ORDER.get(entry[0][1], 99), SLOT_ORDER.get(entry[0][0].casefold(), 99),
        entry[0][0], entry[0][2],
    ))
    for (slot, phase, class_name), count in slot_rows:
        lines.append("| {} | {} | {} | {} |".format(
            display_slot(slot), phase, CLASS_NAMES.get(class_name, class_name), count
        ))

    for class_name in classes:
        if class_name == "desconocida":
            continue
        rows = [item for item in pending if item["clase"] == class_name]
        lines.extend([
            "",
            "## {}: runas no implementadas ({})".format(
                CLASS_NAMES.get(class_name, class_name), len(rows)
            ),
            "",
            "| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |",
            "|---:|---|---|---|---|---|---|",
        ])
        for item in rows:
            lines.append("| {} | {} | {} | {} | {} | {} | {} |".format(
                escape_cell(item["taught_spell_id"]), escape_cell(item["name_en"]),
                escape_cell(item["ranura"]), escape_cell(item["fase"]),
                TYPE_NAMES.get(item["tipo"], item["tipo"]),
                escape_cell(item["nivel"]), escape_cell(item["razon"]),
            ))

    unknown = [item for item in pending if item["clase"] == "desconocida"]
    lines.extend([
        "",
        "## Clase desconocida: runas sin clasificar ({})".format(len(unknown)),
        "",
        "| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |",
        "|---:|---|---|---|---|---|---|",
    ])
    for item in unknown:
        lines.append("| {} | {} | {} | {} | {} | {} | {} |".format(
            escape_cell(item["taught_spell_id"]), escape_cell(item["name_en"]),
            escape_cell(item["ranura"]), escape_cell(item["fase"]),
            TYPE_NAMES[item["tipo"]], escape_cell(item["nivel"]), escape_cell(item["razon"]),
        ))
    return "\n".join(lines) + "\n"


def summary_report(plan):
    """Render compact count summaries by level, phase and class."""
    pending = pending_rows(plan)
    levels = Counter(item["nivel"] or "sin_clasificar" for item in pending)
    phases = defaultdict(Counter)
    classes = defaultdict(Counter)
    for item in plan:
        state = "implementadas" if item["implementada"] else "pendientes"
        phases[item["fase"]][state] += 1
        classes[item["clase"]]["total"] += 1
        if item["implementada"]:
            classes[item["clase"]]["implementadas"] += 1
        else:
            classes[item["clase"]][item["nivel"] or "sin_clasificar"] += 1

    lines = [
        "# Resumen del plan de runas de SoD",
        "",
        "Conteos del catálogo completo; P/T/C/R y sin clasificar cuentan solo runas pendientes.",
        "",
        "## Pendientes por nivel",
        "",
        "| Nivel | Runas |",
        "|---|---:|",
    ]
    for level, label in (("P", "P — Pasiva"), ("T", "T — Proc o disparo"),
                         ("C", "C — Requiere C++"), ("R", "R — Redundante en WotLK"),
                         ("sin_clasificar", "Sin clasificar")):
        lines.append("| {} | {} |".format(label, levels[level]))
    lines.extend([
        "",
        "## Pendientes e implementadas por fase",
        "",
        "| Fase | Pendientes | Implementadas | Total |",
        "|---|---:|---:|---:|",
    ])
    for phase in sorted(phases, key=lambda name: PHASE_ORDER.get(name, 99)):
        counts = phases[phase]
        lines.append("| {} | {} | {} | {} |".format(
            phase, counts["pendientes"], counts["implementadas"],
            counts["pendientes"] + counts["implementadas"],
        ))
    lines.extend([
        "",
        "## Pendientes por clase",
        "",
        "| Clase | P | T | C | R | Sin clasificar | Implementadas | Total |",
        "|---|---:|---:|---:|---:|---:|---:|---:|",
    ])
    class_names = set(classes) | {"deathknight"}
    for class_name in sorted(
        class_names, key=lambda name: (name == "desconocida", CLASS_NAMES.get(name, name))
    ):
        counts = classes[class_name]
        lines.append("| {} | {} | {} | {} | {} | {} | {} | {} |".format(
            CLASS_NAMES.get(class_name, class_name), counts["P"], counts["T"],
            counts["C"], counts["R"], counts["sin_clasificar"],
            counts["implementadas"], counts["total"],
        ))
    return "\n".join(lines) + "\n"


def main():
    catalog = json.loads(CATALOG_PATH.read_text(encoding="utf-8"))["runas"]
    stored_equivalences = json.loads(EQUIVALENCES_PATH.read_text(encoding="utf-8"))
    catalog_ids = {rune.get("taught_spell_id") for rune in catalog}
    implemented_ids = implemented_spell_ids(catalog_ids)
    spells_by_name = load_wotlk_spells()
    plan = build_plan(catalog, stored_equivalences, implemented_ids, spells_by_name)

    JSON_PATH.write_text(
        json.dumps(plan, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    MARKDOWN_PATH.write_text(markdown_report(plan), encoding="utf-8")
    SUMMARY_PATH.write_text(summary_report(plan), encoding="utf-8")

    totals = Counter(item["nivel"] if item["nivel"] else "sin_clasificar" for item in pending_rows(plan))
    print("Filas del catálogo: {}".format(len(plan)))
    print("Runas implementadas: {}".format(sum(item["implementada"] for item in plan)))
    print("Pendientes por nivel: {}".format(dict(sorted(totals.items()))))


if __name__ == "__main__":
    main()
