#!/usr/bin/env python3
"""Genera sod_runes_locale_es.sql: nombres y descripciones esES de las runas que aún no tienen traducción.

Toma las runas de server/mod-sod-content/data/sql/db-world/base/sod_*_runes.sql, descarta las que ya traduce
mod-rune-engraving (rune_engraving_locale_es.sql) y busca el texto de su hechizo en tools/sod_spells_es.json.
Uso: python3 tools/sod-data/gen_rune_locale.py
"""
import glob
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CONTENT = ROOT / 'server/mod-sod-content'
ENGINE_LOCALE = ROOT / 'server/mod-rune-engraving/data/sql/db-world/base/rune_engraving_locale_es.sql'
OUT = CONTENT / 'data/sql/db-world/base/sod_runes_locale_es.sql'


def sql_string(text):
    return "'" + text.replace("\\", "\\\\").replace("'", "''") + "'"


def main():
    es = json.loads((CONTENT / 'tools/sod_spells_es.json').read_text())
    translated = {int(i) for i in re.findall(r'^\((\d{7}), \'esES\'', ENGINE_LOCALE.read_text(), re.M)}
    rows, sin_texto = [], []
    for path in sorted(glob.glob(str(CONTENT / 'data/sql/db-world/base/sod_*_runes.sql'))):
        for rid, sid in re.findall(r"\((70\d{5}), (\d+), \d+, \d+, ''", Path(path).read_text()):
            rid = int(rid)
            if rid in translated:
                continue
            entry = es.get(sid)
            if not entry or not entry.get('name'):
                sin_texto.append((rid, sid))
                continue
            rows.append((rid, entry['name'], entry.get('desc') or entry.get('aura_desc') or ''))
    lines = [
        "-- Nombres y descripciones esES de las runas que no traduce rune_engraving_locale_es.sql.",
        "-- Generado por tools/sod-data/gen_rune_locale.py; no editar a mano.",
        "CREATE TABLE IF NOT EXISTS `rune_template_locale` (",
        "    `rune_id`     INT UNSIGNED NOT NULL,",
        "    `locale`      ENUM('koKR','frFR','deDE','zhCN','zhTW','esES','esMX','ruRU') NOT NULL,",
        "    `name`        VARCHAR(255) NOT NULL,",
        "    `description` TEXT NOT NULL,",
        "    PRIMARY KEY (`rune_id`, `locale`)",
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;",
        "",
        "REPLACE INTO `rune_template_locale` (`rune_id`, `locale`, `name`, `description`) VALUES",
    ]
    lines.append(",\n".join(f"({r}, 'esES', {sql_string(n)}, {sql_string(d)})" for r, n, d in sorted(rows)) + ";")
    OUT.write_text("\n".join(lines) + "\n")
    print(f"{len(rows)} runas traducidas; sin texto en el JSON: {sin_texto}")


if __name__ == '__main__':
    main()
