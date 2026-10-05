#!/usr/bin/env python3
"""Download and summarize the Classic Era Season of Discovery rune catalog."""

import argparse
import csv
import io
import json
import sys
from collections import defaultdict
from datetime import date
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import quote
from urllib.request import Request, urlopen


ROOT = Path(__file__).resolve().parents[2]
CACHE_ROOT = ROOT / "datos" / "wago"
DOCS_ROOT = ROOT / "docs" / "runas"
USER_AGENT = "Mozilla/5.0"
PHASE_ONE_SLOTS = {399954: "Chest", 399966: "Legs", 399967: "Hands"}
SLOT_ORDER = {"Chest": 0, "Legs": 1, "Hands": 2}
CLASS_BY_SET = {
    3: "mage", 4: "warrior", 5: "warlock", 6: "priest", 7: "druid",
    8: "rogue", 9: "hunter", 10: "paladin", 11: "shaman", 15: "deathknight",
}
CLASS_BY_MASK_BIT = {
    0: "warrior", 1: "paladin", 2: "hunter", 3: "rogue", 4: "priest",
    5: "deathknight", 6: "shaman", 7: "mage", 8: "warlock", 10: "druid",
}
CLASSES = (
    "mage", "rogue", "priest", "warrior", "warlock", "druid",
    "paladin", "shaman", "hunter", "deathknight", "desconocida",
)
EFFECT_FIELDS = (
    ("EffectIndex", "effect_index"), ("Effect", "effect"),
    ("EffectAura", "effect_aura"), ("EffectBasePoints", "effect_base_points"),
    ("EffectBonusCoefficient", "effect_bonus_coefficient"),
    ("Coefficient", "coefficient"), ("EffectTriggerSpell", "effect_trigger_spell"),
    ("EffectMiscValue_0", "effect_misc_value_0"),
    ("EffectMiscValue_1", "effect_misc_value_1"),
    ("ImplicitTarget_0", "implicit_target_0"),
    ("ImplicitTarget_1", "implicit_target_1"),
    ("EffectSpellClassMask_0", "effect_spell_class_mask_0"),
    ("EffectSpellClassMask_1", "effect_spell_class_mask_1"),
    ("EffectSpellClassMask_2", "effect_spell_class_mask_2"),
    ("EffectSpellClassMask_3", "effect_spell_class_mask_3"),
    ("EffectAuraPeriod", "effect_aura_period"),
    ("EffectChainTargets", "effect_chain_targets"),
)


def number(value):
    """Convert CSV numbers while preserving non-numeric values as null."""
    if value is None or value == "":
        return None
    try:
        parsed = float(value)
        return int(parsed) if parsed.is_integer() else parsed
    except (TypeError, ValueError):
        return None


def get_build():
    request = Request("https://wago.tools/api/builds", headers={"User-Agent": USER_AGENT})
    with urlopen(request, timeout=120) as response:
        payload = json.loads(response.read().decode("utf-8"))
    builds = payload["wow_classic_era"]
    if not builds or not isinstance(builds[0], dict) or not builds[0].get("version"):
        raise ValueError("La API no devolvió una versión de wow_classic_era.")
    return builds[0]["version"]


def download_table(build, table, locale):
    cache_path = CACHE_ROOT / build / (table + "." + locale + ".csv")
    if not cache_path.exists():
        url = "https://wago.tools/db2/{}/csv?build={}&locale={}".format(
            quote(table), quote(build), quote(locale)
        )
        request = Request(url, headers={"User-Agent": USER_AGENT})
        try:
            with urlopen(request, timeout=180) as response:
                content = response.read()
        except (HTTPError, URLError, TimeoutError) as error:
            raise RuntimeError("No se pudo descargar {} ({}): {}".format(table, locale, error)) from error
        cache_path.parent.mkdir(parents=True, exist_ok=True)
        cache_path.write_bytes(content)
    text = cache_path.read_text(encoding="utf-8-sig")
    reader = csv.DictReader(io.StringIO(text))
    if not reader.fieldnames:
        raise ValueError("CSV vacío o sin cabecera: {}".format(cache_path))
    return list(reader), set(reader.fieldnames)


def load_tables(build):
    requests = [
        ("SpellEffect", "enUS"), ("SpellClassOptions", "enUS"),
        ("SkillLineAbility", "enUS"), ("SkillRaceClassInfo", "enUS"),
        ("SpellName", "enUS"), ("SpellName", "esES"),
        ("Spell", "enUS"), ("Spell", "esES"), ("SpellMisc", "enUS"),
        ("SpellPower", "enUS"), ("SpellCooldowns", "enUS"),
        ("SpellLevels", "enUS"), ("SpellAuraOptions", "enUS"),
        ("SpellCastTimes", "enUS"), ("SpellDuration", "enUS"),
        ("SpellRange", "enUS"),
    ]
    tables = {}
    headers = {}
    for table, locale in requests:
        rows, columns = download_table(build, table, locale)
        tables[(table, locale)] = rows
        headers[(table, locale)] = columns
        print("Descargado/cacheado {}.{}: {} filas".format(table, locale, len(rows)))
    return tables, headers


def index_rows(rows, key):
    indexed = {}
    for row in rows:
        item_id = number(row.get(key))
        if item_id is not None:
            indexed.setdefault(item_id, []).append(row)
    return indexed


def index_spell_rows(rows, columns):
    """Index spell tables by SpellID when present, otherwise their ID key."""
    return index_rows(rows, "SpellID" if "SpellID" in columns else "ID")


def first_row(index, item_id):
    rows = index.get(item_id, [])
    return rows[0] if rows else {}


def localized(index, item_id, column):
    return first_row(index, item_id).get(column) or None


def resolve_index(index, item_id, output_column):
    row = first_row(index, item_id)
    return number(row.get(output_column))


def class_from_mask(mask):
    value = number(mask)
    if value is None or value < 0:
        return None
    matches = {name for bit, name in CLASS_BY_MASK_BIT.items() if int(value) & (1 << bit)}
    return next(iter(matches)) if len(matches) == 1 else None


def skill_class(taught_id, learn_id, line_abilities, skill_rows):
    for spell_id in (taught_id, learn_id):
        classes = set()
        for ability in line_abilities.get(spell_id, []):
            skill_id = number(ability.get("SkillLine"))
            for skill in skill_rows.get(skill_id, []):
                class_name = class_from_mask(skill.get("ClassMask"))
                if class_name:
                    classes.add(class_name)
        if len(classes) == 1:
            return next(iter(classes))
        if len(classes) > 1:
            return None
    return None


def slot_sort_key(slot):
    if slot in SLOT_ORDER:
        return SLOT_ORDER[slot]
    suffix = slot.partition("_")[2]
    return 3 + (number(suffix) or 0)


# SpellClassSet misattributes these; reason in the value. "probable" = no second source.
CLASS_OVERRIDES = {
    415813: ("shaman", "Ghost Wolf is a shaman ability"),
    409324: ("shaman", "text mentions Flame Shock; SkillRaceClassInfo says shaman"),
    425609: ("paladin", "SkillRaceClassInfo says paladin; Rebuke is a paladin interrupt"),
    408307: ("shaman", "probable: text scales with Nature spell damage; no second source"),
}


def build_catalog(build, generated, tables, headers):
    spell_effects = tables[("SpellEffect", "enUS")]
    spell_class = index_spell_rows(tables[("SpellClassOptions", "enUS")], headers[("SpellClassOptions", "enUS")])
    skill_abilities = index_rows(tables[("SkillLineAbility", "enUS")], "Spell")
    skill_classes = index_rows(tables[("SkillRaceClassInfo", "enUS")], "SkillID")
    names_en = index_rows(tables[("SpellName", "enUS")], "ID")
    names_es = index_rows(tables[("SpellName", "esES")], "ID")
    spell_en = index_rows(tables[("Spell", "enUS")], "ID")
    spell_es = index_rows(tables[("Spell", "esES")], "ID")
    misc = index_spell_rows(tables[("SpellMisc", "enUS")], headers[("SpellMisc", "enUS")])
    power = index_spell_rows(tables[("SpellPower", "enUS")], headers[("SpellPower", "enUS")])
    cooldowns = index_spell_rows(tables[("SpellCooldowns", "enUS")], headers[("SpellCooldowns", "enUS")])
    levels = index_spell_rows(tables[("SpellLevels", "enUS")], headers[("SpellLevels", "enUS")])
    aura_options = index_spell_rows(tables[("SpellAuraOptions", "enUS")], headers[("SpellAuraOptions", "enUS")])
    cast_times = index_rows(tables[("SpellCastTimes", "enUS")], "ID")
    durations = index_rows(tables[("SpellDuration", "enUS")], "ID")
    ranges = index_rows(tables[("SpellRange", "enUS")], "ID")

    effects_by_spell = defaultdict(list)
    for row in spell_effects:
        spell_id = number(row.get("SpellID"))
        if spell_id is not None:
            effects_by_spell[spell_id].append(row)

    missing = []
    expected_columns = {
        ("SpellEffect", "enUS"): {"SpellID", "EffectIndex", "EffectAura", "EffectBasePoints", "EffectMiscValue_0"},
        ("SpellClassOptions", "enUS"): {"SpellClassSet"},
        ("SkillLineAbility", "enUS"): {"Spell", "SkillLine"},
        ("SkillRaceClassInfo", "enUS"): {"SkillID", "ClassMask"},
        ("SpellName", "enUS"): {"ID", "Name_lang"},
        ("SpellName", "esES"): {"ID", "Name_lang"},
        ("Spell", "enUS"): {"ID", "Description_lang", "AuraDescription_lang"},
        ("Spell", "esES"): {"ID", "Description_lang", "AuraDescription_lang"},
        ("SpellMisc", "enUS"): {"CastingTimeIndex", "DurationIndex", "RangeIndex", "SchoolMask", "SpellIconFileDataID"},
        ("SpellPower", "enUS"): {"ManaCost", "PowerCostPct", "PowerType"},
        ("SpellCooldowns", "enUS"): {"RecoveryTime", "CategoryRecoveryTime"},
        ("SpellLevels", "enUS"): {"BaseLevel", "SpellLevel"},
        ("SpellAuraOptions", "enUS"): {"ProcChance", "ProcCharges"},
        ("SpellCastTimes", "enUS"): {"ID", "Base"},
        ("SpellDuration", "enUS"): {"ID", "Duration"},
        ("SpellRange", "enUS"): {"ID", "RangeMax_0"},
    }
    for key, expected in expected_columns.items():
        absent = sorted(expected - headers[key])
        if key[0] in {"SpellClassOptions", "SpellMisc", "SpellPower", "SpellCooldowns", "SpellLevels", "SpellAuraOptions"} and not ({"SpellID", "ID"} & headers[key]):
            absent.append("SpellID o ID")
        if absent:
            missing.append("{}.{}: {}".format(key[0], key[1], ", ".join(absent)))

    runes = []
    for learn_effect in spell_effects:
        if number(learn_effect.get("EffectAura")) != 332:
            continue
        learn_id = number(learn_effect.get("SpellID"))
        taught_id = number(learn_effect.get("EffectBasePoints"))
        slot_id = number(learn_effect.get("EffectMiscValue_0"))
        if learn_id is None:
            continue
        slot = PHASE_ONE_SLOTS.get(slot_id, "slot_{}".format(slot_id) if slot_id is not None else "slot_null")
        class_row = first_row(spell_class, taught_id)
        if not class_row:
            class_row = first_row(spell_class, learn_id)
        class_set = number(class_row.get("SpellClassSet"))
        source_class = CLASS_BY_SET.get(class_set)
        rune_class = source_class or "desconocida"
        checked_class = skill_class(taught_id, learn_id, skill_abilities, skill_classes)
        effects = []
        for effect in effects_by_spell.get(taught_id, []):
            effects.append({target: number(effect.get(source)) for source, target in EFFECT_FIELDS})
        misc_row = first_row(misc, taught_id)
        power_row = first_row(power, taught_id)
        cooldown_row = first_row(cooldowns, taught_id)
        level_row = first_row(levels, taught_id)
        aura_row = first_row(aura_options, taught_id)
        casting_index = number(misc_row.get("CastingTimeIndex"))
        duration_index = number(misc_row.get("DurationIndex"))
        range_index = number(misc_row.get("RangeIndex"))
        desc_en = localized(spell_en, taught_id, "Description_lang")
        desc_es = localized(spell_es, taught_id, "Description_lang")
        aura_en = localized(spell_en, taught_id, "AuraDescription_lang")
        aura_es = localized(spell_es, taught_id, "AuraDescription_lang")
        runes.append({
            "learn_spell_id": learn_id,
            "learn_spell_name": localized(names_en, learn_id, "Name_lang"),
            "taught_spell_id": taught_id,
            "name_en": localized(names_en, taught_id, "Name_lang"),
            "name_es": localized(names_es, taught_id, "Name_lang"),
            "clase": CLASS_OVERRIDES.get(taught_id, (rune_class,))[0],
            "class_source": "override" if taught_id in CLASS_OVERRIDES else "SpellClassOptions",
            "class_override_reason": CLASS_OVERRIDES[taught_id][1] if taught_id in CLASS_OVERRIDES else None,
            "class_skill_check": checked_class,
            "class_conflict": bool(source_class and checked_class and source_class != checked_class),
            "slot": slot,
            "slot_id": slot_id,
            "desc_en": desc_en,
            "desc_es": desc_es,
            "aura_en": aura_en,
            "aura_es": aura_es,
            "cast_ms": resolve_index(cast_times, casting_index, "Base"),
            "duration_ms": resolve_index(durations, duration_index, "Duration"),
            "range_yd": resolve_index(ranges, range_index, "RangeMax_0"),
            "school_mask": number(misc_row.get("SchoolMask")),
            "spell_icon_file_data_id": number(misc_row.get("SpellIconFileDataID")),
            "power_type": number(power_row.get("PowerType")),
            "mana_cost": number(power_row.get("ManaCost")),
            "mana_pct": number(power_row.get("PowerCostPct")),
            "cooldown_ms": number(cooldown_row.get("RecoveryTime")),
            "category_cd_ms": number(cooldown_row.get("CategoryRecoveryTime")),
            "base_level": number(level_row.get("BaseLevel")),
            "spell_level": number(level_row.get("SpellLevel")),
            "proc_chance": number(aura_row.get("ProcChance")),
            "proc_charges": number(aura_row.get("ProcCharges")),
            "effects": effects,
        })
    runes.sort(key=lambda rune: (
        (rune["clase"] or "").lower(), slot_sort_key(rune["slot"]),
        (rune["name_en"] or rune["name_es"] or "").lower(),
        rune["taught_spell_id"] or 0, rune["learn_spell_id"],
    ))
    return {"build": build, "generado": generated, "runas": runes}, missing


def format_time(milliseconds):
    if milliseconds is None:
        return "—"
    return "{} s".format(milliseconds // 1000) if milliseconds % 1000 == 0 else "{} ms".format(milliseconds)


def format_cost(rune):
    cost = rune["mana_cost"]
    pct = rune["mana_pct"]
    parts = []
    if cost not in (None, 0):
        parts.append(str(cost))
    if pct not in (None, 0):
        parts.append("{}%".format(pct))
    return " / ".join(parts) if parts else "—"


def markdown_cell(value):
    return str(value or "—").replace("|", "\\|").replace("\n", " ").replace("\r", " ")


def write_class_pages(catalog):
    DOCS_ROOT.mkdir(parents=True, exist_ok=True)
    runes = catalog["runas"]
    for class_name in CLASSES:
        class_runes = [rune for rune in runes if rune["clase"] == class_name and rune["slot"] in SLOT_ORDER]
        lines = [
            "# Runas de {}".format(class_name.capitalize()), "",
            "Build consultada: `{}`. Fecha de generación: {}.".format(catalog["build"], catalog["generado"]), "",
            "Estos datos corresponden a la build moderna y no están escalados a 3.3.5a.", "",
        ]
        for slot in ("Chest", "Legs", "Hands"):
            slot_runes = [rune for rune in class_runes if rune["slot"] == slot]
            grouped = {}
            for rune in slot_runes:
                key = (rune["name_es"] or "", rune["name_en"] or "")
                grouped.setdefault(key, []).append(rune)
            lines.extend(["## {}".format(slot), "", "| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |", "|---|---|---|---:|---:|---:|:---:|"])
            for key, group in sorted(grouped.items(), key=lambda item: ((item[0][0] or item[0][1]).lower(), item[1][0]["taught_spell_id"] or 0)):
                first = group[0]
                label = "{} / {}".format(key[0] or "—", key[1] or "—")
                taught = ", ".join(str(rune["taught_spell_id"]) for rune in group if rune["taught_spell_id"] is not None) or "—"
                description = (first["desc_en"] or "—")[:220]
                conflict = "sí" if any(rune["class_conflict"] for rune in group) else "no"
                lines.append("| {} | {} | {} | {} | {} | {} | {} |".format(
                    markdown_cell(label), markdown_cell(taught), markdown_cell(description),
                    format_cost(first), format_time(first["cooldown_ms"]),
                    format_time(first["cast_ms"]), conflict,
                ))
            lines.append("")
        (DOCS_ROOT / (class_name + ".md")).write_text("\n".join(lines).rstrip() + "\n", encoding="utf-8")


def report(catalog, missing):
    counts = defaultdict(int)
    for rune in catalog["runas"]:
        if rune["slot"] in SLOT_ORDER:
            counts[(rune["clase"], rune["slot"])] += 1
    print("\nResumen de runas de fase 1 (clase / ranura):")
    for class_name in CLASSES:
        parts = ["{}={}".format(slot, counts[(class_name, slot)]) for slot in ("Chest", "Legs", "Hands")]
        print("  {}: {}".format(class_name, ", ".join(parts)))
    conflicts = [rune for rune in catalog["runas"] if rune["class_conflict"]]
    print("\nConflictos de clase: {}".format(len(conflicts)))
    for rune in conflicts:
        print("  {} ({}) taught={} skill={}".format(
            rune["name_en"] or "(sin nombre)", rune["clase"],
            rune["taught_spell_id"], rune["class_skill_check"],
        ))
    if missing:
        print("\nColumnas no disponibles (sus campos quedan null):")
        for item in missing:
            print("  " + item)


def main():
    parser = argparse.ArgumentParser(description="Extrae el catálogo de runas SoD desde wago.tools.")
    parser.add_argument("--build", help="Versión de build; por defecto usa la última de wow_classic_era.")
    args = parser.parse_args()
    try:
        build = args.build or get_build()
        print("Build: {}".format(build))
        tables, headers = load_tables(build)
        generated = date.today().isoformat()
        catalog, missing = build_catalog(build, generated, tables, headers)
        DOCS_ROOT.mkdir(parents=True, exist_ok=True)
        (DOCS_ROOT / "catalogo-sod.json").write_text(
            json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
        )
        write_class_pages(catalog)
        report(catalog, missing)
        print("\nGenerados {} registros en {}".format(len(catalog["runas"]), DOCS_ROOT))
    except (HTTPError, URLError, TimeoutError, RuntimeError, ValueError, KeyError) as error:
        print("Error: {}".format(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
