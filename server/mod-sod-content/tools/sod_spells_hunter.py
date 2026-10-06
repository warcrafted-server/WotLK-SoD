#!/usr/bin/env python3
"""Hunter spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403

SKILL_MARKSMANSHIP = 163


def build(idx):
    """Return Hunter spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    icon_master_marksman = idx["icon"]["ability_hunter_mastermarksman"]

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
        {  # Extend the cost modifier to every Shot family present in SoD.
            "id": 409428, "client": True, "template": 34489,
            "skill_line": SKILL_MARKSMANSHIP,
            "name": "Master Marksman", "inherit_server": True,
            "desc": "Increases your critical strike chance by 5%, and reduces the Mana cost of all your Shot abilities by 25%.",
            "aura_desc": "Increases your critical strike chance by 5%, and reduces the Mana cost of all your Shot abilities by 25%.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SpellIconID": icon_master_marksman,
                "SpellLevel": 0,
                "EffectSpellClassMaskA_2": 137216,
                "EffectSpellClassMaskB_2": -2139095039,
                "EffectSpellClassMaskC_2": 1,
                "EffectBasePoints_3": 0,
                "EffectDieSides_3": 0,
                "EffectSpellClassMaskA_3": 0,
                "EffectSpellClassMaskB_3": 0,
                "EffectSpellClassMaskC_3": 0,
            },
        },
    ]
