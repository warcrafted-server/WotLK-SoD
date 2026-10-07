/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "SpellInfo.h"
#include "SpellMgr.h"

class spell_sod_druid_gale_winds : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_gale_winds);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        if (!spellMod)
        {
            SpellInfo const* hurricane = sSpellMgr->GetSpellInfo(SPELL_DRUID_HURRICANE);
            if (!hurricane || !hurricane->SpellFamilyFlags)
                return;

            spellMod = new SpellModifier(GetAura());
            spellMod->op = SpellModOp(aurEff->GetMiscValue());
            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = GetId();
            spellMod->mask = hurricane->SpellFamilyFlags;
        }

        switch (aurEff->GetEffIndex())
        {
            case EFFECT_0:
                spellMod->value = int32(SodDruidGaleWindsDamagePct());
                break;
            case EFFECT_1:
                spellMod->value = -int32(SodDruidGaleWindsManaCostReductionPct());
                break;
            case EFFECT_2:
                spellMod->value = -100;
                break;
            default:
                break;
        }
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_druid_gale_winds::HandleSpellMod, EFFECT_ALL, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_druid_gale_winds()
{
    RegisterSpellScript(spell_sod_druid_gale_winds);
}
