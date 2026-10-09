/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "DBCStores.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool HasFlametongueOnMainHand(Player* player)
{
    Item* weapon = player ? player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND) : nullptr;
    if (!weapon)
        return false;

    SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(
        weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT));
    if (!enchant)
        return false;

    for (uint32 spellId : enchant->spellid)
    {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (spellInfo && spellInfo->SpellFamilyName == 11
            && (spellInfo->SpellFamilyFlags[1] & 0x800))
            return true;
    }

    return false;
}

void UpdateBurnSpellDamage(Player* player)
{
    if (!player)
        return;

    if (!HasFlametongueOnMainHand(player))
    {
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_BURN_SPELL_DAMAGE);
        return;
    }

    int32 const spellDamage = int32(player->GetStat(STAT_INTELLECT) * 1.5f);
    AuraEffect const* currentEffect = player->GetAuraEffect(
        SPELL_SOD_SHAMAN_BURN_SPELL_DAMAGE, EFFECT_0);
    if (currentEffect && currentEffect->GetAmount() == spellDamage)
        return;

    player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_BURN_SPELL_DAMAGE);
    CustomSpellValues values;
    values.AddSpellMod(SPELLVALUE_BASE_POINT0, spellDamage);
    player->CastCustomSpell(SPELL_SOD_SHAMAN_BURN_SPELL_DAMAGE,
        values, player, TRIGGERED_FULL_MASK);
}
}

class spell_sod_shaman_burn : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_burn);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void UpdateSpellDamage(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        UpdateBurnSpellDamage(player);
    }

    void RemoveSpellDamage(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            target->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_BURN_SPELL_DAMAGE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_shaman_burn::UpdateSpellDamage,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sod_shaman_burn::RemoveSpellDamage,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_shaman_burn_flame_shock : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_burn_flame_shock);

    bool Load() override
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        return SodShamanEnabled() && caster && caster->HasAura(SPELL_SOD_SHAMAN_BURN);
    }

    void IncreasePeriodicDamage(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount *= 2;
    }

    void IncreaseDuration(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Aura* aura = GetAura();
        if (!aura || !GetSpellInfo() || GetSpellInfo()->GetDuration() < 0)
            return;

        int32 const duration = GetSpellInfo()->GetDuration() + 6000;
        aura->SetMaxDuration(duration);
        aura->SetDuration(duration);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_shaman_burn_flame_shock::IncreasePeriodicDamage,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_burn_flame_shock::IncreaseDuration,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_shaman_burn_flame_shock_direct : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_burn_flame_shock_direct);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void IncreaseDirectDamage(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (caster && caster->HasAura(SPELL_SOD_SHAMAN_BURN))
            SetHitDamage(GetHitDamage() * 2);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_shaman_burn_flame_shock_direct::IncreaseDirectDamage,
            EFFECT_ALL, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_sod_shaman_burn()
{
    RegisterSpellScript(spell_sod_shaman_burn);
    RegisterSpellScript(spell_sod_shaman_burn_flame_shock);
    RegisterSpellScript(spell_sod_shaman_burn_flame_shock_direct);
}
