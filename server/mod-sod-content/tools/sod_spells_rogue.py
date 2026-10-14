#!/usr/bin/env python3
"""Especificaciones de hechizos de pícaro clonados de rangos de WotLK."""

from sod_dbc import *  # noqa: F401,F403 (constantes compartidas de WoW)

SKILL_ASSASSINATION = 253

# Efectos y auras de WotLK 3.3.5a que no están expuestos por sod_dbc.
EFFECT_NORMALIZED_WEAPON_DAMAGE = 121
EFFECT_ADD_COMBO_POINTS = 80
AURA_MOD_THREAT = 10
AURA_MOD_STUN = 12
AURA_MOD_DECREASE_SPEED = 33
AURA_MOD_DODGE_PERCENT = 49
AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE = 187

# Golpe siniestro: máscara de familia A del cliente 3.3.5a.
MASK_SINISTER_STRIKE = 0x800002


def build(idx):
    """Devuelve hechizos de pícaro clonados de WotLK o plantillas genéricas."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    range_20 = idx["range"][20.0]
    return [
        {  # Mutilar conserva los hechizos disparados y las máscaras de WotLK.
            "id": 399956, "client": True, "template": 48666,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Mutilate", "script": "spell_rog_mutilate",
            "inherit_server": True,
            "overrides": {
                "ManaCost": 40,
                "SpellLevel": 0,
            },
        },
        {  # Brebaje letal: reproduce el proc nativo del talento de WotLK.
            "id": 399965, "client": True, "template": 51626,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Deadly Brew", "script": "spell_sod_rogue_deadly_brew",
            "inherit_server": True,
            # Copia de spell_proc -51625: venenos dañinos aplicados al objetivo.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 8,
                "SpellFamilyMask0": 268476416,
                "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 5, "SpellTypeMask": 2, "SpellPhaseMask": 0,
                "HitMask": 2, "AttributesMask": 0,
                "DisableEffectsMask": 0, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "overrides": {"SpellLevel": 0},
        },
        {  # Pasiva: el daño físico extra se limita a Danza de hojas en el script.
            "id": 400014, "client": True, "template": 774,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Just a Flesh Wound", "script": "spell_sod_rogue_just_a_flesh_wound",
            "desc": "While Blade Dance is active, you take 20% less physical damage, reduced further by 1% for every 12 Defense skill above the level-based baseline. Your Dodge chance is increased by 65%, you have 6% reduced chance to be critically hit by melee attacks, you deal 20% less damage, and your actions generate greatly increased threat. Feint taunts your selected target.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 8,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_rogue_cheatdeath"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE,
                "EffectBasePoints_1": -6, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectBasePoints_2": -20, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 127, "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_MOD_THREAT,
                "EffectBasePoints_3": 165, "EffectDieSides_3": 0,
                "EffectMiscValue_3": 127, "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Ayudante no visible: convierte el multiplicador de esquiva en +65 puntos.
            "id": 900066, "client": False, "template": 774,
            "name": "Just a Flesh Wound Dodge",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 8,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_DODGE_PERCENT,
                "EffectBasePoints_1": 65, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Disparo instantáneo a distancia con máscara de Golpe siniestro.
            "id": 398196, "client": True, "template": 49045,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Quick Draw", "script": "spell_sod_rogue_quick_draw",
            "desc": "Fire a quick ranged weapon shot that deals normal ranged weapon damage, slows the target by 50% for 6 sec, and awards 1 combo point. Benefits from talents and effects that trigger from or modify Sinister Strike.",
            "overrides": {
                "Attributes": 65538,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][6000],
                "RangeIndex": range_20, "SchoolMask": 1, "SpellLevel": 0,
                "PowerType": 3, "ManaCost": 25, "ManaCostPct": 0,
                "RecoveryTime": 10000, "Category": 0, "CategoryRecoveryTime": 0,
                "SpellClassSet": 8,
                "SpellClassMask_1": MASK_SINISTER_STRIKE,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": EFFECT_NORMALIZED_WEAPON_DAMAGE, "EffectAura_1": 0,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_DECREASE_SPEED,
                "EffectBasePoints_2": -50, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "Effect_3": EFFECT_ADD_COMBO_POINTS, "EffectAura_3": 0,
                "EffectBasePoints_3": 0, "EffectDieSides_3": 1,
                "ImplicitTargetA_3": TARGET_UNIT_TARGET_ENEMY,
            },
        },
        {  # Reducción de coste nativa; el bono contra PNJ se aplica en Puñalada/Emboscada.
            "id": 424925, "client": True, "template": 51712,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Slaughter from the Shadows", "script": "spell_sod_rogue_slaughter_from_the_shadows",
            "desc": "Reduces the Energy cost of Backstab and Ambush by 30 and increases their damage against non-player-controlled targets by 70%. Does not affect Mutilate or abilities learned from other runes.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 8,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_rogue_slaughterfromtheshadows"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 107,
                "EffectBasePoints_1": -30, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 14,
                # Máscaras WotLK de Puñalada (0x800004) y Emboscada (0x800200).
                "EffectSpellClassMaskA_1": 0x800204,
                "EffectSpellClassMaskB_1": 0, "EffectSpellClassMaskC_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
                "EffectSpellClassMaskA_3": 0, "EffectSpellClassMaskB_3": 0,
                "EffectSpellClassMaskC_3": 0,
            },
        },
        {  # Remate a distancia, comparte categoría y reutilización con Golpe en los riñones.
            "id": 400009, "client": True, "template": 49052,
            "skill_line": SKILL_ASSASSINATION,
            "name": "Between the Eyes", "script": "spell_sod_rogue_between_the_eyes",
            "bonus": {"direct": 0, "dot": 0, "ap": 1, "ap_dot": 0},
            "desc": "A ranged finishing move that deals damage based on combo points and Attack Power, and stuns the target for 1 sec per combo point. Shares a cooldown with Kidney Shot.",
            "overrides": {
                "Attributes": 4259858,
                # Igual que Eviscerar: obliga a tener puntos de combo y los consume al terminar.
                "AttributesEx": 1049088,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][1000],
                "RangeIndex": range_20, "SchoolMask": 1, "SpellLevel": 0,
                "PowerType": 3, "ManaCost": 35, "ManaCostPct": 0,
                "RecoveryTime": 0, "Category": 270, "CategoryRecoveryTime": 20000,
                "SpellClassSet": 8,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_rogue_kidneyshot"],
                "Effect_1": EFFECT_SCHOOL_DAMAGE, "EffectAura_1": 0,
                "EffectBasePoints_1": 52, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_MOD_STUN,
                "EffectBasePoints_3": 0, "EffectDieSides_3": 0,
                "ImplicitTargetA_3": TARGET_UNIT_TARGET_ENEMY,
            },
        },
    ]
