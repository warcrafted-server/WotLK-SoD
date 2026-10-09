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

class spell_sod_paladin_infusion_of_light : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_infusion_of_light);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleDamageHealingApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_0))
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinInfusionOfLightDamageHealingPct(), 100)));
    }

    void HandleTooltipApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_2))
            effect->ChangeAmount(static_cast<int32>(SodPaladinInfusionOfLightCriticalCooldownSeconds()));
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo || spellInfo->SpellFamilyName != SPELLFAMILY_PALADIN
            || !spellInfo->SpellFamilyFlags.HasFlag(0x00200000, 0x00010000, 0))
            return false;

        return (eventInfo.GetHitMask() & PROC_HIT_CRITICAL) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget()->ToPlayer();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!player || !spellInfo)
            return;

        // El crítico llega por el hechizo disparado (daño 25912 / curación 25914), sin coste ni
        // enfriamiento propios: el coste y el enfriamiento son del rango de Choque Sagrado lanzado.
        uint32 reductionMs = SodPaladinInfusionOfLightCriticalCooldownSeconds() * IN_MILLISECONDS;
        for (auto it = std::rbegin(SPELL_PALADIN_HOLY_SHOCK_RANKS); it != std::rend(SPELL_PALADIN_HOLY_SHOCK_RANKS); ++it)
        {
            if (!player->HasSpell(*it))
                continue;

            if (SpellInfo const* rankInfo = sSpellMgr->GetSpellInfo(*it))
            {
                int32 manaCost = rankInfo->CalcPowerCost(player, rankInfo->GetSchoolMask());
                if (manaCost > 0)
                    player->ModifyPower(POWER_MANA, manaCost);
            }

            uint32 remainingMs = player->GetSpellCooldownDelay(*it);
            if (remainingMs && reductionMs)
                player->ModifySpellCooldown(*it, -static_cast<int32>(std::min(remainingMs, reductionMs)));
            break;
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_infusion_of_light::HandleDamageHealingApply,
            EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_infusion_of_light::HandleTooltipApply,
            EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_infusion_of_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_infusion_of_light::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_infusion_of_light()
{
    RegisterSpellScript(spell_sod_paladin_infusion_of_light);
}
