/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_improved_hammer_of_wrath : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_improved_hammer_of_wrath);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        Unit* target = eventInfo.GetActionTarget();
        uint32 threshold = std::min<uint32>(SodPaladinImprovedHammerOfWrathResetHealthPct(), 100);
        return threshold && damageInfo && damageInfo->GetDamage() && target &&
            target->HealthBelowPct(static_cast<int32>(threshold));
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        for (uint32 spellId : SPELL_PALADIN_HAMMER_OF_WRATH_RANKS)
        {
            uint32 remainingMs = player->GetSpellCooldownDelay(spellId);
            if (remainingMs)
                player->ModifySpellCooldown(spellId, -static_cast<int32>(remainingMs));
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_improved_hammer_of_wrath::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_improved_hammer_of_wrath::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_improved_hammer_of_wrath()
{
    RegisterSpellScript(spell_sod_paladin_improved_hammer_of_wrath);
}
