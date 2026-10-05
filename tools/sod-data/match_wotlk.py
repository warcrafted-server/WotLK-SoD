#!/usr/bin/env python3
"""Match phase-one SoD runes to WotLK spells by exact English name."""

import json
import sys
from collections import Counter, defaultdict
from pathlib import Path


sys.dont_write_bytecode = True

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "sod-client"))
import sod_dbc


CATALOG_PATH = ROOT / "docs" / "runas" / "catalogo-sod.json"
JSON_PATH = ROOT / "docs" / "runas" / "equivalencias-wotlk.json"
MARKDOWN_PATH = ROOT / "docs" / "runas" / "equivalencias-wotlk.md"
DBC_ROOT = Path("/home/stark/Servers/acore-test/data/dbc")
SPELL_SQL = Path("/home/stark/Repos/acore-test/data/sql/base/db_world/spell_dbc.sql")
PHASE_ONE_SLOTS = {"Chest": 0, "Legs": 1, "Hands": 2}
SPELL_FIELDS = (
    "ID", "Name_Lang_enUS", "NameSubtext_Lang_enUS", "Attributes",
    "SpellLevel", "BaseLevel", "MaxLevel", "SpellClassSet",
    "DurationIndex", "CastingTimeIndex", "PowerType", "ManaCost",
    "ManaCostPct", "RecoveryTime",
    "Effect_1", "Effect_2", "Effect_3",
    "EffectAura_1", "EffectAura_2", "EffectAura_3",
    "EffectTriggerSpell_1", "EffectTriggerSpell_2", "EffectTriggerSpell_3",
)


def dbc_string(dbc, offset):
    """Read a null-terminated UTF-8 string from a DBC string block."""
    if offset < 0 or offset >= len(dbc.strings):
        return None
    end = dbc.strings.find(b"\0", offset)
    if end < 0:
        return None
    try:
        return bytes(dbc.strings[offset:end]).decode("utf-8")
    except UnicodeDecodeError:
        return None


def skill_line_names(dbc):
    """Map SkillLine ids to their enUS display names."""
    names = {}
    for record in dbc.records:
        line_id = dbc.get_int(record, 0)
        names[line_id] = dbc_string(dbc, dbc.get_int(record, 3))
    return names


def load_talents(dbc):
    """Index talent ranks by spell id and verify the WotLK field layout."""
    expected = 44543
    expected_rows = [
        record for record in dbc.records
        if expected in [dbc.get_int(record, field) for field in range(4, 13)]
    ]
    if not expected_rows:
        raise RuntimeError(
            "Talent.dbc: el hechizo 44543 no aparece en los campos 4..12"
        )

    by_spell = defaultdict(list)
    for record in dbc.records:
        tab_id = dbc.get_int(record, 1)
        rank_spells = [
            dbc.get_int(record, field) for field in range(4, 13)
            if dbc.get_int(record, field) > 0
        ]
        talent = {
            "talent_id": dbc.get_int(record, 0),
            "talent_tab_id": tab_id,
            "rangos": len(rank_spells),
            "rank_spell_ids": rank_spells,
        }
        for spell_id in rank_spells:
            by_spell[spell_id].append(talent)
    return by_spell


def load_skills(dbc, skill_names):
    """Index skill-line memberships by spell id."""
    by_spell = defaultdict(list)
    for record in dbc.records:
        spell_id = dbc.get_int(record, 2)
        line_id = dbc.get_int(record, 1)
        by_spell[spell_id].append({
            "id": line_id,
            "nombre": skill_names.get(line_id),
        })
    for lines in by_spell.values():
        lines.sort(key=lambda line: (line["id"], line["nombre"] or ""))
    return by_spell


def spell_value(dbc, record, columns, name):
    """Read a named field, returning null if the DBC row lacks it."""
    field = columns.get(name)
    if field is None or field >= dbc.nfield:
        return None
    return dbc.get_int(record, field)


def spell_string(dbc, record, columns, name):
    offset = spell_value(dbc, record, columns, name)
    return dbc_string(dbc, offset) if offset is not None else None


def index_spells(dbc, columns, talent_by_spell, skill_by_spell):
    """Index spell rows by case-insensitive exact enUS name."""
    spells_by_name = defaultdict(list)
    for record in dbc.records:
        name = spell_string(dbc, record, columns, "Name_Lang_enUS")
        if not name:
            continue
        spell_id = spell_value(dbc, record, columns, "ID")
        if spell_id is None:
            continue
        attributes = spell_value(dbc, record, columns, "Attributes")
        talents = talent_by_spell.get(spell_id, [])
        candidate = {
            "id": spell_id,
            "nombre": name,
            "rango": spell_string(dbc, record, columns, "NameSubtext_Lang_enUS"),
            "nivel": spell_value(dbc, record, columns, "SpellLevel"),
            "nivel_base": spell_value(dbc, record, columns, "BaseLevel"),
            "max_level": spell_value(dbc, record, columns, "MaxLevel"),
            "pasivo": bool(attributes & 0x40) if attributes is not None else None,
            "es_rango_talento": bool(talents),
            "talentos": talents,
            "spell_class_set": spell_value(dbc, record, columns, "SpellClassSet"),
            "lineas_habilidad": skill_by_spell.get(spell_id, []),
            "detalles": {
                "attributes": attributes,
                "duration_index": spell_value(dbc, record, columns, "DurationIndex"),
                "casting_time_index": spell_value(dbc, record, columns, "CastingTimeIndex"),
                "power_type": spell_value(dbc, record, columns, "PowerType"),
                "mana_cost": spell_value(dbc, record, columns, "ManaCost"),
                "mana_cost_pct": spell_value(dbc, record, columns, "ManaCostPct"),
                "recovery_time": spell_value(dbc, record, columns, "RecoveryTime"),
                "effects": [
                    {
                        "effect": spell_value(dbc, record, columns, "Effect_" + str(index)),
                        "aura": spell_value(dbc, record, columns, "EffectAura_" + str(index)),
                        "trigger_spell": spell_value(
                            dbc, record, columns, "EffectTriggerSpell_" + str(index)
                        ),
                    }
                    for index in (1, 2, 3)
                ],
            },
        }
        spells_by_name[name.casefold()].append(candidate)
    for candidates in spells_by_name.values():
        candidates.sort(key=lambda spell: (spell["nivel"] or 0, spell["id"]))
    return spells_by_name


def rune_result(rune, spells_by_name):
    """Build one rune result and select its highest-level name match."""
    candidates = [dict(candidate) for candidate in spells_by_name.get(
        (rune.get("name_en") or "").casefold(), []
    )]
    if not candidates:
        kind = "sin_equivalente"
        highest = None
    else:
        highest = max(candidates, key=lambda spell: (spell["nivel"] or 0, spell["id"]))
        if any(candidate["es_rango_talento"] for candidate in candidates):
            kind = "talento"
        elif all(candidate["pasivo"] for candidate in candidates):
            kind = "pasivo"
        else:
            kind = "activo"
    return {
        "clase": rune.get("clase"),
        "slot": rune.get("slot"),
        "name_en": rune.get("name_en"),
        "name_es": rune.get("name_es"),
        "taught_spell_id": rune.get("taught_spell_id"),
        "tipo": kind,
        "rango_mas_alto": (
            {"id": highest["id"], "nivel": highest["nivel"]}
            if highest else None
        ),
        "candidatos": candidates,
    }


def escape_cell(value):
    return str(value or "—").replace("|", "\\|").replace("\n", " ")


def markdown_report(results, talent_layout, skill_check):
    """Render the Spanish summary and per-class rune tables."""
    lines = [
        "# Equivalencias de runas SoD con hechizos WotLK 3.3.5a",
        "",
        "El emparejamiento se hace solo por nombre inglés exacto, sin distinguir mayúsculas; "
        "no garantiza que el hechizo haga lo mismo que la runa.",
        "",
        "## Verificación de los DBC",
        "",
        "- `Talent.dbc`: 44543 aparece en los campos 4..12; TalentTab {}.".format(
            talent_layout["tab_id"]
        ),
        "- `SkillLineAbility.dbc`: 30455 aparece en la línea {} ({}) con AcquireMethod {}.".format(
            skill_check["line_id"], escape_cell(skill_check["line_name"]),
            skill_check["acquire_method"],
        ),
        "",
    ]
    overall = Counter(result["tipo"] for result in results)
    classes = sorted({result["clase"] or "desconocida" for result in results})
    slot_order = {slot: order for slot, order in PHASE_ONE_SLOTS.items()}
    for class_name in classes:
        class_rows = [result for result in results if (result["clase"] or "desconocida") == class_name]
        class_rows.sort(key=lambda result: (
            slot_order.get(result["slot"], 99),
            (result["name_en"] or "").casefold(),
        ))
        counts = Counter(result["tipo"] for result in class_rows)
        lines.extend([
            "## {}".format(class_name.capitalize()),
            "",
            "| Runa (es / en) | Ranura | Tipo | Equivalente WotLK |",
            "|---|---|---|---|",
        ])
        for result in class_rows:
            highest = result["rango_mas_alto"]
            if highest is None:
                equivalent = "—"
            else:
                equivalent = "{} (nivel {})".format(highest["id"], highest["nivel"])
                talents = [candidate for candidate in result["candidatos"]
                           if candidate["es_rango_talento"]]
                if talents:
                    annotations = []
                    seen_talents = set()
                    for candidate in talents:
                        for talent in candidate["talentos"]:
                            if talent["talent_id"] in seen_talents:
                                continue
                            seen_talents.add(talent["talent_id"])
                            annotations.append("TalentTab {} ({} rangos, id {})".format(
                                talent["talent_tab_id"], talent["rangos"], candidate["id"],
                            ))
                    equivalent += "; talento " + ", ".join(annotations)
            rune_name = "{} / {}".format(
                escape_cell(result["name_es"]), escape_cell(result["name_en"])
            )
            lines.append("| {} | {} | {} | {} |".format(
                rune_name, escape_cell(result["slot"]), result["tipo"], equivalent
            ))
        lines.extend([
            "",
            "Resumen: {} runas — {}.".format(
                len(class_rows), ", ".join(
                    "{} {}".format(counts[kind], kind)
                    for kind in ("sin_equivalente", "talento", "pasivo", "activo")
                )
            ),
            "",
        ])
    lines.extend([
        "## Total",
        "",
        "- " + ", ".join(
            "{} {}".format(overall[kind], kind)
            for kind in ("sin_equivalente", "talento", "pasivo", "activo")
        ),
        "- Runas sin equivalente: " + (
            ", ".join(
                "{} ({})".format(result["name_en"], result["clase"])
                for result in results if result["tipo"] == "sin_equivalente"
            ) or "ninguna"
        ),
        "",
    ])
    return "\n".join(lines)


def main():
    with CATALOG_PATH.open(encoding="utf-8") as handle:
        catalog = json.load(handle)
    runes = [rune for rune in catalog["runas"] if rune.get("slot") in PHASE_ONE_SLOTS]
    if not runes:
        raise RuntimeError("El catálogo no contiene runas de las tres ranuras de fase 1")

    columns = sod_dbc.load_columns(str(SPELL_SQL))
    column_map = {name: index for index, name in enumerate(columns)}
    missing = [name for name in SPELL_FIELDS if name not in column_map]
    if missing:
        raise RuntimeError("Faltan columnas de spell_dbc: " + ", ".join(missing))

    spell_dbc = sod_dbc.WDBC.load(str(DBC_ROOT / "Spell.dbc"))
    talent_dbc = sod_dbc.WDBC.load(str(DBC_ROOT / "Talent.dbc"))
    ability_dbc = sod_dbc.WDBC.load(str(DBC_ROOT / "SkillLineAbility.dbc"))
    skill_dbc = sod_dbc.WDBC.load(str(DBC_ROOT / "SkillLine.dbc"))
    if spell_dbc.nfield != len(columns):
        raise RuntimeError(
            "Spell.dbc tiene {} campos y spell_dbc define {}".format(
                spell_dbc.nfield, len(columns)
            )
        )

    skill_names = skill_line_names(skill_dbc)
    skill_by_spell = load_skills(ability_dbc, skill_names)
    talent_by_spell = load_talents(talent_dbc)
    spells_by_name = index_spells(spell_dbc, column_map, talent_by_spell, skill_by_spell)

    fingers_record = next((
        record for record in talent_dbc.records
        if 44543 in [talent_dbc.get_int(record, field) for field in range(4, 13)]
    ), None)
    if fingers_record is None:
        raise RuntimeError("No se pudo verificar la fila de talento para 44543")
    fingers_tab = talent_dbc.get_int(fingers_record, 1)
    talent_layout = {"tab_id": fingers_tab}

    known_rows = [record for record in ability_dbc.records
                  if ability_dbc.get_int(record, 2) == 30455]
    if not known_rows:
        raise RuntimeError("SkillLineAbility.dbc no contiene el hechizo conocido 30455")
    known = known_rows[0]
    skill_check = {
        "line_id": ability_dbc.get_int(known, 1),
        "line_name": skill_names.get(ability_dbc.get_int(known, 1)),
        "acquire_method": ability_dbc.get_int(known, 5),
    }

    results = [rune_result(rune, spells_by_name) for rune in runes]
    results.sort(key=lambda result: (
        result["clase"] or "desconocida",
        PHASE_ONE_SLOTS.get(result["slot"], 99),
        (result["name_en"] or "").casefold(),
    ))
    JSON_PATH.write_text(
        json.dumps(results, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    MARKDOWN_PATH.write_text(
        markdown_report(results, talent_layout, skill_check), encoding="utf-8"
    )

    totals = Counter(result["tipo"] for result in results)
    print("Total runas: {}".format(len(results)))
    print("Tipos: " + ", ".join(
        "{} {}".format(totals[kind], kind)
        for kind in ("sin_equivalente", "talento", "pasivo", "activo")
    ))
    print("Sin equivalente: " + (
        ", ".join(result["name_en"] for result in results
                   if result["tipo"] == "sin_equivalente") or "ninguna"
    ))
    print("Talent.dbc verificado: 44543 está en los campos 4..12; TalentTab {}.".format(
        talent_layout["tab_id"]
    ))
    print("SkillLineAbility.dbc verificado: Ice Lance 30455, línea {} ({}), AcquireMethod {}.".format(
        skill_check["line_id"], skill_check["line_name"], skill_check["acquire_method"]
    ))


if __name__ == "__main__":
    main()
