#!/usr/bin/env python3
"""Rogue spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403 (shared WoW enum constants)

SKILL_ASSASSINATION = 253


def build(idx):
    """Return Rogue spells cloned from the level-80 WotLK ranks."""
    return [
        {  # Mutilate: retain the WotLK trigger spells and family masks.
            "id": 399956, "client": True, "template": 48666,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Mutilate", "script": "spell_rog_mutilate",
            "inherit_server": True,
            "overrides": {
                "ManaCost": 40,
                "SpellLevel": 0,
            },
        },
    ]
