/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifndef MODULE_SOD_DRUID_H
#define MODULE_SOD_DRUID_H

#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodDruidSpells
{
    SPELL_SOD_DRUID_MANGLE = 407995,
    SPELL_SOD_DRUID_GORE = 417145,
    SPELL_SOD_DRUID_DEFENDERS_RESOLVE = 460171,
    SPELL_SOD_DRUID_WILD_STRIKES = 407977,
    SPELL_SOD_DRUID_WILD_STRIKES_BUFF = 407975,
    SPELL_SOD_DRUID_KING_OF_THE_JUNGLE = 417046,
    SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_BUFF = 417045,
    SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_FORM_WATCH = 900015,
    SPELL_SOD_DRUID_SKULL_BASH = 410176,
    SPELL_SOD_DRUID_SKULL_BASH_INTERRUPT = 414621,
    SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION = 431389,
    SPELL_SOD_DRUID_FRENZIED_REGENERATION_HELPER = 428708,
    SPELL_SOD_DRUID_IMPROVED_SWIPE = 439510,
    SPELL_SOD_DRUID_SWIPE_CAT = 411128,
    SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION_FORM_PERMIT = 900016,
    SPELL_SOD_DRUID_IMPROVED_BARKSKIN = 431388,
    SPELL_SOD_DRUID_GALE_WINDS = 417135,
    SPELL_SOD_DRUID_FURY_OF_STORMRAGE = 414799,
    SPELL_SOD_DRUID_FURY_OF_STORMRAGE_BUFF = 900017,
    SPELL_SOD_DRUID_DREAMSTATE = 408258,
    SPELL_SOD_DRUID_DREAMSTATE_REGEN = 900018,
    SPELL_SOD_DRUID_DREAMSTATE_MAGIC = 900019,
    SPELL_SOD_DRUID_TREE_OF_LIFE = 439733,
    SPELL_SOD_DRUID_TREE_OF_LIFE_BENEFITS = 900020,
    SPELL_SOD_DRUID_TREE_OF_LIFE_PARTY_BUFF = 900021,
    SPELL_SOD_DRUID_EFFLORESCENCE_AURA = 900022,
    SPELL_SOD_DRUID_ECLIPSE_BUFF = 900023,
    SPELL_SOD_DRUID_STARFALL_DAMAGE = 900024,
};

constexpr uint32 SPELL_DRUID_BARKSKIN = 22812;
constexpr uint32 SPELL_DRUID_FRENZIED_REGENERATION = 22842;
constexpr uint32 SPELL_DRUID_FRENZIED_REGENERATION_HEAL = 22845;
constexpr uint32 SPELL_DRUID_SWIPE_BEAR_FIRST_RANK = 779;
constexpr uint32 SPELL_DRUID_SWIPE_CAT = 62078;
constexpr uint32 SPELL_DRUID_MANGLE_BEAR = 48564;
constexpr uint32 SPELL_DRUID_MANGLE_CAT = 48566;
constexpr uint32 SPELL_DRUID_TIGERS_FURY_RANKS[] = { 5217, 6793, 9845, 9846, 50212, 50213 };
constexpr uint32 SPELL_DRUID_KING_OF_THE_JUNGLE_TALENT = 48492;
constexpr uint32 SPELL_DRUID_TIGER_FURY_ENERGIZE = 51178;
constexpr uint32 SPELL_DRUID_WINDFURY_TOTEM_EFFECT = 8515;
constexpr uint32 SPELL_DRUID_WINDFURY_ATTACK_MAINHAND = 25504;
constexpr uint32 SPELL_DRUID_WINDFURY_ATTACK_OFFHAND = 33750;
constexpr uint32 SPELL_DRUID_HURRICANE = 16914;
constexpr uint32 SPELL_DRUID_WRATH = 5176;
constexpr uint32 SPELL_DRUID_HEALING_TOUCH_FAMILY_MASK0 = 0x00000020;
constexpr uint32 SPELL_DRUID_STARSURGE = 417157;
constexpr uint32 SPELL_DRUID_STARFIRE = 48465;
constexpr uint32 SPELL_DRUID_REGROWTH = 48443;
constexpr uint32 SPELL_DRUID_SHRED = 48572;
constexpr uint32 SPELL_DRUID_SWIFTMEND = 18562;

inline uint32 SodDruidGaleWindsDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.GaleWinds.DamagePct", 20);
}

inline uint32 SodDruidGaleWindsManaCostReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.GaleWinds.ManaCostReductionPct", 30);
}

inline uint32 SodDruidFuryOfStormrageWrathCostReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.FuryOfStormrage.WrathCostReductionPct", 100);
}

inline uint32 SodDruidFuryOfStormrageProcChance()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.FuryOfStormrage.ProcChance", 12);
}

inline uint32 SodDruidFuryOfStormrageBuffDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.FuryOfStormrage.BuffDurationSeconds", 15);
}

inline uint32 SodDruidDreamstateManaRegenPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Dreamstate.ManaRegenPct", 50);
}

inline uint32 SodDruidDreamstateManaRegenDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Dreamstate.ManaRegenDurationSeconds", 8);
}

inline uint32 SodDruidDreamstateDamageTakenPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Dreamstate.DamageTakenPct", 20);
}

inline uint32 SodDruidDreamstateDamageTakenDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Dreamstate.DamageTakenDurationSeconds", 12);
}

inline float SodDruidTreeOfLifePartyRadiusYards()
{
    return sConfigMgr->GetOption<float>("SodDruid.TreeOfLife.PartyRadiusYards", 45.0f);
}

inline uint32 SodDruidTreeOfLifePartyBuffDurationMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.TreeOfLife.PartyBuffDurationMs", 2000);
}

inline uint32 SodDruidTreeOfLifePartyRefreshMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.TreeOfLife.PartyRefreshMs", 1000);
}

inline uint32 SodDruidTreeOfLifeHotManaCostReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.TreeOfLife.HotManaCostReductionPct", 20);
}

inline uint32 SodDruidTreeOfLifeWildGrowthHealingPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.TreeOfLife.WildGrowthHealingPct", 60);
}

inline uint32 SodDruidStarsurgeCooldownSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Starsurge.CooldownSeconds", 6);
}

inline uint32 SodDruidEfflorescenceDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Efflorescence.DurationSeconds", 15);
}

inline float SodDruidEfflorescenceRadiusYards()
{
    return sConfigMgr->GetOption<float>("SodDruid.Efflorescence.RadiusYards", 15.0f);
}

inline uint32 SodDruidElunesFiresMoonfireSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ElunesFires.MoonfireSeconds", 6);
}

inline uint32 SodDruidElunesFiresSunfireSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ElunesFires.SunfireSeconds", 3);
}

inline uint32 SodDruidElunesFiresRejuvenationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ElunesFires.RejuvenationSeconds", 6);
}

inline uint32 SodDruidElunesFiresRipSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ElunesFires.RipSeconds", 2);
}

inline uint32 SodDruidEclipseDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Eclipse.DurationSeconds", 15);
}

inline uint32 SodDruidEclipseMaxStacks()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Eclipse.MaxStacks", 4);
}

inline uint32 SodDruidEclipseCritChancePct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Eclipse.CritChancePct", 30);
}

inline uint32 SodDruidEclipseCastTimeReductionMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Eclipse.CastTimeReductionMs", 1000);
}

inline uint32 SodDruidEclipsePushbackReductionPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Eclipse.PushbackReductionPct", 70);
}

inline uint32 SodDruidStarfallDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Starfall.DurationSeconds", 10);
}

inline uint32 SodDruidStarfallCooldownSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Starfall.CooldownSeconds", 90);
}

inline uint32 SodDruidStarfallManaCostPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Starfall.ManaCostPct", 39);
}

inline bool SodDruidEnabled()
{
    return sConfigMgr->GetOption<bool>("SodDruid.Enable", true);
}

inline uint32 SodDruidMangleBearRageCost()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.BearRageCost", 15);
}

inline uint32 SodDruidMangleDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.DamagePct", 160);
}

inline uint32 SodDruidMangleBleedDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.BleedDamagePct", 30);
}

inline uint32 SodDruidMangleCatEnergyCost()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.CatEnergyCost", 45);
}

inline uint32 SodDruidMangleDefenseSkillPerLevel()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.DefenseSkillPerLevel", 5);
}

inline uint32 SodDruidMangleAttackPowerPerDefense()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.AttackPowerPerDefense", 4);
}

inline uint32 SodDruidMangleBuffDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Mangle.BuffDurationSeconds", 60);
}

inline uint32 SodDruidGoreProcChance()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Gore.ProcChance", 15);
}

inline uint32 SodDruidGoreRageAmount()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.Gore.RageAmount", 10);
}

inline float SodDruidWildStrikesRadiusYards()
{
    return sConfigMgr->GetOption<float>("SodDruid.WildStrikes.RadiusYards", 100.0f);
}

inline uint32 SodDruidWildStrikesRefreshMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.WildStrikes.RefreshMs", 5000);
}

inline uint32 SodDruidWildStrikesBuffDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.WildStrikes.BuffDurationSeconds", 6);
}

inline uint32 SodDruidWildStrikesProcChance()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.WildStrikes.ProcChance", 20);
}

inline uint32 SodDruidWildStrikesProcCooldownMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.WildStrikes.ProcCooldownMs", 1500);
}

inline uint32 SodDruidWildStrikesAttackPowerPct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.WildStrikes.AttackPowerPct", 20);
}

inline uint32 SodDruidKingOfTheJungleDamagePct()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.KingOfTheJungle.DamagePct", 15);
}

inline uint32 SodDruidKingOfTheJungleEnergy()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.KingOfTheJungle.Energy", 60);
}

inline uint32 SodDruidKingOfTheJungleBuffDurationSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.KingOfTheJungle.BuffDurationSeconds", 6);
}

inline uint32 SodDruidKingOfTheJungleCooldownSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.KingOfTheJungle.CooldownSeconds", 30);
}

inline uint32 SodDruidKingOfTheJungleFormCheckMs()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.KingOfTheJungle.FormCheckMs", 250);
}

inline uint32 SodDruidSkullBashEnergyCost()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.SkullBash.EnergyCost", 25);
}

inline uint32 SodDruidSkullBashRageCost()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.SkullBash.RageCost", 10);
}

inline uint32 SodDruidSkullBashSchoolLockoutSeconds()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.SkullBash.SchoolLockoutSeconds", 2);
}

inline uint32 SodDruidImprovedFrenziedRegenerationEnergyPerSecond()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ImprovedFrenziedRegeneration.EnergyPerSecond", 10);
}

inline uint32 SodDruidImprovedFrenziedRegenerationRagePerSecond()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ImprovedFrenziedRegeneration.RagePerSecond", 10);
}

inline uint32 SodDruidImprovedFrenziedRegenerationBaseManaPctPerSecond()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ImprovedFrenziedRegeneration.BaseManaPctPerSecond", 20);
}

inline uint32 SodDruidImprovedFrenziedRegenerationHealthPctPerSecond()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ImprovedFrenziedRegeneration.HealthPctPerSecond", 10);
}

inline uint32 SodDruidImprovedSwipeMaxBearTargets()
{
    return sConfigMgr->GetOption<uint32>("SodDruid.ImprovedSwipe.MaxBearTargets", 8);
}

#endif // MODULE_SOD_DRUID_H
