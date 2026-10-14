#!/usr/bin/env python3
"""Especificaciones de hechizos de mago clonados de rangos de WotLK (runas posteriores a la fase 1)."""

from sod_dbc import *  # noqa: F401,F403 (constantes compartidas de WoW)

SKILL_FROST = 6


def build(idx):
    """Devuelve los hechizos de mago clonados de rangos de WotLK."""
    cast_3s = idx["cast"][3000]
    duration_9s = idx["dur"][9000]

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
    ]
