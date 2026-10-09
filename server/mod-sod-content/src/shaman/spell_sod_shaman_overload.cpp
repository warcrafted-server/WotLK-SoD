/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "SpellInfo.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
uint32 GetOverloadSpell(SpellInfo const* spellInfo)
{
    if (!spellInfo || spellInfo->SpellFamilyName != 11)
        return 0;

    if (spellInfo->Id >= SPELL_SOD_SHAMAN_OVERLOAD_LIGHTNING_BOLT
        && spellInfo->Id <= SPELL_SOD_SHAMAN_OVERLOAD_LAVA_BURST)
        return 0;

    uint32 const familyMaskA = spellInfo->SpellFamilyFlags[0];
    uint32 const familyMaskB = spellInfo->SpellFamilyFlags[1];
    if (familyMaskA & 0x2)
        return SPELL_SOD_SHAMAN_OVERLOAD_CHAIN_LIGHTNING;
    if (familyMaskA & 0x1)
        return SPELL_SOD_SHAMAN_OVERLOAD_LIGHTNING_BOLT;
    if (familyMaskA & 0x100)
        return SPELL_SOD_SHAMAN_OVERLOAD_CHAIN_HEAL;
    if (familyMaskA & 0x40)
        return SPELL_SOD_SHAMAN_OVERLOAD_HEALING_WAVE;
    if (familyMaskB & 0x1000)
        return SPELL_SOD_SHAMAN_OVERLOAD_LAVA_BURST;
    return 0;
}
}

class spell_sod_shaman_overload : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_overload);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return GetTarget() && GetTarget()->IsPlayer()
            && eventInfo.GetActionTarget() && GetOverloadSpell(eventInfo.GetSpellInfo());
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetTarget();
        Unit* target = eventInfo.GetActionTarget();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        uint32 overloadSpell = GetOverloadSpell(spellInfo);
        if (!caster || !target || !overloadSpell)
            return;

        uint32 amount = 0;
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
            amount = damageInfo->GetDamage();
        else if (HealInfo* healInfo = eventInfo.GetHealInfo())
            amount = healInfo->GetHeal();

        if (amount < 2)
            return;

        caster->CastCustomSpell(overloadSpell, SPELLVALUE_BASE_POINT0,
            int32(amount / 2), target, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_overload::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_overload::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_shaman_overload()
{
    RegisterSpellScript(spell_sod_shaman_overload);
}
