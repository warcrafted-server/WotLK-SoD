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
ENGRAVING_SLOTS = {
    399954: ("Chest", "Pecho"),
    399966: ("Legs", "Piernas"),
    399967: ("Hands", "Manos"),
    417346: ("Bracer", "Muñecas"),
    415449: ("Waist", "Cintura"),
    415450: ("Feet", "Pies"),
    417345: ("Helm", "Cabeza"),
    417347: ("Cloak", "Espalda"),
}
SOUL_SLOT_ID = 1219955
RACIAL_SLOT_IDS = {459695, 1219274}
SLOT_ORDER = {
    slot_id: index for index, slot_id in enumerate(ENGRAVING_SLOTS)
}
CATEGORY_ORDER = {"runa": 0, "alma": 1, "racial": 2, "ruido": 3}
TYPE_NAMES = {
    "talento": "Talento", "sin_equivalente": "Sin equivalente",
    "activo": "Activo", "pasivo": "Pasivo", "sin_clasificar": "Sin clasificar",
}
LEVEL_ORDER = {"P": 0, "T": 1, "C": 2, "R": 3, None: 4}


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


def category_for_slot(slot_id):
    """Return the catalog category determined by its slot spell id."""
    if slot_id in ENGRAVING_SLOTS:
        return "runa"
    if slot_id == SOUL_SLOT_ID:
        return "alma"
    if slot_id in RACIAL_SLOT_IDS:
        return "racial"
    return "ruido"


def slot_labels(rune, category):
    """Return stable slot labels while preserving unknown catalog values."""
    slot_id = rune.get("slot_id")
    if category == "runa":
        english, spanish = ENGRAVING_SLOTS[slot_id]
        return english, spanish, english
    if category == "alma":
        return "Soul Engraving", "Grabado de alma", "Soul Engraving"
    slot = rune.get("slot") or "desconocida"
    if slot_id == 459695:
        slot = "Priest Racial Ability"
    return slot, slot, None


def build_plan(catalog, stored_equivalences, implemented_ids, spells_by_name):
    stored_by_id = {
        item.get("taught_spell_id"): item for item in stored_equivalences
    }
    plan = []
    for rune in catalog:
        spell_id = rune.get("taught_spell_id")
        slot_id = rune.get("slot_id")
        category = category_for_slot(slot_id)
        class_name = rune.get("clase") or "desconocida"
        slot, slot_name, slot_name_en = slot_labels(rune, category)
        implemented = spell_id in implemented_ids if category == "runa" else None
        redundant = False
        templates = []

        if category == "runa":
            rune_type, templates = infer_equivalence(
                rune, stored_by_id, spells_by_name
            )
            redundant = rune_type == "activo" and bool(templates)
            if redundant:
                level = "R"
                reason = (
                    "Tiene un hechizo WotLK con el mismo nombre exacto; se marca como "
                    "redundante para decisión del usuario."
                )
            else:
                level, reason = classify(rune, rune_type)
        elif category == "alma":
            rune_type = "sin_equivalente"
            level, reason = classify(rune, rune_type)
        elif category == "racial":
            rune_type = "sin_clasificar"
            level = None
            reason = "El slot_id {} identifica una ranura racial, fuera del sistema de grabado de runas.".format(slot_id)
        else:
            rune_type = "sin_clasificar"
            level = None
            reason = "El slot_id {} no corresponde a una ranura de grabado ni a Soul Engraving.".format(slot_id)

        plan.append({
            "taught_spell_id": spell_id,
            "name_en": rune.get("name_en"),
            "clase": class_name,
            "categoria": category,
            "slot_id": slot_id,
            "slot": slot,
            "ranura": slot_name,
            "ranura_en": slot_name_en,
            "tipo": rune_type,
            "nivel": level,
            "implementada": implemented,
            "redundante_wotlk": redundant,
            "razon": reason,
            "riesgo_hueco": rune_type == "talento" and level in {"P", "T"},
            "plantilla_wotlk": templates,
        })

    plan.sort(key=lambda item: (
        CATEGORY_ORDER[item["categoria"]],
        LEVEL_ORDER[item["nivel"]],
        CLASS_NAMES.get(item["clase"], item["clase"] or ""),
        SLOT_ORDER.get(item["slot_id"], 99),
        item["slot"],
        (item["name_en"] or "").casefold(),
        item["taught_spell_id"] or 0,
    ))
    return plan


def escape_cell(value):
    return str(value if value not in (None, "") else "—").replace("|", "\\|").replace("\n", " ")


def pending_rows(plan):
    return [
        item for item in plan
        if item["categoria"] == "runa" and not item["implementada"]
    ]


def ordered_classes(plan):
    names = {item["clase"] for item in plan}
    return sorted(names, key=lambda name: (
        name == "desconocida", CLASS_NAMES.get(name, name)
    ))


def category_counts(plan):
    return Counter(item["categoria"] for item in plan)


def level_counts(rows, fallback="sin_clasificar"):
    return Counter(item["nivel"] or fallback for item in rows)


def markdown_report(plan):
    """Render category, slot, class and pending implementation summaries."""
    runes = [item for item in plan if item["categoria"] == "runa"]
    souls = [item for item in plan if item["categoria"] == "alma"]
    racial = [item for item in plan if item["categoria"] == "racial"]
    noise = [item for item in plan if item["categoria"] == "ruido"]
    pending = [item for item in runes if not item["implementada"]]
    pending_levels = level_counts(pending)
    soul_levels = level_counts(souls)
    classes = ordered_classes(plan)
    by_slot_class = Counter((item["slot_id"], item["clase"]) for item in runes)
    by_slot_state = defaultdict(Counter)
    by_class_category = Counter((item["clase"], item["categoria"]) for item in plan)
    for item in runes:
        state = "implementadas" if item["implementada"] else "pendientes"
        by_slot_state[item["slot_id"]][state] += 1

    lines = [
        "# Plan de implementación de runas de SoD",
        "",
        "El catálogo contiene runas de grabado, almas de la temporada final y hechizos "
        "sueltos que no son runas. La categoría se determina por `slot_id`; no se deducen fases.",
        "",
        "P = pasiva sencilla; T = proc o disparo; C = requiere C++ o no encaja en las reglas; "
        "R = hechizo activo redundante por nombre exacto en WotLK. La clasificación P/T/C/R "
        "se aplica solo a runas; las almas usan P/T/C, sin R.",
        "",
        "## Totales por categoría",
        "",
        "| Categoría | Total | Implementadas | Pendientes |",
        "|---|---:|---:|---:|",
    ]
    totals = category_counts(plan)
    lines.append("| Runa | {} | {} | {} |".format(
        totals["runa"], sum(item["implementada"] for item in runes), len(pending)
    ))
    lines.append("| Alma | {} | — | — |".format(totals["alma"]))
    lines.append("| Racial | {} | — | — |".format(totals["racial"]))
    lines.append("| Ruido | {} | — | — |".format(totals["ruido"]))
    lines.append("| **Total** | **{}** | — | — |".format(len(plan)))

    lines.extend([
        "",
        "## Runas por ranura y clase",
        "",
        "| Ranura | " + " | ".join(CLASS_NAMES[name] for name in classes if name != "desconocida") + " | Total |",
        "|---|" + "---:|" * (len(classes) - ("desconocida" in classes) + 1),
    ])
    rune_classes = [name for name in classes if name != "desconocida"]
    for slot_id, (slot_en, slot_es) in ENGRAVING_SLOTS.items():
        values = [by_slot_class[(slot_id, class_name)] for class_name in rune_classes]
        lines.append("| {} ({}) | {} | {} |".format(
            slot_es, slot_en, " | ".join(str(value) for value in values), sum(values)
        ))
    lines.append("| **Total** | {} | {} |".format(
        " | ".join(str(sum(by_slot_class[(slot_id, name)] for slot_id in ENGRAVING_SLOTS))
                   for name in rune_classes), len(runes)
    ))

    lines.extend([
        "",
        "## Implementadas y pendientes por ranura",
        "",
        "| Ranura | Implementadas | Pendientes | Total |",
        "|---|---:|---:|---:|",
    ])
    for slot_id, (_, slot_es) in ENGRAVING_SLOTS.items():
        counts = by_slot_state[slot_id]
        lines.append("| {} | {} | {} | {} |".format(
            slot_es, counts["implementadas"], counts["pendientes"],
            counts["implementadas"] + counts["pendientes"],
        ))

    lines.extend([
        "",
        "## Runas pendientes por nivel",
        "",
        "| Nivel | Runas pendientes |",
        "|---|---:|",
    ])
    for level, label in (("P", "P — Pasiva"), ("T", "T — Proc o disparo"),
                         ("C", "C — Requiere C++"), ("R", "R — Redundante en WotLK")):
        lines.append("| {} | {} |".format(label, pending_levels[level]))

    lines.extend([
        "",
        "## Resumen por clase y categoría",
        "",
        "| Clase | Runas | Almas | Raciales | Ruido |",
        "|---|---:|---:|---:|---:|",
    ])
    for class_name in classes:
        lines.append("| {} | {} | {} | {} | {} |".format(
            CLASS_NAMES.get(class_name, class_name),
            by_class_category[(class_name, "runa")],
            by_class_category[(class_name, "alma")],
            by_class_category[(class_name, "racial")],
            by_class_category[(class_name, "ruido")],
        ))

    lines.extend([
        "",
        "## Almas por nivel (sin R)",
        "",
        "| Nivel | Almas |",
        "|---|---:|",
    ])
    for level, label in (("P", "P — Pasiva"), ("T", "T — Proc o disparo"),
                         ("C", "C — Requiere C++"), ("sin_clasificar", "Sin clasificar")):
        lines.append("| {} | {} |".format(label, soul_levels[level]))

    for class_name in rune_classes:
        rows = [item for item in pending if item["clase"] == class_name]
        lines.extend([
            "",
            "## {}: runas pendientes ({})".format(CLASS_NAMES[class_name], len(rows)),
            "",
            "| ID | Nombre | Ranura | Tipo | Nivel | Razón |",
            "|---:|---|---|---|---|---|",
        ])
        for item in rows:
            lines.append("| {} | {} | {} | {} | {} | {} |".format(
                escape_cell(item["taught_spell_id"]), escape_cell(item["name_en"]),
                escape_cell(item["ranura"]), TYPE_NAMES.get(item["tipo"], item["tipo"]),
                escape_cell(item["nivel"]), escape_cell(item["razon"]),
            ))

    lines.extend([
        "",
        "## Raciales y ruido (sin clasificar)",
        "",
        "- **Raciales ({}, slot_id {}):** fuera del sistema de grabado de runas; no se les asigna nivel.".format(
            len(racial), " y ".join(str(slot_id) for slot_id in sorted(RACIAL_SLOT_IDS))
        ),
        "- **Ruido ({}):** `slot_id` ajeno a las ocho ranuras y a Soul Engraving; no se les asigna nivel.".format(len(noise)),
    ])
    return "\n".join(lines) + "\n"


def summary_report(plan):
    """Render compact category, slot, class and level totals."""
    runes = [item for item in plan if item["categoria"] == "runa"]
    souls = [item for item in plan if item["categoria"] == "alma"]
    pending = [item for item in runes if not item["implementada"]]
    totals = category_counts(plan)
    pending_levels = level_counts(pending)
    soul_levels = level_counts(souls)
    by_slot = Counter(item["slot_id"] for item in runes)
    by_class_category = Counter((item["clase"], item["categoria"]) for item in plan)
    classes = ordered_classes(plan)

    lines = [
        "# Resumen del plan de runas de SoD",
        "",
        "## Totales por categoría",
        "",
        "| Runa | Alma | Racial | Ruido | Total |",
        "|---:|---:|---:|---:|---:|",
        "| {} | {} | {} | {} | {} |".format(
            totals["runa"], totals["alma"], totals["racial"], totals["ruido"], len(plan)
        ),
        "",
        "## Runas por ranura",
        "",
        "| Ranura | Runas | Implementadas | Pendientes |",
        "|---|---:|---:|---:|",
    ]
    for slot_id, (slot_en, slot_es) in ENGRAVING_SLOTS.items():
        slot_rows = [item for item in runes if item["slot_id"] == slot_id]
        implemented = sum(item["implementada"] for item in slot_rows)
        lines.append("| {} ({}) | {} | {} | {} |".format(
            slot_es, slot_en, by_slot[slot_id], implemented, len(slot_rows) - implemented
        ))

    lines.extend([
        "",
        "## Pendientes de runa por nivel",
        "",
        "| P | T | C | R | Total |",
        "|---:|---:|---:|---:|---:|",
        "| {} | {} | {} | {} | {} |".format(
            pending_levels["P"], pending_levels["T"], pending_levels["C"],
            pending_levels["R"], len(pending),
        ),
        "",
        "## Totales por clase y categoría",
        "",
        "| Clase | Runas | Almas | Raciales | Ruido |",
        "|---|---:|---:|---:|---:|",
    ])
    for class_name in classes:
        lines.append("| {} | {} | {} | {} | {} |".format(
            CLASS_NAMES.get(class_name, class_name),
            by_class_category[(class_name, "runa")],
            by_class_category[(class_name, "alma")],
            by_class_category[(class_name, "racial")],
            by_class_category[(class_name, "ruido")],
        ))

    lines.extend([
        "",
        "## Almas por nivel (sin R)",
        "",
        "| P | T | C | Sin clasificar | Total |",
        "|---:|---:|---:|---:|---:|",
        "| {} | {} | {} | {} | {} |".format(
            soul_levels["P"], soul_levels["T"], soul_levels["C"],
            soul_levels["sin_clasificar"], len(souls),
        ),
    ])
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

    totals = Counter(
        item["nivel"] if item["nivel"] else "sin_clasificar"
        for item in pending_rows(plan)
    )
    implemented = sum(
        item["categoria"] == "runa" and item["implementada"] for item in plan
    )
    print("Filas del catálogo: {}".format(len(plan)))
    print("Runas de grabado: {}".format(sum(item["categoria"] == "runa" for item in plan)))
    print("Runas implementadas: {}".format(implemented))
    print("Pendientes por nivel: {}".format(dict(sorted(totals.items()))))


if __name__ == "__main__":
    main()
