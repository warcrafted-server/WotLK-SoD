/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Unit.h"
#include "UnitScript.h"

namespace
{
constexpr uint32 MASK_ROGUE_RUPTURE = 0x00100000;

bool HasOwnPhysicalBleed(Unit* target, Player* rogue)
{
    if (!target || !rogue)
        return false;

    for (AuraEffect const* effect : target->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE))
    {
        SpellInfo const* spellInfo = effect->GetSpellInfo();
        if (effect->GetCasterGUID() == rogue->GetGUID() && spellInfo
            && spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE
            && (spellInfo->SchoolMask & SPELL_SCHOOL_MASK_NORMAL))
            return true;
    }

    return false;
}

int32 GetCarnageDamagePercent(Player* rogue)
{
    SpellInfo const* valueSpell = sSpellMgr->GetSpellInfo(SPELL_SOD_ROGUE_CARNAGE_VALUE);
    return valueSpell ? valueSpell->Effects[EFFECT_0].CalcValue(rogue) : 0;
}

void ApplyCarnageDamageBonus(Unit* target, Player* rogue, uint32& damage)
{
    if (!SodRogueEnabled() || !target || !rogue || !rogue->IsClass(CLASS_ROGUE)
        || !rogue->HasAura(SPELL_SOD_ROGUE_CARNAGE))
        return;

    int32 const percent = GetCarnageDamagePercent(rogue);
    if (percent <= 0 || !HasOwnPhysicalBleed(target, rogue))
        return;

    damage += uint32(uint64(damage) * uint32(percent) / 100);
}
}

class unit_sod_rogue_carnage : public UnitScript
{
public:
    unit_sod_rogue_carnage() : UnitScript("unit_sod_rogue_carnage", true,
        { UNITHOOK_MODIFY_PERIODIC_DAMAGE_AURAS_TICK, UNITHOOK_MODIFY_SPELL_DAMAGE_TAKEN }) { }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage,
        SpellInfo const* spellInfo) override
    {
        Player* rogue = attacker ? attacker->ToPlayer() : nullptr;
        if (!rogue || !spellInfo || !rogue->IsClass(CLASS_ROGUE)
            || !rogue->HasAura(SPELL_SOD_ROGUE_CARNAGE))
            return;

        ApplyCarnageDamageBonus(target, rogue, damage);

        bool const isRupture = spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE
            && (spellInfo->SpellFamilyFlags[0] & MASK_ROGUE_RUPTURE)
            && spellInfo->Id != SPELL_SOD_ROGUE_CRIMSON_TEMPEST;
        if (!isRupture || !HasOwnPhysicalBleed(target, rogue))
            return;

        AuraEffect const* healEffect = rogue->GetAuraEffect(SPELL_SOD_ROGUE_CARNAGE, EFFECT_1);
        if (!healEffect || healEffect->GetAmount() <= 0 || !damage)
            return;

        uint32 const heal = uint32(uint64(damage) * uint32(healEffect->GetAmount()) / 100);
        Unit::DealHeal(rogue, rogue, heal);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage,
        SpellInfo const* /*spellInfo*/) override
    {
        if (damage <= 0)
            return;

        uint32 adjustedDamage = uint32(damage);
        ApplyCarnageDamageBonus(target, attacker ? attacker->ToPlayer() : nullptr, adjustedDamage);
        damage = int32(adjustedDamage);
    }
};

void AddSC_sod_rogue_carnage()
{
    new unit_sod_rogue_carnage();
}
