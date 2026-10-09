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

class spell_sod_paladin_guarded_by_the_light : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_guarded_by_the_light);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player || eventInfo.GetActor() != player)
            return false;

        constexpr uint32 meleeFlags = PROC_FLAG_DONE_MELEE_AUTO_ATTACK
            | PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS;
        return (eventInfo.GetTypeMask() & meleeFlags) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        if (!player)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodPaladinGuardedByTheLightDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_PALADIN_GUARDED_BY_THE_LIGHT_BUFF,
            values, player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_guarded_by_the_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_guarded_by_the_light::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_paladin_guarded_by_the_light_buff : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_guarded_by_the_light_buff);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void CalculatePeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = int32(std::max<uint32>(SodPaladinGuardedByTheLightTickSeconds(), 1)
            * IN_MILLISECONDS);
    }

    void HandleManaTick(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        uint32 maxMana = uint32(std::max<int32>(player->GetMaxPower(POWER_MANA), 0));
        uint32 manaPct = std::min<uint32>(SodPaladinGuardedByTheLightManaPctPerTick(), 100);
        int32 mana = int32(CalculatePct(maxMana, manaPct));
        if (mana > 0)
            player->ModifyPower(POWER_MANA, mana);
    }

    void HandleHealingReductionApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (AuraEffect* effect = GetEffect(EFFECT_1))
            effect->ChangeAmount(-int32(std::min<uint32>(
                SodPaladinGuardedByTheLightHealingReductionPct(), 100)));
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_paladin_guarded_by_the_light_buff::CalculatePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_paladin_guarded_by_the_light_buff::HandleManaTick,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_guarded_by_the_light_buff::HandleHealingReductionApply,
            EFFECT_1, SPELL_AURA_MOD_HEALING_DONE_PERCENT, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_paladin_guarded_by_the_light()
{
    RegisterSpellScript(spell_sod_paladin_guarded_by_the_light);
    RegisterSpellScript(spell_sod_paladin_guarded_by_the_light_buff);
}
