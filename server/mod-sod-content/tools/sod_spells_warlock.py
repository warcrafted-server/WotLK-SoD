#!/usr/bin/env python3
"""Warlock spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)

SKILL_AFFLICTION = 355
SKILL_DESTRUCTION = 593


def build(idx):
    """Return Warlock spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_15000 = idx["dur"][15000]

    return [
        {  # Chaos Bolt: retain WotLK rank effects; apply the confirmed SoD cooldown.
            "id": 403629, "client": True, "template": 59172,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Chaos Bolt", "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 12000,
                "SpellLevel": 0,
                "SchoolMask": 124,
            },
        },
        {  # Haunt: preserve the WotLK dummy aura expected by spell_warl_haunt.
            "id": 403501, "client": True, "template": 59164,
            "skill_line": SKILL_AFFLICTION,
            "name": "Haunt", "script": "spell_warl_haunt",
            "inherit_server": True,
            "overrides": {
                "CastingTimeIndex": cast_instant,
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 12000,
                "DurationIndex": duration_15000,
                "SpellLevel": 0,
            },
        },
    ]
