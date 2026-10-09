/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifndef MODULE_SOD_PALADIN_H
#define MODULE_SOD_PALADIN_H

#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodPaladinSpells
{
    SPELL_SOD_PALADIN_ART_OF_WAR = 426157,
    SPELL_SOD_PALADIN_RIGHTEOUS_VENGEANCE = 440672,
    SPELL_SOD_PALADIN_RIGHTEOUS_VENGEANCE_DOT = 61840,
    SPELL_SOD_PALADIN_IMPROVED_HAMMER_OF_WRATH = 429152,
    SPELL_SOD_PALADIN_PURIFYING_POWER = 429144,
    SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R1 = 429145,
    SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R2 = 429146,
    SPELL_SOD_PALADIN_PURIFYING_POWER_STUN = 429147,
    SPELL_SOD_PALADIN_FANATICISM = 429142,
    SPELL_SOD_PALADIN_FANATICISM_HOT = 426162,
    SPELL_SOD_PALADIN_WRATH = 429139,
    SPELL_SOD_PALADIN_INFUSION_OF_LIGHT = 426065,
    SPELL_SOD_PALADIN_AEGIS = 425589,
    SPELL_SOD_PALADIN_SHEATH_OF_LIGHT = 426158,
    SPELL_SOD_PALADIN_SHEATH_OF_LIGHT_BUFF = 426159,
    SPELL_SOD_PALADIN_GUARDED_BY_THE_LIGHT = 415059,
    SPELL_SOD_PALADIN_GUARDED_BY_THE_LIGHT_BUFF = 415058,
    SPELL_SOD_PALADIN_SHOCK_AND_AWE = 462834,
    SPELL_SOD_PALADIN_SHOCK_AND_AWE_BUFF = 462832,
    SPELL_SOD_PALADIN_HALLOWED_GROUND = 458287,
    SPELL_SOD_PALADIN_BEACON_OF_LIGHT = 407613,
    SPELL_PALADIN_BEACON_OF_LIGHT_AURA = 53563,
    SPELL_SOD_PALADIN_DIVINE_LIGHT = 458856,
    SPELL_SOD_PALADIN_DIVINE_LIGHT_SHIELD = 458857,
    SPELL_SOD_PALADIN_DIVINE_LIGHT_WATCH = 900025,
    SPELL_SOD_PALADIN_SACRED_SHIELD = 412019,
    SPELL_SOD_PALADIN_SACRED_SHIELD_CRIT = 900026,
    SPELL_SOD_PALADIN_SACRED_SHIELD_HOT = 900027,
    SPELL_SOD_PALADIN_SACRED_SHIELD_WATCH = 900028,
    SPELL_PALADIN_SACRED_SHIELD_ABSORB = 58597,
    SPELL_SOD_PALADIN_INSPIRATION_EXEMPLAR = 407880,
    SPELL_SOD_PALADIN_HAND_OF_RECKONING = 407631,
    SPELL_SOD_PALADIN_MALLEABLE_PROTECTION = 458318,
    // Defender's Resolve: hechizo de SoD compartido, definido en sod_spells_druid.py.
    SPELL_SOD_PALADIN_MALLEABLE_PROTECTION_AP = 460171,
    SPELL_PALADIN_RIGHTEOUS_FURY = 25780,
};

void AddSC_sod_paladin_sheath_of_light();
void AddSC_sod_paladin_guarded_by_the_light();
void AddSC_sod_paladin_shock_and_awe();
void AddSC_sod_paladin_hallowed_ground();
void AddSC_sod_paladin_beacon_of_light();
void AddSC_sod_paladin_divine_light();
void AddSC_sod_paladin_sacred_shield();
void AddSC_sod_paladin_inspiration_exemplar();
void AddSC_sod_paladin_hand_of_reckoning();
void AddSC_sod_paladin_malleable_protection();

constexpr uint32 SPELL_PALADIN_REDOUBT_RANKS[] = { 20127, 20130, 20135 };
constexpr uint32 SPELL_PALADIN_REDOUBT_PROC_RANKS[] = { 20128, 20131, 20132 };
// Orden de rangos según Spell.dbc 3.3.5a; 20178 es el efecto disparado, no un rango.
constexpr uint32 SPELL_PALADIN_RECKONING_RANKS[] = { 20177, 20179, 20181, 20180, 20182 };
constexpr uint32 SPELL_PALADIN_HOLY_SHOCK_RANKS[] = { 20473, 20929, 20930, 27174, 33072, 48824, 48825 };
constexpr uint32 SPELL_PALADIN_RECKONING_PROC = 20178;
constexpr uint32 SPELL_PALADIN_HOLY_SHIELD_RANKS[] = { 20925, 20927, 20928, 27179, 48951, 48952 };

constexpr uint32 SPELL_PALADIN_EXORCISM_RANKS[] =
    { 879, 5614, 5615, 10312, 10313, 10314, 27138, 48800, 48801 };
constexpr uint32 SPELL_PALADIN_HAMMER_OF_WRATH_RANKS[] =
    { 24275, 24274, 24239, 27180, 48805 };

// WotLK SpellFamilyFlags read from Spell.dbc for the affected Paladin spells.
constexpr uint32 SOD_PALADIN_WRATH_SPELL_MASK_0 = 0x00200020;
constexpr uint32 SOD_PALADIN_WRATH_SPELL_MASK_1 = 0x00200002;
constexpr uint32 SOD_PALADIN_WRATH_CONSECRATION_MASK_0 = 0x00000020;

inline bool SodPaladinEnabled()
{
    return sConfigMgr->GetOption<bool>("SodPaladin.Enable", true);
}

inline uint32 SodPaladinArtOfWarManaCostReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ArtOfWar.ManaCostReductionPct", 80);
}

inline uint32 SodPaladinArtOfWarCooldownReductionSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ArtOfWar.CooldownReductionSeconds", 2);
}

inline uint32 SodPaladinRighteousVengeanceDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.RighteousVengeance.DamagePct", 30);
}

inline uint32 SodPaladinImprovedHammerOfWrathResetHealthPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ImprovedHammerOfWrath.ResetHealthPct", 10);
}

inline uint32 SodPaladinPurifyingPowerCooldownReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.PurifyingPower.CooldownReductionPct", 50);
}

inline uint32 SodPaladinPurifyingPowerStunSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.PurifyingPower.StunSeconds", 2);
}

inline uint32 SodPaladinFanaticismHolyCritChancePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.Fanaticism.HolyCritChancePct", 18);
}

inline uint32 SodPaladinFanaticismHealingPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.Fanaticism.HealingPct", 60);
}

inline uint32 SodPaladinInfusionOfLightDamageHealingPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.InfusionOfLight.DamageHealingPct", 50);
}

inline uint32 SodPaladinInfusionOfLightCriticalCooldownSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.InfusionOfLight.CriticalCooldownSeconds", 3);
}

inline uint32 SodPaladinAegisBlockValuePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.Aegis.BlockValuePct", 30);
}

inline uint32 SodPaladinAegisRedoubtChancePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.Aegis.RedoubtChancePct", 10);
}

inline uint32 SodPaladinAegisReckoningChancePerPointPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.Aegis.ReckoningChancePerPointPct", 2);
}

inline uint32 SodPaladinSheathOfLightAttackPowerPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SheathOfLight.AttackPowerPct", 30);
}

inline uint32 SodPaladinSheathOfLightDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SheathOfLight.DurationSeconds", 60);
}

inline uint32 SodPaladinGuardedByTheLightManaPctPerTick()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.GuardedByTheLight.ManaPctPerTick", 5);
}

inline uint32 SodPaladinGuardedByTheLightTickSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.GuardedByTheLight.TickSeconds", 3);
}

inline uint32 SodPaladinGuardedByTheLightDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.GuardedByTheLight.DurationSeconds", 15);
}

inline uint32 SodPaladinGuardedByTheLightHealingReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.GuardedByTheLight.HealingReductionPct", 50);
}

inline uint32 SodPaladinShockAndAweIntellectSpellDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ShockAndAwe.IntellectSpellDamagePct", 200);
}

inline uint32 SodPaladinShockAndAweThreatReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ShockAndAwe.ThreatReductionPct", 30);
}

inline uint32 SodPaladinShockAndAweDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.ShockAndAwe.DurationSeconds", 60);
}

inline uint32 SodPaladinHallowedGroundHealingPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.HallowedGround.HealingPct", 200);
}

inline uint32 SodPaladinBeaconOfLightHealingPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.BeaconOfLight.HealingPct", 75);
}

inline uint32 SodPaladinBeaconOfLightDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.BeaconOfLight.DurationSeconds", 3600);
}

inline uint32 SodPaladinDivineLightOverhealShieldPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.DivineLight.OverhealShieldPct", 50);
}

inline uint32 SodPaladinDivineLightShieldDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.DivineLight.ShieldDurationSeconds", 15);
}

inline uint32 SodPaladinSacredShieldCooldownSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SacredShield.CooldownSeconds", 5);
}

inline uint32 SodPaladinSacredShieldFlashOfLightHealPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SacredShield.FlashOfLightHealPct", 100);
}

inline uint32 SodPaladinSacredShieldHotDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SacredShield.HotDurationSeconds", 12);
}

inline uint32 SodPaladinSacredShieldFlashOfLightCritPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SacredShield.FlashOfLightCritPct", 50);
}

inline uint32 SodPaladinSacredShieldFlashOfLightCritSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.SacredShield.FlashOfLightCritSeconds", 6);
}

inline uint32 SodPaladinInspirationExemplarIntervalSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.InspirationExemplar.IntervalSeconds", 4);
}

inline float SodPaladinInspirationExemplarRadiusYards()
{
    return sConfigMgr->GetOption<float>("SodPaladin.InspirationExemplar.RadiusYards", 10.0f);
}

inline uint32 SodPaladinHandOfReckoningManaRestorePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.HandOfReckoning.ManaRestorePct", 25);
}

inline uint32 SodPaladinHandOfReckoningDamageThresholdPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.HandOfReckoning.DamageThresholdPct", 35);
}

inline uint32 SodPaladinHandOfReckoningDamageReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.HandOfReckoning.DamageReductionPct", 20);
}

inline uint32 SodPaladinMalleableProtectionDurationIncreasePct()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.MalleableProtection.DurationIncreasePct", 50);
}

inline uint32 SodPaladinMalleableProtectionAttackPowerPerDefense()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.MalleableProtection.AttackPowerPerDefense", 4);
}

inline uint32 SodPaladinMalleableProtectionDefenseSkillPerLevel()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.MalleableProtection.DefenseSkillPerLevel", 5);
}

inline uint32 SodPaladinMalleableProtectionAttackPowerDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodPaladin.MalleableProtection.AttackPowerDurationSeconds", 15);
}

#endif // MODULE_SOD_PALADIN_H
