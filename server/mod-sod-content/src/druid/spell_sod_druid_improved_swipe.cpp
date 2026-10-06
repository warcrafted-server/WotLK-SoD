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
#include <list>

class spell_sod_druid_swipe_bear_targets : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_swipe_bear_targets);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void LimitTargets(std::list<WorldObject*>& targets)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_SWIPE))
            return;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form != FORM_BEAR && form != FORM_DIREBEAR)
            return;

        if (Unit* primaryTarget = GetExplTargetUnit())
        {
            auto itr = std::find(targets.begin(), targets.end(), primaryTarget);
            if (itr != targets.end())
                targets.splice(targets.begin(), targets, itr);
        }

        uint32 maxTargets = std::max<uint32>(1, SodDruidImprovedSwipeMaxBearTargets());
        while (targets.size() > maxTargets)
            targets.pop_back();
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(
            spell_sod_druid_swipe_bear_targets::LimitTargets,
            EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_sod_druid_swipe_cat_redirect : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_swipe_cat_redirect);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void RedirectToSodSwipe(SpellEffIndex effIndex)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_SWIPE)
            || player->GetShapeshiftForm() != FORM_CAT)
            return;

        PreventHitDefaultEffect(effIndex);
        if (_redirected)
            return;

        Unit* target = GetExplTargetUnit();
        if (!target)
            target = GetHitUnit();
        if (!target)
            return;

        _redirected = true;
        player->CastSpell(target, SPELL_SOD_DRUID_SWIPE_CAT, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_druid_swipe_cat_redirect::RedirectToSodSwipe,
            EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
    }

private:
    bool _redirected = false;
};

void AddSC_sod_druid_improved_swipe()
{
    RegisterSpellScript(spell_sod_druid_swipe_bear_targets);
    RegisterSpellScript(spell_sod_druid_swipe_cat_redirect);
}
