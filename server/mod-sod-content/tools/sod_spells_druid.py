#!/usr/bin/env python3
"""Druid spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)


SKILL_RESTORATION = 573
SKILL_FERAL_COMBAT = 134


def build(idx):
    """Return Druid spells cloned from the level-80 WotLK ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    icon_survival = idx["icon"]["spell_nature_spiritwolf"]

    return [
        {  # Wild Growth: retain WotLK rank effects and its core scripts.
            "id": 408120, "client": True, "template": 53251,
            "skill_line": SKILL_RESTORATION,
            "name": "Wild Growth", "script": "spell_dru_wild_growth",
            "bonus": {"direct": 0, "dot": 0.115, "ap": 0, "ap_dot": 0},
            "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 6000,
                "SpellLevel": 0,
                "ManaCostPct": 45,
            },
        },
        {  # Lacerate: retain rank-3 damage and its WotLK attack-power coefficient.
            "id": 414644, "client": True, "template": 48568,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Lacerate", "inherit_server": True,
            "bonus": {"direct": 0, "dot": 0, "ap": 0, "ap_dot": 0.01},
            "scale_to_level": {"effects": [1], "level": 80},
            "overrides": {
                "ManaCost": 100,
                "SpellLevel": 0,
            },
        },
        {  # Savage Roar: its paired core scripts remain rank-independent.
            "id": 407988, "client": True, "template": 52610,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Savage Roar", "script": "spell_dru_savage_roar",
            "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Berserk: use the active talent, not its 51266 trigger spell.
            "id": 417141, "client": True, "template": 50334,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Berserk", "script": "spell_dru_berserk",
            "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "SpellLevel": 0,
            },
        },
        {  # Survival Instincts: preserve its max-health script at SoD's 20%.
            "id": 408024, "client": True, "template": 61336,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Survival Instincts",
            "script": "spell_dru_survival_instincts",
            "inherit_server": True,
            "overrides": {
                "RecoveryTime": 180000,
                "CategoryRecoveryTime": 0,
                "EffectBasePoints_1": 19,
                "SpellLevel": 0,
            },
        },
        {  # SoD's 10% bear-form reduction (411124) is omitted; it needs C++.
            "id": 411115, "client": True, "template": 774,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Survival of the Fittest", "inherit_server": True,
            "desc": "Reduces the chance you'll be critically hit by melee attacks by 7% and reduces all damage taken by 10%.",
            "aura_desc": "Reduces the chance you'll be critically hit by melee attacks by 7% and reduces all damage taken by 10%.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SpellIconID": icon_survival,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 87,
                "EffectBasePoints_1": -9, "EffectDieSides_1": 1,
                "EffectMiscValue_1": 127,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 187,
                "EffectBasePoints_2": -6, "EffectDieSides_2": 1,
                "EffectMiscValue_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
                "EffectBasePoints_3": 0, "EffectDieSides_3": 0,
                "EffectMiscValue_3": 0,
                "ImplicitTargetA_3": 0,
                "EffectSpellClassMaskA_3": 0, "EffectSpellClassMaskB_3": 0,
                "EffectSpellClassMaskC_3": 0,
            },
        },
    ]
