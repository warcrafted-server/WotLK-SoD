#!/usr/bin/env python3
"""Warlock spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)

SKILL_AFFLICTION = 355
SKILL_DEMONOLOGY = 354
SKILL_DESTRUCTION = 593
TARGET_UNIT_PET = 5


def build(idx):
    """Return Warlock spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_15000 = idx["dur"][15000]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    icon_demonic_tactics = idx["icon"]["spell_shadow_demonictactics"]

    return [
        {  # Chaos Bolt: retain WotLK rank effects; apply the confirmed SoD cooldown.
            "id": 403629, "client": True, "template": 59172,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Chaos Bolt", "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
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
            "scale_to_level": {"effects": [1], "level": 80},
            "overrides": {
                "CastingTimeIndex": cast_instant,
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 12000,
                "DurationIndex": duration_15000,
                "SpellLevel": 0,
            },
        },
        {  # Demonic Tactics: preserve the WotLK rank-5 effects and also target the pet.
            "id": 412727, "client": True, "template": 30248,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Demonic Tactics", "inherit_server": True,
            "desc": "Increases the melee and spell critical strike chance of you and your pet by 10%.",
            "aura_desc": "Increases the melee and spell critical strike chance of you and your pet by 10%.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SpellIconID": icon_demonic_tactics,
                "SpellLevel": 0,
                "ImplicitTargetB_1": TARGET_UNIT_PET,
                "ImplicitTargetB_2": TARGET_UNIT_PET,
                "ImplicitTargetB_3": TARGET_UNIT_PET,
            },
        },
    ]
