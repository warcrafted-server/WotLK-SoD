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
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool HasRockbiterOnMainHand(Player* player)
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
            && (spellInfo->SpellFamilyFlags[0] & 0x00400000))
            return true;
    }

    return false;
}

bool HasWayOfEarthRequirements(Player* player)
{
    if (!player || !player->HasAura(SPELL_SOD_SHAMAN_WAY_OF_EARTH)
        || !HasRockbiterOnMainHand(player))
        return false;

    Item* shield = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
    return shield && shield->GetTemplate()->InventoryType == INVTYPE_SHIELD;
}

void UpdateWayOfEarthThreat(Player* player)
{
    if (!player)
        return;

    if (HasWayOfEarthRequirements(player))
    {
        player->CastSpell(player, SPELL_SOD_SHAMAN_WAY_OF_EARTH_BUFF, true);
        player->CastSpell(player, SPELL_SOD_SHAMAN_WAY_OF_EARTH_MELEE_CRIT, true);
        player->CastSpell(player, SPELL_SOD_SHAMAN_WAY_OF_EARTH_RANGE, true);
    }
    else
    {
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_BUFF);
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_MELEE_CRIT);
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_RANGE);
    }
}

void RemoveShamanShockCooldowns(Player* player)
{
    if (!player)
        return;

    constexpr uint32 shockSpellIds[] =
    {
        SPELL_SHAMAN_EARTH_SHOCK,
        SPELL_SHAMAN_FLAME_SHOCK,
        SPELL_SHAMAN_FROST_SHOCK,
    };

    for (uint32 spellId : shockSpellIds)
    {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo)
            continue;

        for (SpellInfo const* rank = spellInfo->GetFirstRankSpell(); rank; rank = rank->GetNextRankSpell())
            player->RemoveSpellCooldown(rank->Id, true);
    }
}

void SeparateShamanShockCooldown(Player* player, SpellInfo const* spellInfo)
{
    if (!player || !spellInfo || !HasWayOfEarthRequirements(player))
        return;

    RemoveShamanShockCooldowns(player);
    player->AddSpellCooldown(spellInfo->Id, 0, spellInfo->GetRecoveryTime(), true, true);
}
}

class spell_sod_shaman_way_of_earth : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_way_of_earth);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        UpdateWayOfEarthThreat(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        UpdateWayOfEarthThreat(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player)
        {
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_BUFF);
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_MELEE_CRIT);
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_WAY_OF_EARTH_RANGE);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sod_shaman_way_of_earth::HandleApply,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_shaman_way_of_earth::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sod_shaman_way_of_earth::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_shaman_way_of_earth_earth_shock : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_way_of_earth_earth_shock);

    SpellCastResult CheckCast()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetExplTargetUnit();
        if (HasWayOfEarthRequirements(player) && target && !player->IsWithinMeleeRange(target))
            return SPELL_FAILED_OUT_OF_RANGE;

        return SPELL_CAST_OK;
    }

    void HandleHit()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetHitUnit();
        if (!HasWayOfEarthRequirements(player) || !target || !target->IsAlive())
            return;

        player->CastSpell(target, SPELL_WARRIOR_TAUNT, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_shaman_way_of_earth_earth_shock::CheckCast);
        OnHit += SpellHitFn(spell_sod_shaman_way_of_earth_earth_shock::HandleHit);
    }
};

class spell_sod_shaman_way_of_earth_shock_cooldown : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_way_of_earth_shock_cooldown);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleAfterCast()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        SeparateShamanShockCooldown(player, GetSpellInfo());
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sod_shaman_way_of_earth_shock_cooldown::HandleAfterCast);
    }
};

void AddSC_sod_shaman_way_of_earth()
{
    RegisterSpellScript(spell_sod_shaman_way_of_earth);
    RegisterSpellScript(spell_sod_shaman_way_of_earth_earth_shock);
    RegisterSpellScript(spell_sod_shaman_way_of_earth_shock_cooldown);
}
