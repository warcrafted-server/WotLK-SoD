/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"
#include "SpellMgr.h"

#include <algorithm>

namespace
{
uint8 GetRedoubtRank(Player const* player)
{
    uint8 rank = 0;
    for (uint8 index = 0; index < std::size(SPELL_PALADIN_REDOUBT_RANKS); ++index)
        if (player->HasSpell(SPELL_PALADIN_REDOUBT_RANKS[index]))
            rank = index + 1;
    return rank;
}

uint8 GetReckoningRank(Player const* player)
{
    uint8 rank = 0;
    for (uint8 index = 0; index < std::size(SPELL_PALADIN_RECKONING_RANKS); ++index)
        if (player->HasSpell(SPELL_PALADIN_RECKONING_RANKS[index]))
            rank = index + 1;
    return rank;
}
}

class spell_sod_paladin_aegis : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_aegis);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleRedoubtChanceApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_0))
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinAegisRedoubtChancePct(), 100)));
    }

    void HandleBlockValueApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_1))
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinAegisBlockValuePct(), 500)));
    }

    void HandleReckoningChanceApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_2))
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinAegisReckoningChancePerPointPct(), 100)));
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return false;

        uint32 eventFlags = eventInfo.GetTypeMask();
        if (eventInfo.GetActor() == player)
        {
            constexpr uint32 meleeFlags = PROC_FLAG_DONE_MELEE_AUTO_ATTACK
                | PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS;
            return GetRedoubtRank(player) && (eventFlags & meleeFlags)
                && (eventInfo.GetHitMask() & PROC_HIT_CRITICAL);
        }

        if (eventInfo.GetActionTarget() != player)
            return false;

        constexpr uint32 incomingFlags = PROC_FLAG_TAKEN_MELEE_AUTO_ATTACK
            | PROC_FLAG_TAKEN_SPELL_MELEE_DMG_CLASS
            | PROC_FLAG_TAKEN_RANGED_AUTO_ATTACK
            | PROC_FLAG_TAKEN_SPELL_RANGED_DMG_CLASS;
        if (!(eventFlags & incomingFlags))
            return false;

        return GetRedoubtRank(player) || GetReckoningRank(player);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        uint8 redoubtRank = GetRedoubtRank(player);
        if (eventInfo.GetActor() == player)
        {
            if (redoubtRank)
                player->CastSpell(player, SPELL_PALADIN_REDOUBT_PROC_RANKS[redoubtRank - 1], true);
            return;
        }

        if (redoubtRank && roll_chance_i(static_cast<int32>(std::min<uint32>(
                SodPaladinAegisRedoubtChancePct(), 100))))
            player->CastSpell(player, SPELL_PALADIN_REDOUBT_PROC_RANKS[redoubtRank - 1], true);

        uint8 reckoningRank = GetReckoningRank(player);
        uint32 reckoningChance = std::min<uint32>(
            SodPaladinAegisReckoningChancePerPointPct() * reckoningRank, 100);
        if (reckoningRank && roll_chance_i(static_cast<int32>(reckoningChance)))
            player->CastSpell(player, SPELL_PALADIN_RECKONING_PROC, true);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_aegis::HandleRedoubtChanceApply,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_aegis::HandleBlockValueApply,
            EFFECT_1, SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_aegis::HandleReckoningChanceApply,
            EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_aegis::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_aegis::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_aegis()
{
    RegisterSpellScript(spell_sod_paladin_aegis);
}
