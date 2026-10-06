#!/usr/bin/env python3
"""Paladin spell specs cloned from the highest WotLK talent ranks."""

from sod_dbc import *  # noqa: F401,F403

SKILL_RETRIBUTION = 184
SKILL_PROTECTION = 267
SKILL_HOLY = 594


def build(idx):
    """Return Paladin spells cloned from their level-80 WotLK ranks."""
    duration_5000 = idx["dur"][5000]

    return [
        {  # Divine Storm: the core script handles the party heal.
            "id": 407778, "client": True, "template": 53385,
            "skill_line": SKILL_RETRIBUTION,
            "name": "Divine Storm", "script": "spell_pal_divine_storm",
            "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Avenger's Shield: remove the WotLK category cooldown.
            "id": 407669, "client": True, "template": 48827,
            "skill_line": SKILL_PROTECTION,
            "name": "Avenger's Shield", "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "bonus": {"direct": 0.07, "dot": 0.0, "ap": 0.07, "ap_dot": 0.0},
            "overrides": {
                "CategoryRecoveryTime": 0,
                "DurationIndex": duration_5000,
                "RecoveryTime": 15000,
                "SpellLevel": 0,
            },
        },
        {  # Aura Mastery: the core script supplies the silence immunity.
            "id": 407624, "client": True, "template": 31821,
            "skill_line": SKILL_HOLY,
            "name": "Aura Mastery", "script": "spell_pal_aura_mastery",
            "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Crusader Strike: retain its WotLK effect data and mana cost.
            "id": 407676, "client": True, "template": 35395,
            "skill_line": SKILL_RETRIBUTION,
            "name": "Crusader Strike", "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 6000,
                "SpellLevel": 0,
            },
        },
    ]
