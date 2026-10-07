#!/usr/bin/env python3
"""Druid spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)


SKILL_RESTORATION = 573
SKILL_FERAL_COMBAT = 134
SKILL_BALANCE = 574
AURA_MOD_IGNORE_SHAPESHIFT = 275  # Core SpellAuraDefines.h
AURA_PROC_TRIGGER_SPELL = 42  # Core SpellAuraDefines.h


def build(idx):
    """Return Druid spells cloned from the level-80 WotLK ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    duration_60s = idx["dur"][60000]
    duration_6s = idx["dur"][6000]
    duration_10s = idx["dur"][10000]
    duration_12s = idx["dur"][12000]
    duration_2s = idx["dur"][2000]
    range_self = idx["range"][0.0]
    range_13 = idx["range"][13.0]
    range_30 = idx["range"][30.0]
    range_100 = idx["range"][100.0]
    icon_survival = idx["icon"]["spell_nature_spiritwolf"]
    icon_mangle = idx["icon"]["ability_druid_mangle2"]
    icon_question = idx["icon"]["inv_misc_questionmark"]
    icon_windfury = idx["icon"]["spell_nature_windfury"]
    icon_tigers_fury = idx["icon"]["ability_mount_jungletiger"]
    icon_skull_bash = idx["icon"]["spell_druid_feralchargecat"]
    icon_frenzied_regeneration = idx["icon"]["ability_bullrush"]
    icon_swipe = idx["icon"]["inv_misc_monsterclaw_03"]
    icon_barkskin = idx["icon"]["spell_nature_stoneclawtotem"]
    icon_sunfire = idx["icon"]["spell_nature_wrath"]
    icon_tree_of_life = idx["icon"]["spell_nature_rejuvenation"]

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
        {  # Mangle dispatches to a max-rank WotLK form spell with SoD effect values.
            "id": 407995, "client": True, "template": 48564,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Mangle", "script": "spell_sod_druid_mangle",
            "inherit_server": True,
            "desc": "Mangle the target for 160% normal damage and cause it to take "
                    "30% additional damage from Bleed effects and Shred for 60 sec. "
                    "This ability benefits from and triggers all effects associated "
                    "with Claw and Maul. In Bear Form, hitting a target also grants "
                    "4 Attack Power for each point of Defense above 5 times your level "
                    "for 60 sec.",
            "aura_desc": "All Bleed effects and Shred cause 30% additional damage.",
            "overrides": {
                "Attributes": 0, "AttributesEx": 0,
                "ShapeshiftMask": 145,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_60s,
                "CategoryRecoveryTime": 6000, "RecoveryTime": 0,
                "StartRecoveryCategory": 133, "StartRecoveryTime": 1500,
                "RangeIndex": idx["range"][5.0], "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_mangle, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0x440,
                "SpellClassMask_3": 0,
                "Effect_1": EFFECT_DUMMY, "EffectAura_1": 0,
                "EffectBasePoints_1": 0, "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Gore's proc filters use the WotLK Druid family masks.
            "id": 417145, "client": True, "template": 774,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Gore", "script": "spell_sod_druid_gore",
            "desc": "Striking a target with Lacerate, Swipe, or Maul has a 15% chance "
                    "to reset the cooldown on Mangle (Bear) and grant 10 Rage. "
                    "Striking a target with Mangle (Cat) or Shred has a 15% chance "
                    "to reset the cooldown on Tiger's Fury.",
            "aura_desc": "Striking a target with Lacerate, Swipe, or Maul has a 15% "
                         "chance to reset the cooldown on Mangle (Bear) and grant "
                         "10 Rage. Striking a target with Mangle (Cat) or Shred has a "
                         "15% chance to reset the cooldown on Tiger's Fury.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": idx["range"][0.0], "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_question, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "SpellClassMask_1": 0x8800, "SpellClassMask_2": 0x00100540,
                "SpellClassMask_3": 0x00000800,
                "ProcTypeMask": 16, "ProcChance": 100,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 7,
                "SpellFamilyMask0": 0x8800,
                "SpellFamilyMask1": 0x00100540,
                "SpellFamilyMask2": 0x00000800,
                "ProcFlags": 16, "SpellTypeMask": 1,
                "SpellPhaseMask": 2, "HitMask": 0,
                "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100,
                "Cooldown": 100, "Charges": 0,
            },
        },
        {  # Defender's Resolve supplies the dynamic Bear Mangle Attack Power aura.
            "id": 460171, "client": True, "template": 774,
            "name": "Defender's Resolve",
            "aura_desc": "Attack Power increased by $w1.",
            "overrides": {
                "Attributes": 0, "AttributesEx": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_60s,
                "RangeIndex": idx["range"][0.0], "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_question, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 99,
                "EffectBasePoints_1": 4, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 124,
                "EffectBasePoints_2": 4, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Wild Strikes is maintained on eligible raid members by its rune driver.
            "id": 407975, "client": True, "template": 8515,
            "name": "Wild Strikes", "script": "spell_sod_druid_wild_strikes_proc",
            "desc": "Party members within $a1 yards gain increased combat ferocity. "
                    "Each melee hit has a $h% chance of granting the attacker an extra "
                    "attack with $s1% additional Attack Power. No effect if the attacker "
                    "is already benefitting from Windfury Totem.",
            "aura_desc": "Chance to gain extra attacks.",
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 0,
                "ProcFlags": 0x00C00014,
                "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100, "Cooldown": 0, "Charges": 0,
            },
            "overrides": {
                "Attributes": 0, "AttributesEx": 0,
                "ShapeshiftMask": 0, "AuraInterruptFlags": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_6s,
                "RangeIndex": range_self, "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_windfury, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "ProcTypeMask": 0x00C00014, "ProcChance": 20,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectAuraPeriod_1": 0, "EffectBasePoints_1": 20,
                "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectRadiusIndex_1": 12,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # The rune's passive driver polls form and nearby party or raid members.
            "id": 407977, "client": True, "template": 774,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Wild Strikes", "script": "spell_sod_druid_wild_strikes",
            "desc": "While you are in Cat Form, Bear Form, or Dire Bear Form, party or raid "
                    "members within $407975a1 yards gain increased combat ferocity. Each melee "
                    "hit has a $407975h% chance of granting the attacker an extra attack with "
                    "$407975s1% additional Attack Power. No effect if the target is already "
                    "benefitting from Windfury Totem.",
            "aura_desc": "Chance to gain extra attacks.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_windfury, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectAuraPeriod_1": 1000, "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectRadiusIndex_1": 0,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # SoD's Tiger's Fury helper applies the physical damage buff and energy gain.
            "id": 417045, "client": True, "template": 5217,
            "name": "Tiger's Fury",
            "desc": "Increases damage done by $s1% for $d and instantly grants you $s2 Energy.",
            "aura_desc": "Increases damage done by $s1%.",
            "overrides": {
                "Attributes": 0, "AttributesEx": 0,
                "ShapeshiftMask": 0, "AuraInterruptFlags": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_6s,
                "RangeIndex": range_self, "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_tigers_fury, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA,
                "EffectAura_1": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectAuraPeriod_1": 0, "EffectBasePoints_1": 15,
                "EffectDieSides_1": 0, "EffectMiscValue_1": 1,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 30, "EffectAura_2": 0,
                "EffectBasePoints_2": 60, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 3,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # The rune spell is a hidden marker checked by the Tiger's Fury script.
            "id": 417046, "client": False, "template": None,
            "name": "King of the Jungle",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_tigers_fury, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Hidden form watcher lets the Tiger's Fury helper persist outside Cat Form.
            "id": 900015, "client": False, "template": None,
            "name": "Tiger's Fury Form Watch",
            "script": "spell_sod_druid_king_of_the_jungle_form_watch",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "ShapeshiftMask": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_6s,
                "RangeIndex": range_self, "PowerType": 0,
                "ManaCost": 0, "ManaCostPct": 0, "SchoolMask": 1,
                "EquippedItemClass": -1, "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA,
                "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectAuraPeriod_1": 250, "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Skull Bash charges like Bear Feral Charge and triggers the school interrupt.
            "id": 410176, "client": True, "template": 16979,
            "inherit_server": True,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Skull Bash", "script": "spell_sod_druid_skull_bash",
            "desc": "Charge to a target within 13 yards and bash the target's skull, "
                    "interrupting spellcasting and preventing any spell in that school "
                    "from being cast for $414621d. Shares a cooldown with Feral Charge.",
            "overrides": {
                "Category": 1205, "RecoveryTime": 10000,
                "CategoryRecoveryTime": 10000,
                "StartRecoveryCategory": 133, "StartRecoveryTime": 1000,
                "ShapeshiftMask": 145,
                "CastingTimeIndex": cast_instant, "DurationIndex": 0,
                "RangeIndex": range_13, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_skull_bash, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0,
                "SpellClassMask_3": 0,
                "Effect_1": 96, "EffectAura_1": 0,
                "EffectBasePoints_1": 0, "EffectMechanic_1": 26,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "EffectTriggerSpell_1": 0,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "EffectTriggerSpell_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
                "EffectTriggerSpell_3": 0,
            },
        },
        {  # Hidden interrupt spell; the core applies the interrupted school's lockout.
            "id": 414621, "client": True, "template": 1766,
            "inherit_server": True,
            "name": "Skull Bash",
            "desc": "You bash the target's skull, interrupting spellcasting and preventing "
                    "any spell in that school from being cast for $d.",
            "overrides": {
                "Attributes": SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_2s,
                "RangeIndex": range_100, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_skull_bash, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0,
                "SpellClassMask_3": 0,
                "Effect_1": 68, "EffectAura_1": 0,
                "EffectBasePoints_1": 0, "EffectMechanic_1": 26,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Rune tooltip helper with the SoD conversion limits and duration.
            "id": 428708, "client": True, "template": 774,
            "name": "Frenzied Regeneration",
            "desc": "Converts Rage, Energy, and base Mana into health every second for $d.",
            "aura_desc": "Converting resources into health.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_10s,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_frenzied_regeneration, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectAuraPeriod_1": 1000, "EffectBasePoints_1": 9,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 9, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": 19, "EffectDieSides_3": 0,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # The visible rune marker grants a form exception and handles non-Rage resources.
            "id": 431389, "client": True, "template": 774,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Improved Frenzied Regeneration",
            "script": "spell_sod_druid_improved_frenzied_regeneration_rune",
            "desc": "Your Frenzied Regeneration can now be used in all forms except Moonkin "
                    "Form or while not shapeshifted. It now converts your active resource "
                    "into health every second for $428708d. Up to $428708s1 Rage, "
                    "$428708s2 Energy, or $428708s3% base Mana is converted per second "
                    "into up to 10% health.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_frenzied_regeneration, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # SoD's Cat Swipe keeps the WotLK weapon damage and adds one combo point.
            "id": 411128, "client": True, "template": 62078,
            "inherit_server": True,
            "name": "Swipe (Cat)",
            "desc": "Swipe nearby enemies, inflicting $s1% weapon damage and generating "
                    "$s2 combo point(s) on your current target.",
            "overrides": {
                "Attributes": SPELL_ATTR0_DO_NOT_DISPLAY,
                "SpellIconID": icon_swipe, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "PowerType": 3, "ManaCost": 50, "ManaCostPct": 0,
                "Effect_1": 31, "EffectBasePoints_1": 249,
                "Effect_2": 80, "EffectAura_2": 0,
                "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "EffectChainTargets_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
                "ImplicitTargetA_3": 0,
            },
        },
        {  # The rune marker is checked by the Bear target cap and Cat Swipe redirect.
            "id": 439510, "client": True, "template": 774,
            "skill_line": SKILL_FERAL_COMBAT,
            "name": "Improved Swipe",
            "desc": "While in Cat Form, your Swipe ability becomes Swipe (Cat), and while "
                    "in Bear Form, your Swipe ability strikes up to $s1 additional enemies.\n\n"
                    "Swipe (Cat)\n$@spellicon411128\n$@spelldesc411128",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_swipe, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 6,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # The client and server need this family-scoped form exception aura.
            "id": 900016, "client": True, "template": 774,
            "name": "Frenzied Regeneration Form Permit",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_frenzied_regeneration, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "SpellClassMask_1": 0, "SpellClassMask_2": 1073741824,
                "SpellClassMask_3": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 275,
                "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # WotLK Barkskin already has no speed penalties and works in every form.
            "id": 431388, "client": True, "template": 774,
            "name": "Improved Barkskin",
            "desc": "Your Barkskin can now be cast on allies, no longer penalizes melee "
                    "combat speed or spellcasting time, and can be cast while shapeshifted.",
            "aura_desc": "Your Barkskin can now be cast on allies, no longer penalizes melee "
                         "combat speed or spellcasting time, and can be cast while shapeshifted.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 1,
                "SpellIconID": icon_barkskin, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA,
                "EffectAura_1": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_1": 0,
                "EffectSpellClassMaskB_1": 262144,
                "EffectSpellClassMaskC_1": 0,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Sunfire uses Moonfire's rank-14 damage profile with Nature damage.
            "id": 414684, "client": True, "template": 48463,
            "skill_line": SKILL_BALANCE,
            "name": "Sunfire", "inherit_server": False,
            "desc": "Burns the enemy for $s1 Nature damage and then an additional "
                    "$o2 Nature damage over $d sec.",
            "scale_to_level": {"effects": [1, 2], "level": 80},
            "bonus": {"direct": 0.13, "dot": 0.13, "ap": 0, "ap_dot": 0},
            "overrides": {
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_12s,
                "RangeIndex": range_30, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 16, "SchoolMask": 8,
                "SpellIconID": icon_sunfire, "EquippedItemClass": -1,
                "SpellLevel": 0,
            },
        },
        {  # Living Seed reuses the WotLK rank-3 Restoration talent behavior.
            "id": 414677, "client": True, "template": 48500,
            "skill_line": SKILL_RESTORATION,
            "name": "Living Seed", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
        {  # Gale Winds applies its Hurricane-only SpellMods in the rune script.
            "id": 417135, "client": True, "template": 774,
            "skill_line": SKILL_BALANCE,
            "name": "Gale Winds", "script": "spell_sod_druid_gale_winds",
            "desc": "Increases the damage done by your Hurricane by 20%, removes its "
                    "cooldown, and reduces its mana cost by 30%.",
            "aura_desc": "Hurricane damage increased by 20%, mana cost reduced by 30%, "
                         "and cooldown removed.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 8,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 19, "EffectMiscValue_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": -29, "EffectMiscValue_2": 14,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": -99, "EffectMiscValue_3": 11,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Wrath reduces its mana cost and can empower the next Healing Touch.
            "id": 414799, "client": True, "template": 774,
            "skill_line": SKILL_RESTORATION,
            "name": "Fury of Stormrage", "script": "spell_sod_druid_fury_of_stormrage",
            "desc": "Reduces the mana cost of Wrath by 100%. Each time Wrath deals damage, "
                    "you have a 12% chance for your next Healing Touch within 15 sec to be "
                    "instant and castable in any shapeshift form.",
            "aura_desc": "Wrath costs no mana. Wrath damage has a 12% chance to make your "
                         "next Healing Touch instant and castable in any form for 15 sec.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 8,
                "SpellIconID": icon_sunfire, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "ProcTypeMask": 0x00010000, "ProcChance": 12,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": -99, "EffectMiscValue_1": 14,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_PROC_TRIGGER_SPELL,
                "EffectBasePoints_2": -99,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 0,
                "ProcFlags": 0x00010000, "SpellTypeMask": 1,
                "SpellPhaseMask": 2, "HitMask": 0,
                "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100,
                "Cooldown": 0, "Charges": 0,
            },
        },
        {  # The proc buff makes Healing Touch instant, form-independent, and one-use.
            "id": 900017, "client": True, "template": 774,
            "name": "Fury of Stormrage",
            "desc": "Your next Healing Touch is instant and can be cast in any shapeshift form.",
            "aura_desc": "Your next Healing Touch is instant and can be cast in any shapeshift form.",
            "overrides": {
                "Attributes": 0, "CastingTimeIndex": cast_instant,
                "DurationIndex": idx["dur"][15000], "RangeIndex": range_self,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellIconID": icon_sunfire, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_1": 0, "EffectSpellClassMaskA_1": 0x20,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": -99, "EffectMiscValue_2": 10,
                "EffectSpellClassMaskA_2": 0x20,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": 0,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 7,
                "SpellFamilyMask0": 0x20,
                "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0x00004000, "SpellTypeMask": 2,
                "SpellPhaseMask": 2, "HitMask": 0,
                "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100,
                "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Dreamstate procs on non-periodic spell crits and any Starsurge damage.
            "id": 408258, "client": True, "template": 774,
            "skill_line": SKILL_BALANCE,
            "name": "Dreamstate", "script": "spell_sod_druid_dreamstate",
            "desc": "Your damaging non-periodic spell critical strikes or any damage from "
                    "Starsurge grant you 50% of your mana regeneration while casting for 8 sec "
                    "and increase Arcane and Nature damage dealt to non-player targets by 20% "
                    "for 12 sec.",
            "aura_desc": "Damaging spell critical strikes and Starsurge damage restore 50% "
                         "of your mana regeneration while casting for 8 sec and make non-player "
                         "targets take 20% more Arcane and Nature damage for 12 sec.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 64,
                "SpellIconID": icon_question, "EquippedItemClass": -1,
                "SpellLevel": 0, "SpellClassSet": 7,
                "ProcTypeMask": 0x00010000, "ProcChance": 100,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PROC_TRIGGER_SPELL,
                "EffectBasePoints_1": 50,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 0,
                "ProcFlags": 0x00010000, "SpellTypeMask": 1,
                "SpellPhaseMask": 2, "HitMask": 0,
                "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100,
                "Cooldown": 0, "Charges": 0,
            },
        },
        {  # 50% spirit-based mana regen continues while casting for 8 seconds.
            "id": 900018, "client": True, "template": 774,
            "name": "Dreamstate", "aura_desc": "50% of your mana regeneration continues while casting.",
            "overrides": {
                "Attributes": 0, "CastingTimeIndex": cast_instant,
                "DurationIndex": idx["dur"][8000], "RangeIndex": range_self,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellIconID": icon_question, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 134,
                "EffectBasePoints_1": 49, "EffectMiscValue_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Damage taken debuff: Arcane and Nature each increase by 20% for 12 seconds.
            "id": 900019, "client": True, "template": 774,
            "name": "Dreamstate Magic",
            "aura_desc": "Increases Arcane and Nature damage taken by 20%.",
            "overrides": {
                "Attributes": 0, "CastingTimeIndex": cast_instant,
                "DurationIndex": idx["dur"][12000], "RangeIndex": range_100,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellIconID": icon_question, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 87,
                "EffectBasePoints_1": 19, "EffectMiscValue_1": 64,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 87,
                "EffectBasePoints_2": 19, "EffectMiscValue_2": 8,
                "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Passive approximation of Tree Form: exact self-stat bonuses, no new form enum.
            "id": 439733, "client": True, "template": 774,
            "skill_line": SKILL_RESTORATION,
            "name": "Tree of Life", "script": "spell_sod_druid_tree_of_life",
            "desc": "Increases healing received by 10% for party members within 45 yards, "
                    "Wild Growth healing by 60%, reduces heal over time mana costs by 20%, "
                    "increases Spirit by 25% and armor by 200%.",
            "aura_desc": "Increases Spirit by 25% and armor by 200%. Nearby party members "
                         "receive 10% more healing. Wild Growth healing is increased by 60% "
                         "and heal over time spells cost 20% less mana.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 8,
                "SpellIconID": icon_tree_of_life, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 29,
                "EffectBasePoints_1": 24, "EffectMiscValue_1": 4,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 142,
                "EffectBasePoints_2": 199, "EffectMiscValue_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Helper: HoT cost and Wild Growth healing modifiers plus party refresh.
            "id": 900020, "client": False, "template": 774,
            "name": "Tree of Life Benefits", "script": "spell_sod_druid_tree_of_life_benefits",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "PowerType": 0, "ManaCost": 0,
                "ManaCostPct": 0, "SchoolMask": 8,
                "SpellLevel": 0, "SpellClassSet": 7,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": -19, "EffectMiscValue_1": 14,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 59, "EffectMiscValue_2": 22,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_3": 0, "EffectAuraPeriod_3": 1000,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Refreshed on the Tree of Life helper aura; 10% healing received for 2 sec.
            "id": 900021, "client": True, "template": 774,
            "name": "Tree of Life", "aura_desc": "Increases healing received by 10%.",
            "overrides": {
                "Attributes": 0, "CastingTimeIndex": cast_instant,
                "DurationIndex": idx["dur"][2000], "RangeIndex": range_self,
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellIconID": icon_tree_of_life, "EquippedItemClass": -1,
                "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 118,
                "EffectBasePoints_1": 9,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
    ]
