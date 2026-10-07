#!/usr/bin/env python3
"""Generate SoD rune item acquisitions supported by the local WotLK world data."""

from __future__ import annotations

import argparse
import csv
import json
import re
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[2]
CORE_SQL = Path("/home/stark/Repos/acore-test/data/sql")
SOURCE_FILE = ROOT / "docs/runas/fuentes-sod.json"
ITEM_DATA = ROOT / "datos/wago/1.15.9.70003"
CONTENT_BASE = ROOT / "server/mod-sod-content/data/sql/db-world/base"
CLIENT_ITEMS = ROOT / "server/mod-sod-content/tools/client_items.json"
CLASS_MASKS = {
    "warrior": 1,
    "paladin": 2,
    "hunter": 4,
    "rogue": 8,
    "priest": 16,
    "deathknight": 32,
    "shaman": 64,
    "mage": 128,
    "warlock": 256,
    "druid": 1024,
}
BROKER_IDS = {233335, 233428}
SUPPLY_OFFICERS = {213077, 214070, 214096, 214098, 214099, 214101}
GRIZZBY_ID = 211653
BROKER_PRICE_COPPER = 10000
CREATURE_LOOT_ID_INDEX = 34
GAMEOBJECT_DATA1_INDEX = 9


def sql_string(value: Any) -> str:
    return "'" + str(value).replace("\\", "\\\\").replace("'", "''") + "'"


def read_csv(path: Path) -> dict[int, dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as source:
        return {int(row["ID"]): row for row in csv.DictReader(source)}


def parse_tuple(text: str, start: int) -> tuple[list[str], int]:
    fields: list[str] = []
    current: list[str] = []
    depth = 0
    quoted = False
    index = start
    while index < len(text):
        char = text[index]
        if char == "\\" and quoted and index + 1 < len(text):
            current.extend((char, text[index + 1]))
            index += 2
            continue
        if char == "'":
            if quoted and index + 1 < len(text) and text[index + 1] == "'":
                current.extend((char, text[index + 1]))
                index += 2
                continue
            quoted = not quoted
        elif not quoted and char == "(":
            depth += 1
        elif not quoted and char == ")":
            depth -= 1
            if depth == 0:
                fields.append("".join(current).strip())
                return fields, index + 1
        if not quoted and char == "," and depth == 1:
            fields.append("".join(current).strip())
            current = []
        else:
            current.append(char)
        index += 1
    return [], len(text)


def parse_template_values(text: str, table: str, ids: set[int]) -> dict[int, list[str]]:
    header = re.compile(
        rf"(?:INSERT|REPLACE)\s+(?:IGNORE\s+)?INTO\s+`?{re.escape(table)}`?"
        rf"\s*(?:\([^;]*?\))?\s*VALUES\b",
        re.IGNORECASE,
    )
    wanted = {str(value) for value in ids}
    row_start = re.compile(r"\(\s*(\d+)\s*,")
    rows: dict[int, list[str]] = {}
    for statement in header.finditer(text):
        end = text.find(";", statement.end())
        if end < 0:
            end = len(text)
        cursor = statement.end()
        while cursor < end:
            match = row_start.search(text, cursor, end)
            if not match:
                break
            cursor = match.start()
            if match.group(1) in wanted:
                values, after = parse_tuple(text, cursor)
                if values:
                    rows[int(match.group(1))] = values
                cursor = after
            else:
                cursor = match.end()
    return rows


def parse_template_updates(text: str, table: str, ids: set[int]) -> dict[int, dict[str, int]]:
    rows: dict[int, dict[str, int]] = {}
    update = re.compile(
        rf"UPDATE\s+`?{re.escape(table)}`?\s+SET\s+(.*?)\s+WHERE\s+(.*?);",
        re.IGNORECASE | re.DOTALL,
    )
    for match in update.finditer(text):
        assignments = {
            key.lower(): int(value)
            for key, value in re.findall(r"`?(\w+)`?\s*=\s*(\d+)", match.group(1))
        }
        entries = [int(value) for value in re.findall(r"`?entry`?\s*=\s*(\d+)", match.group(2), re.I)]
        for entry in entries:
            if entry in ids:
                rows.setdefault(entry, {}).update(assignments)
    return rows


def load_template_rows(table: str, ids: set[int], base: Path, search_roots: list[Path], field_index: int) -> dict[int, tuple[int, Path]]:
    if not ids:
        return {}
    result: dict[int, tuple[int, Path]] = {}
    base_rows = parse_template_values(base.read_text(encoding="utf-8", errors="replace"), table, ids)
    for entry, fields in base_rows.items():
        if len(fields) > field_index:
            try:
                result[entry] = (int(fields[field_index]), base)
            except ValueError:
                pass

    missing = ids - result.keys()
    for root in search_roots:
        if not root.is_dir() or not missing:
            continue
        for path in sorted(root.rglob("*.sql")):
            try:
                text = path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            if table not in text:
                continue
            rows = parse_template_values(text, table, missing)
            updates = parse_template_updates(text, table, missing)
            for entry, fields in rows.items():
                if len(fields) > field_index:
                    try:
                        result[entry] = (int(fields[field_index]), path)
                    except ValueError:
                        pass
            for entry, values in updates.items():
                if entry not in result and entry in values:
                    result[entry] = (values[entry], path)
            missing = ids - result.keys()
            if not missing:
                break
    return result


def vendor_coin_cost(vendor: dict[str, Any]) -> int | None:
    for cost in vendor.get("cost", []):
        if cost and isinstance(cost[0], int) and cost[0] > 0:
            return cost[0]
    return None


def percent(count: Any, outof: Any) -> str:
    rate = round(100 * float(count) / float(outof), 4)
    rate = min(100.0, max(0.01, rate))
    return f"{rate:.4f}".rstrip("0").rstrip(".")


def make_sql(class_name: str, runes: list[dict[str, Any]], source: dict[str, Any], en_items: dict[int, dict[str, str]], es_items: dict[int, dict[str, str]], creature_rows: dict[int, tuple[int, Path]], gameobject_rows: dict[int, tuple[int, Path]]) -> str:
    rune_by_spell = {rune["spell_id"]: rune for rune in runes}
    item_records: dict[int, tuple[dict[str, Any], dict[str, Any], dict[str, str], dict[str, str]]] = {}
    for spell_id, rune in rune_by_spell.items():
        rune_source = source.get(str(spell_id))
        if not rune_source or rune_source.get("clase") != class_name:
            continue
        for item in rune_source.get("objetos", []):
            item_id = int(item["id"])
            if item_id not in en_items or item_id not in es_items:
                raise ValueError(f"Falta ItemSparse enUS/esES para el objeto {item_id}.")
            item_records[item_id] = (rune, item, en_items[item_id], es_items[item_id])

    if not item_records:
        raise ValueError(f"No se encontraron objetos de runa para la clase {class_name}.")

    item_values: list[str] = []
    locale_values: list[str] = []
    unlock_values: list[str] = []
    broker_values: list[str] = []
    grizzby_values: list[str] = []
    supply_values: list[tuple[int, int]] = []
    drop_values: list[str] = []
    creature_condition_values: list[str] = []
    object_values: list[str] = []
    object_condition_values: list[str] = []
    skipped_creatures: set[int] = set()
    skipped_objects: set[int] = set()
    skipped_zero_loot: set[int] = set()
    broker_only_items: set[int] = set()
    seen_gameobject_loot: set[tuple[int, int]] = set()
    gameobject_sources: dict[int, set[int]] = {}

    for item_id, (rune, item, en, es) in sorted(item_records.items()):
        rune_label = rune["name"]
        vendors = item.get("vendors", [])
        non_broker_vendors = [vendor for vendor in vendors if int(vendor["id"]) not in BROKER_IDS]
        buy_price = int(en["BuyPrice"])
        if not non_broker_vendors and any(int(vendor["id"]) in BROKER_IDS for vendor in vendors):
            buy_price = BROKER_PRICE_COPPER
            broker_only_items.add(item_id)
        grizzby = next((vendor for vendor in vendors if int(vendor["id"]) == GRIZZBY_ID), None)
        if grizzby:
            cost = vendor_coin_cost(grizzby)
            if cost is not None:
                buy_price = cost
                grizzby_values.append(
                    f"    (211653, 0, {item_id}, 0, 0, 0)"
                )
        for vendor in vendors:
            vendor_id = int(vendor["id"])
            if vendor_id in SUPPLY_OFFICERS:
                supply_values.append((item_id, 4))

        allowable_class = int(en["AllowableClass"])
        if allowable_class == -1:
            allowable_class = int(rune["class_mask"])
        fields = (
            item_id,
            sql_string(en["Display_lang"]),
            int(en["OverallQualityID"]),
            buy_price,
            int(en["SellPrice"]),
            allowable_class,
            int(en["ItemLevel"]),
            int(en["RequiredLevel"]),
            int(en["MaxCount"]),
            int(en["Stackable"]),
            int(en["Bonding"]),
            sql_string(en["Description_lang"]),
        )
        item_values.append(
            "    ({}, 15, 0, {}, 1102, {}, 0, 1, {}, {}, 0,\n"
            "     {}, -1, {}, {},\n"
            "     {}, {}, {}, 1, 0,\n"
            "     55884, 0, 'item_rune_unlock',\n"
            "     {})".format(*fields)
        )
        description = "NULL" if not es["Description_lang"] else sql_string(es["Description_lang"])
        locale_values.append(
            f"    ({item_id}, 'esES', {sql_string(es['Display_lang'])}, {description}, 0)"
        )
        unlock_values.append(f"    ({item_id}, {rune['rune_id']})")
        broker_values.append(f"    (700000, 0, {item_id}, 0, 0, 0)")

        for drop in item.get("drops", []):
            creature_id = int(drop["id"])
            if creature_id not in creature_rows:
                skipped_creatures.add(creature_id)
                continue
            loot_id = creature_rows[creature_id][0]
            if loot_id == 0:
                skipped_zero_loot.add(creature_id)
                continue
            drop_values.append(
                f"    ({loot_id}, {item_id}, 0, {percent(drop['count'], drop['outof'])}, 0, 1, 0, 1, 1, "
                f"{sql_string('mod-sod-' + class_name + ' ' + rune_label + ' rune')})"
            )
            creature_condition_values.append(
                f"    (1, {loot_id}, {item_id}, 0, 0, 15, 0, {allowable_class}, 0, 0, 0, "
                f"{sql_string('mod-sod-' + class_name + ': ' + rune_label + ' item for class only')})"
            )

        for obj in item.get("objects", []):
            object_id = int(obj["id"])
            if object_id not in gameobject_rows:
                skipped_objects.add(object_id)
                continue
            loot_id = gameobject_rows[object_id][0]
            if loot_id == 0:
                skipped_objects.add(object_id)
                continue
            key = (loot_id, item_id)
            gameobject_sources.setdefault(loot_id, set()).add(object_id)
            if key in seen_gameobject_loot:
                continue
            seen_gameobject_loot.add(key)
            object_values.append(
                f"    ({loot_id}, {item_id}, 0, {percent(obj['count'], obj['outof'])}, 0, 1, 0, 1, 1, "
                f"{sql_string('mod-sod-' + class_name + ' ' + rune_label + ' rune')})"
            )
            object_condition_values.append(
                f"    (4, {loot_id}, {item_id}, 0, 0, 15, 0, {allowable_class}, 0, 0, 0, "
                f"{sql_string('mod-sod-' + class_name + ': ' + rune_label + ' item for class only')})"
            )

    lines = [
        f"-- mod-sod-{class_name}: WotLK-supported item acquisition for SoD runes.",
        "-- Real Rune Brokers sell these items throughout the capitals and starting zones;",
        "-- the summoned Rune Engraver is the local substitute. Broker-only vendor stock uses 10000 copper",
        "-- because this core has no per-vendor price hook. Grizzby's recorded coin cost overrides ItemSparse.",
    ]
    for loot_id, sources in sorted(gameobject_sources.items()):
        if len(sources) > 1:
            lines.append(
                f"-- Shared WotLK gameobject lootid {loot_id} for SoD objects "
                f"{', '.join(map(str, sorted(sources)))}; one loot row uses the first source rate."
            )
    lines.extend(
        [
        "",
        "REPLACE INTO `item_template`",
        "    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,",
        "     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,",
        "     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,",
        "     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,",
        "     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`)",
        "VALUES",
        ",\n".join(item_values) + ";",
        "",
        "REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES",
        ",\n".join(locale_values) + ";",
        ]
    )
    if drop_values:
        lines.extend(
            [
                "",
                "REPLACE INTO `creature_loot_template`",
                "    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES",
                ",\n".join(drop_values) + ";",
            ]
        )
    if object_values:
        lines.extend(
            [
                "",
                "REPLACE INTO `gameobject_loot_template`",
                "    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES",
                ",\n".join(object_values) + ";",
            ]
        )
    if creature_condition_values or object_condition_values:
        lines.extend(
            [
                "",
                "REPLACE INTO `conditions`",
                "    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,",
                "     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,",
                "     `NegativeCondition`, `Comment`) VALUES",
                ",\n".join(creature_condition_values + object_condition_values) + ";",
            ]
        )
    lines.extend(
        [
            "",
            "REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES",
            ",\n".join(broker_values) + ";",
        ]
    )
    if grizzby_values:
        lines.extend(
            [
                "",
                "INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES",
                ",\n".join(grizzby_values),
                "ON DUPLICATE KEY UPDATE `maxcount` = VALUES(`maxcount`), `incrtime` = VALUES(`incrtime`), `ExtendedCost` = VALUES(`ExtendedCost`);",
            ]
        )
    if supply_values:
        supplies = sorted(set(supply_values))
        lines.extend(
            [
                "",
                "SET @supply_tbl := (SELECT COUNT(*) FROM information_schema.tables",
                "                    WHERE table_schema = DATABASE() AND table_name = 'sod_world_supply_vendor');",
                "SET @sql := IF(@supply_tbl > 0,",
                "'INSERT INTO `sod_world_supply_vendor` (`item`, `RequiredRank`) VALUES "
                + ", ".join(f"({item}, {rank})" for item, rank in supplies)
                + " ON DUPLICATE KEY UPDATE `RequiredRank` = VALUES(`RequiredRank`)',",
                "'DO 0');",
                "PREPARE stmt FROM @sql;",
                "EXECUTE stmt;",
                "DEALLOCATE PREPARE stmt;",
            ]
        )
    lines.extend(
        [
            "",
            "SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables",
            "                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');",
            "SET @sql := IF(@item_unlock_tbl > 0,",
            "'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES "
            + ", ".join(f"({item_id}, {rune['rune_id']})" for item_id, (rune, _item, _en, _es) in sorted(item_records.items()))
            + " ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',",
            "'DO 0');",
            "PREPARE stmt FROM @sql;",
            "EXECUTE stmt;",
            "DEALLOCATE PREPARE stmt;",
            "",
        ]
    )
    if skipped_zero_loot:
        lines.insert(4, "-- Skipped creature lootid 0: " + ", ".join(map(str, sorted(skipped_zero_loot))) + ".")
    return "\n".join(lines)


def load_runes(path: Path, class_name: str) -> list[dict[str, Any]]:
    sql = path.read_text(encoding="utf-8")
    matches = re.findall(
        r"^\s*\((\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*\d+\s*,\s*''((?:[^']|'''')*)''\s*,",
        sql,
        re.MULTILINE,
    )
    runes = []
    for rune_id, spell_id, class_mask, name in matches:
        spell = int(spell_id)
        runes.append(
            {
                "rune_id": int(rune_id),
                "spell_id": spell,
                "class_mask": int(class_mask),
                "name": name.replace("''''", "'"),
            }
        )
    if not runes:
        raise ValueError(f"No se pudieron leer runas de {path}.")
    return runes


def update_client_manifest(records: dict[int, tuple[dict[str, Any], dict[str, Any], dict[str, str], dict[str, str]]]) -> None:
    manifest = json.loads(CLIENT_ITEMS.read_text(encoding="utf-8"))
    existing = {int(row["id"]) for row in manifest}
    additions = []
    for item_id, (_rune, _item, en, _es) in sorted(records.items()):
        if item_id in existing:
            continue
        additions.append(
            {
                "id": item_id,
                "name": en["Display_lang"],
                "class": 15,
                "subclass": 0,
                "material": 1,
                "display": 1102,
                "invtype": 0,
                "sheath": 0,
            }
        )
    manifest.extend(additions)
    CLIENT_ITEMS.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--class", dest="class_name", required=True, choices=sorted(CLASS_MASKS))
    args = parser.parse_args()
    class_name = args.class_name
    rune_path = CONTENT_BASE / f"sod_{class_name}_runes.sql"
    runes = load_runes(rune_path, class_name)
    sources = json.loads(SOURCE_FILE.read_text(encoding="utf-8"))
    spells = {rune["spell_id"] for rune in runes}
    item_ids = {
        int(item["id"])
        for spell_id, info in sources.items()
        if int(spell_id) in spells and info.get("clase") == class_name
        for item in info.get("objetos", [])
    }
    en_items = {item_id: row for item_id, row in read_csv(ITEM_DATA / "ItemSparse.enUS.csv").items() if item_id in item_ids}
    es_items = {item_id: row for item_id, row in read_csv(ITEM_DATA / "ItemSparse.esES.csv").items() if item_id in item_ids}

    creature_ids = {
        int(drop["id"])
        for spell_id, info in sources.items()
        if int(spell_id) in spells and info.get("clase") == class_name
        for item in info.get("objetos", [])
        for drop in item.get("drops", [])
    }
    object_ids = {
        int(obj["id"])
        for spell_id, info in sources.items()
        if int(spell_id) in spells and info.get("clase") == class_name
        for item in info.get("objetos", [])
        for obj in item.get("objects", [])
    }
    base = CORE_SQL / "base/db_world"
    creatures = load_template_rows(
        "creature_template",
        creature_ids,
        base / "creature_template.sql",
        [CORE_SQL / "updates/db_world", CORE_SQL / "archive/db_world"],
        CREATURE_LOOT_ID_INDEX,
    )
    gameobjects = load_template_rows(
        "gameobject_template",
        object_ids,
        base / "gameobject_template.sql",
        [],
        GAMEOBJECT_DATA1_INDEX,
    )
    sql = make_sql(class_name, runes, sources, en_items, es_items, creatures, gameobjects)
    target = CONTENT_BASE / f"sod_{class_name}_acquisition.sql"
    target.write_text(sql, encoding="utf-8")

    records = {}
    for spell_id, rune in {item["spell_id"]: item for item in runes}.items():
        info = sources.get(str(spell_id), {})
        for item in info.get("objetos", []):
            item_id = int(item["id"])
            if item_id in en_items and item_id in es_items:
                records[item_id] = (rune, item, en_items[item_id], es_items[item_id])
    update_client_manifest(records)
    print(f"Generado {target.relative_to(ROOT)} ({len(item_ids)} objeto(s), {len(runes)} runa(s)).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
