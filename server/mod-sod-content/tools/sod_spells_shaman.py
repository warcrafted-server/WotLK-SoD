#!/usr/bin/env python3
"""Shaman spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403 (shared WoW enum constants)

SKILL_ENHANCEMENT = 373
SKILL_RESTORATION = 374


def build(idx):
    """Return Shaman spells cloned from the WotLK rank templates."""
    return [
        {  # Earth Shield: preserve the WotLK aura effects and proc script.
            "id": 408514, "client": True, "template": 49284,
            "skill_line": SKILL_RESTORATION,
            "name": "Earth Shield", "script": "spell_sha_earth_shield",
            "bonus": {"direct": 0.5371, "dot": 0, "ap": 0, "ap_dot": 0},
            "inherit_server": True,
            "overrides": {
                "ManaCostPct": 5,
                "SpellLevel": 0,
            },
        },
        {  # Lava Lash: keep the WotLK weapon damage and Flametongue script.
            "id": 408507, "client": True, "template": 60103,
            "skill_line": SKILL_ENHANCEMENT,
            "name": "Lava Lash", "script": "spell_sha_lava_lash",
            "inherit_server": True,
            "overrides": {
                "ManaCostPct": 1,
                "SpellLevel": 0,
            },
        },
    ]
