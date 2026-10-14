/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "SpellAuras.h"
#include "SpellInfo.h"
#include "SpellAuraEffects.h"
#include "Unit.h"
#include "UnitScript.h"

namespace
{
constexpr uint32 SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE = 31665;
constexpr uint32 SPELL_ROGUE_MASTER_OF_SUBTLETY_TRACKER = 31666;
constexpr uint32 MASK_ROGUE_STEALTH = 0x00400000;

bool IsRogueStealthAura(Aura const* aura)
{
    SpellInfo const* spellInfo = aura ? aura->GetSpellInfo() : nullptr;
    return spellInfo && spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE
        && (spellInfo->SpellFamilyFlags[0] & MASK_ROGUE_STEALTH);
}

void UpdateMasterOfSubtlety(Unit* unit, bool stealthed)
{
    if (!SodRogueEnabled() || !unit || !unit->IsPlayer()
        || !unit->IsClass(CLASS_ROGUE))
        return;

    AuraEffect const* runeEffect = unit->GetAuraEffect(
        SPELL_SOD_ROGUE_MASTER_OF_SUBTLETY, EFFECT_0);
    if (!runeEffect)
        return;

    if (stealthed)
    {
        unit->RemoveAurasDueToSpell(SPELL_ROGUE_MASTER_OF_SUBTLETY_TRACKER);
        int32 amount = runeEffect->GetAmount();
        unit->CastCustomSpell(unit, SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE,
            &amount, nullptr, nullptr, true);
    }
    else
        unit->CastSpell(unit, SPELL_ROGUE_MASTER_OF_SUBTLETY_TRACKER, true);
}
}

class unit_sod_rogue_master_of_subtlety : public UnitScript
{
public:
    unit_sod_rogue_master_of_subtlety() : UnitScript(
        "unit_sod_rogue_master_of_subtlety", true,
        { UNITHOOK_ON_AURA_APPLY, UNITHOOK_ON_AURA_REMOVE }) { }

    void OnAuraApply(Unit* unit, Aura* aura) override
    {
        if (IsRogueStealthAura(aura))
            UpdateMasterOfSubtlety(unit, true);
    }

    void OnAuraRemove(Unit* unit, AuraApplication* aurApp, AuraRemoveMode /*mode*/) override
    {
        Aura* aura = aurApp ? aurApp->GetBase() : nullptr;
        if (IsRogueStealthAura(aura))
            UpdateMasterOfSubtlety(unit, false);
    }
};

void AddSC_sod_rogue_master_of_subtlety()
{
    new unit_sod_rogue_master_of_subtlety();
}
