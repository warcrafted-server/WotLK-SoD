#!/usr/bin/env python3
"""Druid spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)


SKILL_RESTORATION = 573


def build(idx):
    """Return Druid spells cloned from the level-80 WotLK ranks."""
    return [
        {  # Wild Growth: retain WotLK rank effects and its core scripts.
            "id": 408120, "client": True, "template": 53251,
            "skill_line": SKILL_RESTORATION,
            "name": "Wild Growth", "script": "spell_dru_wild_growth",
            "bonus": {"direct": 0, "dot": 0.115, "ap": 0, "ap_dot": 0},
            "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 6000,
                "SpellLevel": 0,
                "ManaCostPct": 45,
            },
        },
    ]
