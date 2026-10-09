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

#include <array>

namespace
{
constexpr uint32 SPELL_SHAMAN_DUAL_WIELD = 674;
constexpr std::array<uint32, 3> SPELL_SHAMAN_DUAL_WIELD_TALENTS = {30816, 30818, 30819};
}

class spell_sod_shaman_dual_wield_specialization : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_dual_wield_specialization);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    // En WotLK Golpe de tormenta (17364) ya golpea con ambas armas: la runa solo concede la doble
    // empuñadura y los bonos de golpe y daño de mano izquierda.
    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player && !player->HasSpell(SPELL_SHAMAN_DUAL_WIELD))
            player->learnSpell(SPELL_SHAMAN_DUAL_WIELD);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        for (uint32 talent : SPELL_SHAMAN_DUAL_WIELD_TALENTS)
            if (player->HasSpell(talent))
                return;

        player->removeSpell(SPELL_SHAMAN_DUAL_WIELD, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_dual_wield_specialization::HandleApply,
            EFFECT_0, SPELL_AURA_MOD_HIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_shaman_dual_wield_specialization::HandleRemove,
            EFFECT_0, SPELL_AURA_MOD_HIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_dual_wield_specialization()
{
    RegisterSpellScript(spell_sod_shaman_dual_wield_specialization);
}
