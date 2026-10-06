#!/usr/bin/env python3
"""Hunter spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403

SKILL_MARKSMANSHIP = 163


def build(idx):
    """Return Hunter spells cloned from the level-80 WotLK talent ranks."""
    return [
        {  # Keep the WotLK script effect; apply Chimera Shot's SoD costs.
            "id": 409433, "client": True, "template": 53209,
            "skill_line": SKILL_MARKSMANSHIP,
            "name": "Chimera Shot", "script": "spell_hun_chimera_shot",
            "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "ManaCostPct": 6,
                "RecoveryTime": 6000,
                "SpellLevel": 0,
            },
        },
    ]
