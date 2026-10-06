/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 */

#include "spell_sod_druid.h"

#include <algorithm>

class spell_sod_druid_king_of_the_jungle : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_king_of_the_jungle);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void PreventFlatDamageAura(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        if (caster && caster->HasAura(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE))
            PreventHitDefaultEffect(effIndex);
    }

    void HandleAfterHit()
    {
        Player* player = GetHitUnit() ? GetHitUnit()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE))
            return;

        int32 duration = int32(SodDruidKingOfTheJungleBuffDurationSeconds() * IN_MILLISECONDS);
        int32 talentEnergy = 0;
        if (AuraEffect const* talent = player->GetAuraEffectOfRankedSpell(
                SPELL_DRUID_KING_OF_THE_JUNGLE_TALENT, EFFECT_1))
            talentEnergy = std::max(0, talent->GetAmount());
        // The core's Tiger's Fury script already grants the WotLK talent's energy.
        int32 supplementalEnergy = std::max(0,
            int32(SodDruidKingOfTheJungleEnergy()) - talentEnergy);

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0,
            int32(SodDruidKingOfTheJungleDamagePct()));
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, supplementalEnergy);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION, duration);
        player->CastCustomSpell(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_BUFF,
            values, player, TRIGGERED_FULL_MASK);

        uint32 spellId = GetSpellInfo()->Id;
        player->RemoveSpellCooldown(spellId, true);
        uint32 cooldownSeconds = SodDruidKingOfTheJungleCooldownSeconds();
        if (cooldownSeconds)
        {
            // Re-send the normal cooldown event, then adjust it to the configured
            // duration. This keeps the client timer in sync with the server.
            SpellInfo const* spellInfo = GetSpellInfo();
            uint32 cooldownMs = cooldownSeconds * IN_MILLISECONDS;
            player->SendCooldownEvent(spellInfo);
            int32 cooldownDeltaMs = int32(cooldownMs) - int32(spellInfo->RecoveryTime);
            if (cooldownDeltaMs)
                player->ModifySpellCooldown(spellId, cooldownDeltaMs);
        }

        CustomSpellValues watchValues;
        watchValues.AddSpellMod(SPELLVALUE_AURA_DURATION, duration);
        player->CastCustomSpell(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_FORM_WATCH,
            watchValues, player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_druid_king_of_the_jungle::PreventFlatDamageAura,
            EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        AfterHit += SpellHitFn(
            spell_sod_druid_king_of_the_jungle::HandleAfterHit);
    }
};

class spell_sod_druid_king_of_the_jungle_form_watch : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_king_of_the_jungle_form_watch);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void CalculatePeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = int32(std::max<uint32>(100, SodDruidKingOfTheJungleFormCheckMs()));
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        ShapeshiftForm form = target->GetShapeshiftForm();
        if (form != FORM_BEAR && form != FORM_DIREBEAR)
            return;

        target->RemoveAura(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_BUFF);
        target->RemoveAura(SPELL_SOD_DRUID_KING_OF_THE_JUNGLE_FORM_WATCH);
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_druid_king_of_the_jungle_form_watch::CalculatePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_druid_king_of_the_jungle_form_watch::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_druid_king_of_the_jungle()
{
    RegisterSpellScript(spell_sod_druid_king_of_the_jungle);
    RegisterSpellScript(spell_sod_druid_king_of_the_jungle_form_watch);
}
