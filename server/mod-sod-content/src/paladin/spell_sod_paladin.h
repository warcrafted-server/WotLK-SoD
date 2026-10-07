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
};

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

#endif // MODULE_SOD_PALADIN_H
