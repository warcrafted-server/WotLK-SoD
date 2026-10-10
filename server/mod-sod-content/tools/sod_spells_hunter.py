#!/usr/bin/env python3
"""Hunter spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403

SKILL_BEAST_MASTERY = 50
SKILL_SURVIVAL = 51
SKILL_MARKSMANSHIP = 163
EFFECT_WEAPON_PERCENT_DAMAGE = 31


def build(idx):
    """Return Hunter spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    duration_10000 = idx["dur"][10000]
    range_self = idx["range"][0.0]
    range_35 = idx["range"][35.0]
    icon_master_marksman = idx["icon"]["ability_hunter_mastermarksman"]
    icon_beast_mastery = idx["icon"]["ability_hunter_beastmastery"]
    icon_cobra_strikes = idx["icon"]["ability_hunter_cobrastrikes"]
    icon_lone_wolf = idx["icon"]["ability_hunter_pet_wolf"]
    icon_flanking_strike = idx["icon"]["ability_hunter_swiftstrike"]
    icon_kill_shot = idx["icon"]["ability_hunter_assassinate2"]

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
        {  # Keep the WotLK Explosive Shot script and apply SoD costs.
            "id": 409552, "client": True, "template": 60053,
            "skill_line": SKILL_SURVIVAL,
            "name": "Explosive Shot", "script": "spell_hun_explosive_shot",
            "inherit_server": True,
            "overrides": {
                "CategoryRecoveryTime": 0,
                "ManaCostPct": 4,
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
        # --- Bestialidad ---
        {  # Bestialidad: pasiva de pecho. Las mejoras de mascota las aplica el aura 900056
           # mediante spell_pet_auras; el efecto dummy sólo alimenta el $s1 y el $s3 del texto.
           # El Bramido provoca con el script propio enganchado a 2649.
            "id": 409368, "client": True, "template": 774,
            "skill_line": SKILL_BEAST_MASTERY,
            "name": "Beast Mastery",
            "desc": "Your pet's damage and health are increased by $s1%, and its Focus regeneration by $s3%. In addition, your pet's Growl now also Taunts the target to attack it for $409372d.",
            "aura_desc": "Your pet's damage and health are increased by $s1%, and its Focus regeneration by $s3%.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 9, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_beast_mastery,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 14, "EffectDieSides_1": 1,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 14, "EffectDieSides_2": 1,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": 49, "EffectDieSides_3": 1,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Aura de mascota de Bestialidad (sólo servidor): +15 % daño, +15 % salud y
           # +50 % regeneración de enfoque.
            "id": 900056, "client": False, "template": None,
            "name": "Beast Mastery",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "SpellClassSet": 9, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "DurationIndex": duration_perm, "RangeIndex": range_self,
                "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectBasePoints_1": 14, "EffectDieSides_1": 1, "EffectMiscValue_1": 127,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 133,
                "EffectBasePoints_2": 14, "EffectDieSides_2": 1, "EffectMiscValue_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_MOD_POWER_REGEN_PERCENT,
                "EffectBasePoints_3": 49, "EffectDieSides_3": 1, "EffectMiscValue_3": 2,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Golpes de cobra: conserva el proc y el script nativos de WotLK (spell_hun_cobra_strikes,
           # registrado al id 425713 en sod_hunter_runes.sql). Dispara el buff 425714 en la mascota.
            "id": 425713, "client": True, "template": 53256,
            "skill_line": SKILL_BEAST_MASTERY,
            "name": "Cobra Strikes", "script": "spell_hun_cobra_strikes",
            "inherit_server": True,
            "desc": "Your critical hits with Shot and Strike abilities and with Mongoose Bite cause your pet's next $425714u special attacks to critically hit.",
            "aura_desc": "Your critical hits with Shot and Strike abilities and with Mongoose Bite cause your pet's next special attacks to critically hit.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellIconID": icon_cobra_strikes,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SpellLevel": 0, "ProcChance": 100,
                "EffectBasePoints_1": 4, "EffectDieSides_1": 1,
                "EffectTriggerSpell_1": 425714,
            },
            # Copia de spell_proc -53256 (familia 9, sólo golpes críticos con capacidad de daño).
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 9,
                "SpellFamilyMask0": 2048, "SpellFamilyMask1": 8388609,
                "SpellFamilyMask2": 0, "ProcFlags": 0, "SpellTypeMask": 0,
                "SpellPhaseMask": 2, "HitMask": 2, "AttributesMask": 0,
                "DisableEffectsMask": 0, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Buff de Golpes de cobra: clon de 53257; el script del core le pasa las 2 cargas.
            "id": 425714, "client": True, "template": 53257,
            "name": "Cobra Strikes", "inherit_server": True,
            # El script y el spell_proc del core están ligados al id 53257: el clon no los hereda, y sin ellos
            # las cargas no se gastan.
            "script": "spell_hun_cobra_strikes_triggered",
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 9,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 268435456, "SpellFamilyMask2": 0,
                "ProcFlags": 16, "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 2, "AttributesMask": 8, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "aura_desc": "Your next $u special attacks critically hit.",
            "overrides": {
                "SpellClassSet": 9,
                "SpellIconID": icon_cobra_strikes, "SpellLevel": 0,
                "CumulativeAura": 2,
            },
        },
        {  # Lobo solitario: pasiva con sondeo de 1 s que aplica o retira el bono 900057.
            "id": 415370, "client": True, "template": 774,
            "skill_line": SKILL_BEAST_MASTERY,
            "name": "Lone Wolf", "script": "spell_sod_hunter_lone_wolf",
            "desc": "You deal $s1% increased damage with all attacks while you do not have an active pet.",
            "aura_desc": "You deal $s1% increased damage while you do not have an active pet.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 9, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_lone_wolf,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_1": 24, "EffectDieSides_1": 1,
                "EffectAuraPeriod_1": 1000, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 24, "EffectDieSides_2": 1,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Bono de Lobo solitario (sólo servidor): +25 % a todas las escuelas sin mascota.
            "id": 900057, "client": False, "template": None,
            "name": "Lone Wolf",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "SpellClassSet": 9, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "DurationIndex": duration_perm, "RangeIndex": range_self,
                "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectBasePoints_1": 24, "EffectDieSides_1": 1, "EffectMiscValue_1": 127,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Golpe de flanco: golpe cuerpo a cuerpo instantáneo que aplica un +8 % de daño propio
           # durante 10 s. El ataque simultáneo de la mascota y el reinicio de su enfriamiento no
           # se implementan (requieren guion sobre las habilidades básicas de la mascota); ver TODO.md.
            "id": 415320, "client": True, "template": 1495,
            "skill_line": SKILL_SURVIVAL,
            "name": "Flanking Strike", "inherit_server": True,
            "desc": "You and your pet deal simultaneous instant $s2% melee damage. Afterward, you deal $s3% increased damage for $d, stacking up to $u times. Your pet's Basic attacks have a $s4% chance to reset the cooldown on Flanking Strike.",
            "aura_desc": "All damage increased by $s3%.",
            "overrides": {
                "CategoryRecoveryTime": 30000, "RecoveryTime": 0,
                "ManaCostPct": 2, "DurationIndex": duration_10000,
                "SpellIconID": icon_flanking_strike, "SpellLevel": 0,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "CumulativeAura": 5,
                # EFFECT_0: 100 % del daño del arma (efecto 31, base+1).
                "Effect_1": EFFECT_WEAPON_PERCENT_DAMAGE, "EffectAura_1": 0,
                "EffectBasePoints_1": 99, "EffectDieSides_1": 1,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                # EFFECT_1: +8 % a todo el daño propio durante 10 s.
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectBasePoints_2": 7, "EffectDieSides_2": 1, "EffectMiscValue_2": 127,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                # EFFECT_2: dummy con el 50 % de probabilidad de reinicio para el tooltip.
                "Effect_3": EFFECT_DUMMY, "EffectAura_3": 0,
                "EffectBasePoints_3": 50, "EffectDieSides_3": 0,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Disparo mortal: clon del de WotLK (17 + 31) con daño, coste, alcance y reutilización
           # de SoD. El script propio reinicia el enfriamiento si el objetivo queda al 20 % o menos.
            "id": 409593, "client": True, "template": 53351,
            "skill_line": SKILL_MARKSMANSHIP,
            "name": "Kill Shot", "script": "spell_sod_hunter_kill_shot",
            "inherit_server": True,
            "desc": "You attempt to finish off a wounded target, firing a ranged attack dealing $s2% weapon damage plus ${$m1/100*$m2/100*$<damagepower>}. Kill Shot has no minimum range. Kill Shot's cooldown is reset if used on an enemy that has 20% or less health.",
            "overrides": {
                "CategoryRecoveryTime": 0, "RecoveryTime": 12000,
                "ManaCostPct": 3, "RangeIndex": range_35,
                "SpellIconID": icon_kill_shot, "SpellLevel": 0,
                "EffectBasePoints_1": 586, "EffectDieSides_1": 1,
                "EffectBasePoints_2": 99, "EffectDieSides_2": 1,
            },
        },
    ]
