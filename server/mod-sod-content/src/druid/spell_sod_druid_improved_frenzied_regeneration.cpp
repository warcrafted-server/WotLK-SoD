/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "Player.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_druid_improved_frenzied_regeneration_rune : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_improved_frenzied_regeneration_rune);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            target->CastSpell(target, SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION_FORM_PERMIT, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            target->RemoveAurasDueToSpell(SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION_FORM_PERMIT);
            target->RemoveAurasDueToSpell(SPELL_SOD_DRUID_FRENZIED_REGENERATION_HELPER);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_druid_improved_frenzied_regeneration_rune::HandleApply,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_druid_improved_frenzied_regeneration_rune::HandleRemove,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_druid_improved_frenzied_regeneration_cast : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_improved_frenzied_regeneration_cast);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    SpellCastResult CheckCast()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION))
            return SPELL_CAST_OK;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form == FORM_MOONKIN || form == FORM_NONE)
            return SPELL_FAILED_ONLY_SHAPESHIFT;

        return SPELL_CAST_OK;
    }

    void HandleAfterHit()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION))
            return;

        // Replace the WotLK aura so its core Rage tick cannot apply the old 3% conversion.
        player->RemoveAurasDueToSpell(SPELL_DRUID_FRENZIED_REGENERATION);
        player->CastSpell(player, SPELL_SOD_DRUID_FRENZIED_REGENERATION_HELPER, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(
            spell_sod_druid_improved_frenzied_regeneration_cast::CheckCast);
        AfterHit += SpellHitFn(
            spell_sod_druid_improved_frenzied_regeneration_cast::HandleAfterHit);
    }
};

class spell_sod_druid_improved_frenzied_regeneration_aura : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_improved_frenzied_regeneration_aura);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_FRENZIED_REGENERATION))
            return;

        Powers power = player->getPowerType();
        uint32 maxResource = 0;
        if (power == POWER_RAGE)
            maxResource = SodDruidImprovedFrenziedRegenerationRagePerSecond() * 10;
        else if (power == POWER_ENERGY)
            maxResource = SodDruidImprovedFrenziedRegenerationEnergyPerSecond();
        else if (power == POWER_MANA)
        {
            uint32 baseMana = player->GetCreateMana();
            if (!baseMana)
                return;
            maxResource = CalculatePct(baseMana,
                SodDruidImprovedFrenziedRegenerationBaseManaPctPerSecond());
        }
        else
            return;

        if (!maxResource)
            return;

        int32 consumed = -player->ModifyPower(power,
            -int32(std::min<uint32>(maxResource, player->GetPower(power))));
        if (consumed <= 0)
            return;

        float healthPct = float(SodDruidImprovedFrenziedRegenerationHealthPctPerSecond())
            * float(consumed) / float(maxResource);
        int32 heal = int32(CalculatePct(player->GetMaxHealth(), healthPct));
        if (heal > 0)
            player->CastCustomSpell(SPELL_DRUID_FRENZIED_REGENERATION_HEAL,
                SPELLVALUE_BASE_POINT0, heal, player, true, nullptr, aurEff);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_druid_improved_frenzied_regeneration_aura::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_druid_improved_frenzied_regeneration()
{
    RegisterSpellScript(spell_sod_druid_improved_frenzied_regeneration_rune);
    RegisterSpellScript(spell_sod_druid_improved_frenzied_regeneration_cast);
    RegisterSpellScript(spell_sod_druid_improved_frenzied_regeneration_aura);
}
