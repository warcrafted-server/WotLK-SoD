/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "Group.h"
#include "SpellInfo.h"
#include "SpellMgr.h"

class spell_sod_druid_tree_of_life : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_tree_of_life);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void ApplyBenefits(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            target->CastSpell(target, SPELL_SOD_DRUID_TREE_OF_LIFE_BENEFITS, TRIGGERED_FULL_MASK);
    }

    void RemoveBenefits(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            target->RemoveAurasDueToSpell(SPELL_SOD_DRUID_TREE_OF_LIFE_BENEFITS);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_druid_tree_of_life::ApplyBenefits,
            EFFECT_0, SPELL_AURA_MOD_STAT, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_druid_tree_of_life::RemoveBenefits,
            EFFECT_0, SPELL_AURA_MOD_STAT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_druid_tree_of_life_benefits : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_tree_of_life_benefits);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        if (!spellMod)
        {
            spellMod = new SpellModifier(GetAura());
            spellMod->op = SpellModOp(aurEff->GetMiscValue());
            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = GetId();

            if (aurEff->GetEffIndex() == EFFECT_0)
            {
                uint32 const healingOverTimeSpellIds[] = { 774, 8936, 33763, 740, 53251 };
                flag96 hotMask;
                for (uint32 spellId : healingOverTimeSpellIds)
                    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
                        hotMask |= spellInfo->SpellFamilyFlags;
                spellMod->mask = hotMask;
            }
            else if (SpellInfo const* wildGrowth = sSpellMgr->GetSpellInfo(53251))
                spellMod->mask = wildGrowth->SpellFamilyFlags;
        }

        if (aurEff->GetEffIndex() == EFFECT_0)
            spellMod->value = -int32(SodDruidTreeOfLifeHotManaCostReductionPct());
        else if (aurEff->GetEffIndex() == EFFECT_1)
            spellMod->value = int32(SodDruidTreeOfLifeWildGrowthHealingPct());
    }

    void CalculatePeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = int32(SodDruidTreeOfLifePartyRefreshMs());
    }

    void RefreshPartyHealingAura(AuraEffect const* /*aurEff*/)
    {
        Player* caster = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!caster)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidTreeOfLifePartyBuffDurationMs()));
        caster->CastCustomSpell(SPELL_SOD_DRUID_TREE_OF_LIFE_PARTY_BUFF,
            values, caster, TRIGGERED_FULL_MASK);

        Group* group = caster->GetGroup();
        if (!group)
            return;

        float const radius = SodDruidTreeOfLifePartyRadiusYards();
        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
        {
            Player* member = itr->GetSource();
            if (!member || member == caster || !member->IsInWorld()
                || !member->IsWithinDistInMap(caster, radius))
                continue;

            caster->CastCustomSpell(SPELL_SOD_DRUID_TREE_OF_LIFE_PARTY_BUFF,
                values, member, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_druid_tree_of_life_benefits::HandleSpellMod,
            EFFECT_ALL, SPELL_AURA_DUMMY);
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_druid_tree_of_life_benefits::CalculatePeriodic,
            EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_druid_tree_of_life_benefits::RefreshPartyHealingAura,
            EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_druid_tree_of_life()
{
    RegisterSpellScript(spell_sod_druid_tree_of_life);
    RegisterSpellScript(spell_sod_druid_tree_of_life_benefits);
}
