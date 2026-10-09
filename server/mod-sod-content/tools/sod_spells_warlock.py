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
        {  # Aflicción inestable conserva el manejador de disipación de rango 5 de WotLK.
            "id": 427717, "client": True, "template": 47843,
            "skill_line": SKILL_AFFLICTION,
            "name": "Unstable Affliction", "script": "spell_warl_unstable_affliction",
            "inherit_server": True,
            "bonus": {"direct": 0.0, "dot": 0.2, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Shadow energy slowly destroys the target, causing Shadow damage over 18 sec. If dispelled, it damages and silences the dispeller.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": idx["dur"][18000],
                "ManaCostPct": 15,
                "SpellLevel": 0,
            },
        },
        {  # Invocar guardia vil reutiliza la invocación y el control nativos de WotLK.
            "id": 427733, "client": True, "template": 30146,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Summon Felguard", "inherit_server": True,
            "desc": "Summons a Felguard under your command. The Felguard benefits from talents and effects that affect your other demon minions.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "ManaCostPct": 80,
                "SpellLevel": 0,
            },
        },
        {  # La runa concede la forma demoníaca; 47241 es la forma otorgada por el talento 59672.
            "id": 403789, "client": True, "template": 47241,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Metamorphosis", "inherit_server": True,
            "desc": "Transform into a Demon, increasing your Armor and threat. This tank form changes the effects of some Warlock abilities.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": duration_perm,
                "ManaCostPct": 100,
                "SpellLevel": 0,
            },
        },
        {  # Incinerar conserva el hechizo de Fuego de WotLK y aplica coste y bonificación de SoD.
            "id": 412758, "client": True, "template": 47838,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Incinerate", "inherit_server": True,
            "bonus": {"direct": 0.714, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Burn your enemy and increase all Fire damage you deal by 40% for 15 sec.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": duration_15000,
                "ManaCostPct": 14,
                "SpellLevel": 0,
                # El efecto 2 de 47838 está vacío: el +40 % de daño de Fuego (aura 79, escuela 4) va al lanzador.
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 79,
                "EffectBasePoints_2": 39, "EffectDieSides_2": 1, "EffectMiscValue_2": 4,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
            },
        },
        {  # El manejador nativo de Llama de las Sombras aplica el daño periódico de WotLK.
            "id": 426320, "client": True, "template": 61290,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Shadowflame", "script": "spell_warl_shadowflame",
            "inherit_server": True,
            "bonus": {"direct": 0.1064, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Burns the enemy with Shadowflame and applies additional Shadowflame damage over time.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "ManaCostPct": 27,
                "SpellLevel": 0,
            },
        },
    ]
