/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_hunter.h"

#include "Player.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
constexpr uint32 SPELL_HUNTER_RAPTOR_STRIKE_R1 = 2973;
constexpr int32 MELEE_SPECIALIST_RESET_CHANCE = 40;

void ResetMeleeSpecialistCooldowns(Player* player)
{
    for (uint32 spellId = SPELL_SOD_HUNTER_MONGOOSE_BITE_R1; spellId;
        spellId = sSpellMgr->GetNextSpellInChain(spellId))
        if (player->HasSpell(spellId))
            player->RemoveSpellCooldown(spellId, true);

    for (uint32 spellId = SPELL_HUNTER_RAPTOR_STRIKE_R1; spellId;
        spellId = sSpellMgr->GetNextSpellInChain(spellId))
        if (player->HasSpell(spellId))
            player->RemoveSpellCooldown(spellId, true);
}

void TryResetMeleeSpecialistCooldowns(Player* player)
{
    if (player && SodHunterEnabled()
        && player->HasAura(SPELL_SOD_HUNTER_MELEE_SPECIALIST)
        && roll_chance_i(MELEE_SPECIALIST_RESET_CHANCE))
        ResetMeleeSpecialistCooldowns(player);
}
}

// La runa convierte en instantáneo Golpe de raptor mediante una SpellMod oculta.
class spell_sod_hunter_melee_specialist : public AuraScript
{
    PrepareAuraScript(spell_sod_hunter_melee_specialist);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void ApplyInstantRaptorStrike(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player)
            player->CastSpell(player, SPELL_SOD_HUNTER_MELEE_SPECIALIST_INSTANT, true);
    }

    void RemoveInstantRaptorStrike(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (target)
            target->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_MELEE_SPECIALIST_INSTANT);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_hunter_melee_specialist::ApplyInstantRaptorStrike,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_hunter_melee_specialist::RemoveInstantRaptorStrike,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_hunter_melee_specialist_raptor_strike : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_melee_specialist_raptor_strike);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandleAfterHit()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (GetHitUnit())
            TryResetMeleeSpecialistCooldowns(player);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(
            spell_sod_hunter_melee_specialist_raptor_strike::HandleAfterHit);
    }
};

class spell_sod_hunter_melee_specialist_mongoose_bite : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_melee_specialist_mongoose_bite);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandleAfterHit()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (GetHitUnit())
            TryResetMeleeSpecialistCooldowns(player);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(
            spell_sod_hunter_melee_specialist_mongoose_bite::HandleAfterHit);
    }
};

void AddSC_sod_hunter_melee_specialist()
{
    RegisterSpellScript(spell_sod_hunter_melee_specialist);
    RegisterSpellScript(spell_sod_hunter_melee_specialist_raptor_strike);
    RegisterSpellScript(spell_sod_hunter_melee_specialist_mongoose_bite);
}
