/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_hunter.h"

#include "AllSpellScript.h"
#include "Creature.h"
#include "CreatureData.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
constexpr uint32 HUNTER_SHOT_MASK_A = 0x21A00;
constexpr uint32 HUNTER_SHOT_MASK_B = 0x80820001;
constexpr uint32 HUNTER_SHOT_MASK_C = 0x8341;
constexpr uint32 SCATTER_SHOT_MASK_A = 0x40000;

bool IsHunterShot(SpellInfo const* spellInfo)
{
    if (!spellInfo || spellInfo->SpellFamilyName != SPELLFAMILY_HUNTER
        || (spellInfo->SpellFamilyFlags[0] & SCATTER_SHOT_MASK_A))
        return false;

    return (spellInfo->SpellFamilyFlags[0] & HUNTER_SHOT_MASK_A)
        || (spellInfo->SpellFamilyFlags[1] & HUNTER_SHOT_MASK_B)
        || (spellInfo->SpellFamilyFlags[2] & HUNTER_SHOT_MASK_C);
}

bool IsRapidFire(SpellInfo const* spellInfo)
{
    return spellInfo && spellInfo->SpellFamilyName == SPELLFAMILY_HUNTER
        && (spellInfo->SpellFamilyFlags[0] & 0x20);
}

bool HasRapidFireAura(Player* player)
{
    for (uint32 spellId = SPELL_SOD_HUNTER_RAPID_FIRE_R1; spellId;
        spellId = sSpellMgr->GetNextSpellInChain(spellId))
        if (player->HasAura(spellId))
            return true;

    return false;
}

void GrantRapidKillingBuff(Player* player, Creature* killed)
{
    if (!player || !killed || !SodHunterEnabled()
        || !player->HasAura(SPELL_SOD_HUNTER_RAPID_KILLING)
        || killed->HasFlagsExtra(CREATURE_FLAG_EXTRA_NO_XP))
        return;

    player->CastSpell(player, SPELL_SOD_HUNTER_RAPID_KILLING_BUFF, true);
}
}

class spell_sod_hunter_rapid_killing_rapid_fire_buff : public AuraScript
{
    PrepareAuraScript(spell_sod_hunter_rapid_killing_rapid_fire_buff);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void RemoveAfterRapidFire(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player && !HasRapidFireAura(player))
            player->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_RAPID_KILLING_RAPID_FIRE_HASTE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_hunter_rapid_killing_rapid_fire_buff::RemoveAfterRapidFire,
            EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class all_sod_hunter_rapid_killing : public AllSpellScript
{
public:
    all_sod_hunter_rapid_killing()
        : AllSpellScript("all_sod_hunter_rapid_killing", { ALLSPELLHOOK_ON_CAST }) { }

    void OnSpellCast(Spell* /*spell*/, Unit* caster, SpellInfo const* spellInfo,
        bool /*skipCheck*/) override
    {
        Player* player = caster ? caster->ToPlayer() : nullptr;
        if (!player || !SodHunterEnabled())
            return;

        if (player->HasAura(SPELL_SOD_HUNTER_RAPID_KILLING) && IsRapidFire(spellInfo))
            player->CastSpell(player, SPELL_SOD_HUNTER_RAPID_KILLING_RAPID_FIRE_HASTE, true);

        if (player->HasAura(SPELL_SOD_HUNTER_RAPID_KILLING_BUFF) && IsHunterShot(spellInfo))
            player->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_RAPID_KILLING_BUFF);
    }
};

class player_sod_hunter_rapid_killing : public PlayerScript
{
public:
    player_sod_hunter_rapid_killing()
        : PlayerScript("player_sod_hunter_rapid_killing",
            { PLAYERHOOK_ON_CREATURE_KILL, PLAYERHOOK_ON_CREATURE_KILLED_BY_PET,
              PLAYERHOOK_ON_PVP_KILL }) { }

    void OnPlayerCreatureKill(Player* killer, Creature* killed) override
    {
        GrantRapidKillingBuff(killer, killed);
    }

    void OnPlayerCreatureKilledByPet(Player* owner, Creature* killed) override
    {
        GrantRapidKillingBuff(owner, killed);
    }

    void OnPlayerPVPKill(Player* killer, Player* /*killed*/) override
    {
        if (killer && SodHunterEnabled() && killer->HasAura(SPELL_SOD_HUNTER_RAPID_KILLING))
            killer->CastSpell(killer, SPELL_SOD_HUNTER_RAPID_KILLING_BUFF, true);
    }
};

void AddSC_sod_hunter_rapid_killing()
{
    RegisterSpellScript(spell_sod_hunter_rapid_killing_rapid_fire_buff);
    new all_sod_hunter_rapid_killing();
    new player_sod_hunter_rapid_killing();
}
