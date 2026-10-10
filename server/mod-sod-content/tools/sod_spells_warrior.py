#!/usr/bin/env python3
"""Warrior spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)

# Líneas de habilidad del guerrero (controlan la pestaña del libro de hechizos).
SKILL_ARMS = 26
SKILL_FURY = 256
SKILL_PROTECTION = 257

# Auras nativas de 3.3.5a que usan las runas del guerrero (SpellAuraDefines.h del core).
AURA_MOD_IGNORE_SHAPESHIFT = 275      # anula el requisito de actitud; filtra por máscara de familia
AURA_ABILITY_IGNORE_AURASTATE = 262   # ignora el estado del lanzador; con MiscValue 1 también el combate
AURA_ADD_PCT_MODIFIER = 108
SPELLMOD_DOT = 22                     # SpellModOp 22 de 3.3.5a: daño periódico

EFFECT_WEAPON_PERCENT_DAMAGE = 31

# Máscaras de familia de WotLK (SpellClassSet 4) de los hechizos nativos que se modifican.
MASK_REND = 0x20
MASK_CHARGE = 0x1
MASK_INTERCEPT = 0x40000000
MASK_INTERVENE = 0x10000


def build(idx):
    """Return Warrior spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    range_melee = idx["range"][5.0]

    return [
        {  # Devastate: retain the WotLK rank effects.
            "id": 403195, "client": True, "template": 47498,
            "skill_line": 257,
            "name": "Devastate", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
        {  # Frenesí sangriento: Desgarrar en actitud rabiosa (aura 275) y +100 % de su daño
           # periódico (aura 108 + SpellModOp 22), ambos sobre la máscara de Desgarrar. El
           # daño extra por poder de ataque lo suma el script `spell_sod_warrior_blood_frenzy`
           # en cada tick de Desgarrar.
            "id": 412507, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Blood Frenzy",
            "desc": "Rend can now be used in Berserker stance, Rend's damage is increased by "
                    "$s2%, and Rend deals additional damage equal to $s3% of your Attack "
                    "Power each time it deals damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_bloodfrenzy"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "EffectSpellClassMaskA_1": MASK_REND,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_ADD_PCT_MODIFIER,
                "EffectBasePoints_2": 100, "EffectDieSides_2": 0, "EffectMiscValue_2": SPELLMOD_DOT,
                "EffectSpellClassMaskA_2": MASK_REND,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": 4, "EffectDieSides_3": 0,
                "EffectSpellClassMaskA_3": MASK_REND,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Flagelación: pasiva de marcador; el script de unidad `unit_sod_warrior_flagellation`
           # concede la ira del daño físico recibido como si no hubiera armadura.
            "id": 402877, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Flagellation",
            "desc": "You gain Rage from Physical damage taken as if you were wearing no armor.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_bloodbath"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Arremetida enfurecida: 115 % de daño con arma. El script `spell_sod_warrior_raging_blow`
           # exige Enfurecer, Ira rabiosa o Ira sangrienta, y el reductor de enfriamiento vive en
           # `player_sod_warrior_raging_blow`.
            "id": 402911, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Raging Blow", "script": "spell_sod_warrior_raging_blow",
            "desc": "A ferocious strike that deals $s1% weapon damage, but can only be used "
                    "while Enrage, Berserker Rage, or Bloodrage is active. Each other melee "
                    "ability used while Enrage, Berserker Rage, or Bloodrage is active reduces "
                    "Raging Blow's remaining cooldown by $s3 sec.",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_melee, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 8000, "CategoryRecoveryTime": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_savageblow"],
                "Effect_1": EFFECT_WEAPON_PERCENT_DAMAGE, "EffectBasePoints_1": 114,
                "EffectDieSides_1": 1, "EffectAura_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": EFFECT_DUMMY, "EffectBasePoints_2": 1, "EffectDieSides_2": 0,
                "EffectAura_2": 0, "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Belisario: las auras 262 (MiscValue 1) y 275 hacen Cargar, Interceptar e Intervenir
           # usables en combate y en cualquier actitud; el script `spell_sod_warrior_warbringer`
           # quita los efectos de reducción de movimiento al activarlas.
            "id": 425421, "client": True, "template": 774,
            "skill_line": SKILL_PROTECTION,
            "name": "Warbringer",
            "desc": "Your Charge, Intercept, and Intervene abilities are now usable while in "
                    "combat and in any stance, and will all remove movement impairing effects "
                    "when activated.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_warbringer"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_ABILITY_IGNORE_AURASTATE,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0, "EffectMiscValue_1": 1,
                "EffectSpellClassMaskA_1": MASK_CHARGE,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "EffectSpellClassMaskA_2": MASK_CHARGE | MASK_INTERCEPT,
                "EffectSpellClassMaskB_2": MASK_INTERVENE,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Grito de orden: clon del Grito de orden de WotLK (47440), que el core ya implementa.
           # Diferencia conocida: en 3.3.5a el grito sube la salud máxima (aura 230) y SoD el
           # aguante (aura 29); se conserva el comportamiento nativo del cliente.
            "id": 403215, "client": True, "template": 47440,
            "skill_line": SKILL_FURY,
            "name": "Commanding Shout", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
    ]
