/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Item.h"
#include "ItemTemplate.h"
#include "ObjectGuid.h"
#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool SodDualWielding(Player* player)
{
    return player && player->GetWeaponForAttack(OFF_ATTACK, true);
}
}

// Furia enfocada: pasiva con aura 226 (sondeo cada 2 s) y aura dummy cuyo proc engancha los
// ataques automáticos. Con dos armas concede la velocidad de movimiento (430472) y, cada vez que
// un ataque automático golpea al mismo objetivo que el anterior, aplica o renueva la celeridad
// (461470, hasta 5 acumulaciones de 10 s); si el objetivo cambia, la retira.
class spell_sod_warrior_single_minded_fury : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_single_minded_fury);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (SodDualWielding(player))
        {
            player->CastSpell(player, SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_SPEED, true);
        }
        else
        {
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_SPEED);
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE);
            _lastTarget.Clear();
        }
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        Unit* target = eventInfo.GetProcTarget();
        if (!SodDualWielding(player))
        {
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE);
            _lastTarget.Clear();
            return;
        }

        if (target && target->GetGUID() == _lastTarget)
            player->CastSpell(player, SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE, true);
        else
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE);

        _lastTarget = target ? target->GetGUID() : ObjectGuid::Empty;
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_SPEED);
        player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_warrior_single_minded_fury::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_warrior_single_minded_fury::HandleProc,
            EFFECT_1, SPELL_AURA_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_warrior_single_minded_fury::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }

private:
    ObjectGuid _lastTarget;
};

void AddSC_sod_warrior_single_minded_fury()
{
    RegisterSpellScript(spell_sod_warrior_single_minded_fury);
}
