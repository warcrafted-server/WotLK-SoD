#!/usr/bin/env python3
"""Classify unimplemented phase-one runes by implementation difficulty."""

import json
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
CATALOG_PATH = ROOT / "docs" / "runas" / "catalogo-sod.json"
EQUIVALENCES_PATH = ROOT / "docs" / "runas" / "equivalencias-wotlk.json"
JSON_PATH = ROOT / "docs" / "runas" / "plan-implementacion.json"
MARKDOWN_PATH = ROOT / "docs" / "runas" / "plan-implementacion.md"
PHASE_ONE_SLOTS = {"Chest", "Legs", "Hands"}
SLOT_ORDER = {"Chest": 0, "Legs": 1, "Hands": 2}
IMPLEMENTED_IDS = {
    400647, 412286, 425121, 400640, 401417, 412510, 400735, 401462,
    401556, 425124, 400574, 412324, 412326, 412325, 900003, 900006,
    403629, 403501, 403195, 407778, 407669, 407624, 407676, 409433,
    399956, 401946, 402174, 408514, 408507, 408120,
}
TRIGGER_AURAS = {4, 226, 231, 232, 23, 24}
FORBIDDEN_PASSIVE_AURAS = {4, 226, 231, 232}
CLASS_NAMES = {
    "druid": "Druida", "hunter": "Cazador", "mage": "Mago",
    "paladin": "Paladín", "priest": "Sacerdote", "rogue": "Pícaro",
    "shaman": "Chamán", "warlock": "Brujo", "warrior": "Guerrero",
    "deathknight": "Caballero de la Muerte", "desconocida": "Desconocida",
}
SLOT_NAMES = {"Chest": "Pecho", "Legs": "Piernas", "Hands": "Manos"}
TYPE_NAMES = {"talento": "Talento", "sin_equivalente": "Sin equivalente"}

# Nivel | Regla (se evalúan en este orden)
# C | DUMMY, aura DUMMY, descriptores complejos, activa nueva o caso sin clasificar.
# T | Proc, hechizo disparado o aura de proc/activación.
# P | Tiene aura; sin disparadores, DUMMY, auras periódicas, lanzamiento ni CD.


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
    """Return the highest WotLK template spell id when the match has one."""
    highest = equivalence.get("rango_mas_alto")
    spell_id = highest.get("id") if isinstance(highest, dict) else None
    return [spell_id] if spell_id is not None else []


def build_plan(catalog, equivalences):
    runes_by_id = {}
    for rune in catalog:
        if rune.get("slot") in PHASE_ONE_SLOTS:
            runes_by_id.setdefault(rune.get("taught_spell_id"), rune)

    plan = []
    seen = set()
    for equivalence in equivalences:
        spell_id = equivalence.get("taught_spell_id")
        rune_type = equivalence.get("tipo")
        if rune_type not in {"talento", "sin_equivalente"}:
            continue
        if spell_id in IMPLEMENTED_IDS or spell_id in seen:
            continue
        rune = runes_by_id.get(spell_id)
        if rune is None:
            continue
        seen.add(spell_id)
        level, reason = classify(rune, rune_type)
        plan.append({
            "taught_spell_id": spell_id,
            "name_en": rune.get("name_en"),
            "clase": rune.get("clase"),
            "slot": rune.get("slot"),
            "tipo": rune_type,
            "nivel": level,
            "razon": reason,
            "riesgo_hueco": rune_type == "talento" and level in {"P", "T"},
            "plantilla_wotlk": template_ids(equivalence),
        })

    plan.sort(key=lambda item: (
        "PTC".index(item["nivel"]), item["clase"] or "",
        SLOT_ORDER.get(item["slot"], 99), item["name_en"] or "",
        item["taught_spell_id"],
    ))
    return plan


def markdown_report(plan):
    """Render the grouped implementation plan in Spanish."""
    counts_by_level = Counter(item["nivel"] for item in plan)
    classes_by_level = defaultdict(Counter)
    for item in plan:
        classes_by_level[item["nivel"]][item["clase"]] += 1

    lines = [
        "# Plan de implementación de runas de fase 1",
        "",
        "Se incluyen runas de tipo talento y sin equivalente que aún no están implementadas. "
        "Las runas activas ya disponibles en WotLK quedan fuera del plan.",
        "",
        "## Resumen por nivel",
        "",
        "| Nivel | Runas |",
        "|---|---:|",
    ]
    for level, label in (("P", "P — Pasiva"), ("T", "T — Proc o trigger"), ("C", "C — Requiere C++")):
        lines.append("| {} | {} |".format(label, counts_by_level[level]))
    lines.extend([
        "",
        "## Resumen por clase",
        "",
        "| Clase | P | T | C | Total |",
        "|---|---:|---:|---:|---:|",
    ])
    classes = sorted(
        {item["clase"] for item in plan},
        key=lambda name: CLASS_NAMES.get(name, name or ""),
    )
    for class_name in classes:
        counts = [classes_by_level[level][class_name] for level in "PTC"]
        lines.append("| {} | {} | {} | {} | {} |".format(
            CLASS_NAMES.get(class_name, class_name), *counts, sum(counts)
        ))
    lines.append("| **Total** | {} | {} | {} | {} |".format(
        *(counts_by_level[level] for level in "PTC"), len(plan)
    ))
    lines.extend([
        "",
        "Los casos que no encajan en las reglas simples se asignan a C por prudencia.",
    ])

    for level, label in (("P", "P — Pasivas"), ("T", "T — Proc o trigger"), ("C", "C — Requiere C++")):
        lines.extend([
            "",
            "## {} ({})".format(label, counts_by_level[level]),
            "",
            "| Clase | Runa | Ranura | Tipo | Razón |",
            "|---|---|---|---|---|",
        ])
        for item in (entry for entry in plan if entry["nivel"] == level):
            lines.append("| {} | {} | {} | {} | {} |".format(
                CLASS_NAMES.get(item["clase"], item["clase"]),
                item["name_en"], SLOT_NAMES.get(item["slot"], item["slot"]),
                TYPE_NAMES[item["tipo"]], item["razon"],
            ))
    return "\n".join(lines) + "\n"


def main():
    catalog = json.loads(CATALOG_PATH.read_text(encoding="utf-8"))["runas"]
    equivalences = json.loads(EQUIVALENCES_PATH.read_text(encoding="utf-8"))
    plan = build_plan(catalog, equivalences)
    JSON_PATH.write_text(
        json.dumps(plan, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    MARKDOWN_PATH.write_text(markdown_report(plan), encoding="utf-8")
    print("Runas clasificadas: {}".format(len(plan)))


if __name__ == "__main__":
    main()
