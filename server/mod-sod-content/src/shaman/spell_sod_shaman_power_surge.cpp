/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

#include "Random.h"

class spell_sod_shaman_power_surge : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_power_surge);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return GetTarget() && GetTarget()->IsPlayer() && eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!player || !spellInfo)
            return;

        bool const flameShockTick = spellInfo->SpellFamilyName == 11
            && (spellInfo->SpellFamilyFlags[0] & 0x10000000)
            && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage();
        bool const riptideHeal = (spellInfo->Id == SPELL_SOD_SHAMAN_RIPTIDE
            || (spellInfo->SpellFamilyName == 11 && (spellInfo->SpellFamilyFlags[2] & 0x10)))
            && eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetEffectiveHeal();

        if (flameShockTick && roll_chance_i(5))
        {
            player->RemoveSpellCooldown(SPELL_SOD_SHAMAN_LAVA_BURST, true);
            SpellInfo const* chainLightning = sSpellMgr->GetSpellInfo(SPELL_SHAMAN_CHAIN_LIGHTNING);
            if (chainLightning)
                for (SpellInfo const* rank = chainLightning->GetFirstRankSpell(); rank; rank = rank->GetNextRankSpell())
                    player->RemoveSpellCooldown(rank->Id, true);

            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_LIGHTNING);
            player->CastSpell(player, SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_LIGHTNING, TRIGGERED_FULL_MASK);
        }

        if (riptideHeal && roll_chance_i(5))
        {
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_CHAIN_HEAL);
            player->CastSpell(player, SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_CHAIN_HEAL, TRIGGERED_FULL_MASK);
        }

        if (player->HasAura(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_LIGHTNING))
        {
            bool const lavaBurst = spellInfo->Id == SPELL_SOD_SHAMAN_LAVA_BURST;
            bool const chainLightningCast = spellInfo->SpellFamilyName == 11
                && (spellInfo->SpellFamilyFlags[0] & 0x2);
            if (lavaBurst || chainLightningCast)
                player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_LIGHTNING);
        }

        if (player->HasAura(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_CHAIN_HEAL)
            && spellInfo->SpellFamilyName == 11 && (spellInfo->SpellFamilyFlags[0] & 0x100))
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_POWER_SURGE_INSTANT_CHAIN_HEAL);

        (void)aurEff;
    }

    void RestoreIntellectMana(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32 const mana = int32(player->GetStat(STAT_INTELLECT) * 0.02f);
        if (mana > 0)
            player->ModifyPower(POWER_MANA, mana);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_power_surge::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_power_surge::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_shaman_power_surge::RestoreIntellectMana,
            EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_shaman_power_surge()
{
    RegisterSpellScript(spell_sod_shaman_power_surge);
}
