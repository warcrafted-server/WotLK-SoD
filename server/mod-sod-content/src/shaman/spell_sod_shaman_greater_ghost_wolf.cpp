/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
void ApplyGreaterGhostWolfReduction(Player* player)
{
    if (player && SodShamanEnabled() && player->HasAura(SPELL_SOD_SHAMAN_GREATER_GHOST_WOLF))
        player->CastSpell(player, SPELL_SOD_SHAMAN_GREATER_GHOST_WOLF_REDUCTION, true);
}

void RemoveGreaterGhostWolfReduction(Player* player)
{
    if (player)
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_GREATER_GHOST_WOLF_REDUCTION);
}
}

class spell_sod_shaman_greater_ghost_wolf : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_greater_ghost_wolf);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleRuneApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player && player->HasAura(SPELL_SHAMAN_GHOST_WOLF))
            ApplyGreaterGhostWolfReduction(player);
    }

    void HandleRuneRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        RemoveGreaterGhostWolfReduction(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sod_shaman_greater_ghost_wolf::HandleRuneApply,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sod_shaman_greater_ghost_wolf::HandleRuneRemove,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_shaman_ghost_wolf_aura : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_ghost_wolf_aura);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleWolfApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        ApplyGreaterGhostWolfReduction(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void HandleWolfRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        RemoveGreaterGhostWolfReduction(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sod_shaman_ghost_wolf_aura::HandleWolfApply,
            EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sod_shaman_ghost_wolf_aura::HandleWolfRemove,
            EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_greater_ghost_wolf()
{
    RegisterSpellScript(spell_sod_shaman_greater_ghost_wolf);
    RegisterSpellScript(spell_sod_shaman_ghost_wolf_aura);
}
