#!/usr/bin/env python3
"""Especificaciones de hechizos de mago clonados de rangos de WotLK (runas posteriores a la fase 1)."""

from sod_dbc import *  # noqa: F401,F403 (constantes compartidas de WoW)

SKILL_FROST = 6
SKILL_ARCANE = 237


def build(idx):
    """Devuelve los hechizos de mago clonados de rangos de WotLK."""
    cast_3s = idx["cast"][3000]
    duration_9s = idx["dur"][9000]
    duration_20s = idx["dur"][20000]
    cast_instant = idx["cast"][0]
    range_self = idx["range"][0.0]

    return [
        {  # Frostfire Bolt conserva el impacto, la ralentización y el DoT nativos.
            "id": 401502, "client": True, "template": 47610,
            "skill_line": SKILL_FROST,
            "name": "Frostfire Bolt", "script": "spell_mage_frostfire_bolt",
            "inherit_server": True,
            "desc": "Launches a bolt of frostfire at the enemy, causing Frostfire damage, "
                    "slowing movement speed by 40% and causing additional Frostfire damage "
                    "over 9 sec. This spell counts as both Frost and Fire damage.",
            "aura_desc": "Movement slowed by 40%. Additional Frostfire damage every 3 sec.",
            "bonus": {"direct": 1.0, "dot": 0.12, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "CastingTimeIndex": cast_3s,
                "DurationIndex": duration_9s,
                "ManaCostPct": 14,
                "SchoolMask": 20,
                "SpellLevel": 0,
            },
        },
        {  # Missile Barrage conserva el proc y la mejora de Misiles Arcanos de WotLK.
            "id": 400588, "client": True, "template": 54490,
            "skill_line": SKILL_FROST,
            "name": "Missile Barrage", "script": "spell_mage_missile_barrage",
            "inherit_server": True,
            "desc": "Gives your Arcane Blast a 40% chance, and your Fireball and Frostbolt "
                    "spells a 20% chance to reduce the channeled duration of your next Arcane "
                    "Missiles spell by 100%, reduce the mana cost by 100%, and cause missiles "
                    "to fire every 0.5 sec.",
            "overrides": {
                "SpellLevel": 0,
                # El catálogo indica ProcChance 50; el aura muestra m1=40 y el script nativo
                # reduce a la mitad la probabilidad para los hechizos que no son Arcane Blast.
                "ProcChance": 50,
                "EffectBasePoints_1": 40,
                "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 400589,
            },
            # Copia de spell_proc -44404: Arcane Blast, Fireball y Frostbolt.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 3,
                "SpellFamilyMask0": 536870945, "SpellFamilyMask1": 36864,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Auxiliar: copia el beneficio nativo de Missile Barrage sobre Arcane Missiles.
            "id": 400589, "client": True, "template": 44401,
            "name": "Missile Barrage", "script": "spell_mage_missile_barrage_proc",
            "inherit_server": True,
            "overrides": {"SpellLevel": 0},
            # Copia de spell_proc 44401: se consume con hechizos y conserva una carga.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 3,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 0, "ProcFlags": 69632,
                "SpellTypeMask": 5, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 8, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 1,
            },
        },
        {  # Spellfrost Bolt reutiliza el impacto y la ralentización de Frostfire Bolt.
            "id": 412532, "client": True, "template": 47610,
            "skill_line": SKILL_FROST,
            "name": "Spellfrost Bolt", "script": "spell_mage_frostfire_bolt",
            "inherit_server": True,
            "desc": "Launches a bolt of spellfrost at the enemy, causing Spellfrost damage "
                    "and slowing movement speed by 40% for 9 sec. This spell is checked "
                    "against the lower of the target's Frost and Arcane resistances and "
                    "counts as both Frost and Arcane damage.",
            "bonus": {"direct": 0.814, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "SpellLevel": 0,
                "ManaCostPct": 12,
                "RecoveryTime": 0,
                "SchoolMask": 80,  # Arcane | Frost.
                "DurationIndex": duration_9s,
                "SpellIconID": idx["icon"]["spell_fire_blueflamebolt"],
            },
        },
        {  # Brain Freeze conserva el proc de Escarcha de WotLK y apunta al aura auxiliar.
            "id": 400731, "client": True, "template": 44549,
            "skill_line": SKILL_FROST,
            "name": "Brain Freeze", "script": "spell_mage_brain_freeze",
            "inherit_server": True,
            "desc": "Your Frost damage spells with chilling effects have a 20% chance to "
                    "make your next Fireball, Spellfrost Bolt, Balefire Bolt, or Frostfire "
                    "Bolt instant and cost no mana.",
            "overrides": {
                "SpellLevel": 0,
                "ProcChance": 20,
                "EffectTriggerSpell_1": 400730,
                "SpellIconID": idx["icon"]["ability_mage_brainfreeze"],
            },
            # Copia de spell_proc -44546: disparos mágicos de la familia de mago.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 3,
                "SpellFamilyMask0": 736, "SpellFamilyMask1": 4096,
                "SpellFamilyMask2": 0, "ProcFlags": 69632,
                "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Aura auxiliar que vuelve instantáneo el siguiente hechizo compatible.
            "id": 400730, "client": True, "template": 44545,
            "name": "Brain Freeze", "inherit_server": True,
            # Copia de spell_proc 44545: el id nuevo no la hereda.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 3,
                "SpellFamilyMask0": 1049120, "SpellFamilyMask1": 4096, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 15, "Cooldown": 0, "Charges": 0,
            },
            "desc": "Your next eligible Fire or Frost spell is instant and costs no mana.",
            "overrides": {"SpellLevel": 0},
        },
        {  # Chronostatic Preservation guarda la carga y libera una Flash Heal de WotLK.
            "id": 436516, "client": True, "template": 48071,
            "skill_line": SKILL_ARCANE,
            "name": "Chronostatic Preservation",
            "script": "spell_sod_mage_chronostatic_preservation",
            "inherit_server": True,
            "desc": "Fuse Arcane, Fire, and Frost magic into a stored charge lasting 20 sec. "
                    "Cast again on a friendly target to release the charge as a heal. This "
                    "spell counts as Arcane, Fire, and Frost magic.",
            "overrides": {
                "SpellLevel": 0,
                "ManaCostPct": 24,
                "RecoveryTime": 0,
                "CategoryRecoveryTime": 0,
                "SchoolMask": 84,  # Arcane | Fire | Frost.
                "SpellIconID": idx["icon"]["spell_holy_flashheal"],
                "SpellClassSet": 3,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": EFFECT_DUMMY, "EffectAura_1": 0,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ALLY,
                "EffectRadiusIndex_1": 0,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Spell Power conserva el modificador de daño crítico de su talento WotLK.
            "id": 412322, "client": True, "template": 35581,
            "skill_line": SKILL_ARCANE,
            "name": "Spell Power", "inherit_server": True,
            "desc": "Increases the critical strike damage bonus of all spells by 15%.",
            "overrides": {
                "SpellLevel": 0,
                "EffectBasePoints_1": 49,
                "EffectDieSides_1": 0,
                "EffectMiscValue_1": 15,
                "SpellIconID": idx["icon"]["spell_arcane_arcanepotency"],
            },
        },
        {  # Advanced Warding es una pasiva; sus efectos sobre escudos están en el script local.
            "id": 412115, "client": True, "template": 6143,
            "skill_line": SKILL_ARCANE,
            "name": "Advanced Warding", "script": "spell_sod_mage_advanced_warding",
            "inherit_server": True,
            "desc": "Mana Shield, Frost Ward, and Fire Ward can be cast on any friendly "
                    "target and absorb 100% more damage. Mana Shield uses 50% less mana "
                    "per damage absorbed. Remove Lesser Curse is replaced with Remove "
                    "Greater Curse.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "AttributesEx": 0,
                "CastingTimeIndex": cast_instant,
                "DurationIndex": idx["dur"][0],
                "RangeIndex": range_self,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellLevel": 0,
                "SpellClassSet": 3,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["spell_frost_frostward"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectRadiusIndex_1": 0,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 50, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "EffectRadiusIndex_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Aura oculta que limita a 20 s el almacenamiento de Chronostatic Preservation.
            "id": 900070, "client": False, "template": None,
            "name": "Chronostatic Preservation Storage",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "AttributesEx": 0,
                "CastingTimeIndex": cast_instant,
                "DurationIndex": duration_20s,
                "RangeIndex": range_self,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SchoolMask": 84,
                "SpellClassSet": 3,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "EquippedItemClass": -1, "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
    ]
