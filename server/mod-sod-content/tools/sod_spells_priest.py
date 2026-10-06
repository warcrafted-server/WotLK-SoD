#!/usr/bin/env python3
"""Priest spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403

SKILL_HOLY = 56
SKILL_DISCIPLINE = 613


def build(idx):
    """Return Priest spells cloned from the level-80 WotLK ranks."""
    return [
        {  # Circle of Healing keeps its target filter and healing coefficient.
            "id": 401946, "client": True, "template": 48089,
            "skill_line": SKILL_HOLY,
            "name": "Circle of Healing", "script": "spell_pri_circle_of_healing",
            "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "bonus": {"direct": 0.402, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "ManaCostPct": 56,
                "SpellLevel": 0,
            },
        },
        {  # Penance's core script requires the original WotLK rank chain.
            "id": 402174, "client": True, "template": 53007,
            "skill_line": SKILL_DISCIPLINE,
            "name": "Penance", "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
            },
        },
    ]
