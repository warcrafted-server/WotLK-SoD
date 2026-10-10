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
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
constexpr uint8 SNIPER_TRAINING_MAX_STACKS = 5;
}

// Instrucción de francotirador: pasiva con sondeo de 1 s. Mientras el cazador no se mueve
// acumula la mejora 415401 (+2 % de crítico con disparos por acumulación, hasta 5) y la pierde
// de una en una al moverse. Con la acumulación máxima concede Disparo de puntería instantáneo.
class spell_sod_hunter_sniper_training : public AuraScript
{
    PrepareAuraScript(spell_sod_hunter_sniper_training);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void UpdateInstantAimedShot(Player* player, uint8 stacks)
    {
        if (stacks >= SNIPER_TRAINING_MAX_STACKS)
        {
            if (!player->HasAura(SPELL_SOD_HUNTER_SNIPER_TRAINING_INSTANT))
                player->CastSpell(player, SPELL_SOD_HUNTER_SNIPER_TRAINING_INSTANT, true);
        }
        else
            player->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_SNIPER_TRAINING_INSTANT);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        Aura* buff = player->GetAura(SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF);
        if (player->isMoving())
        {
            if (buff)
            {
                if (buff->GetStackAmount() > 1)
                    buff->ModStackAmount(-1);
                else
                    player->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF);
            }
        }
        else if (!buff)
            player->CastSpell(player, SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF, true);
        else if (buff->GetStackAmount() < SNIPER_TRAINING_MAX_STACKS)
            buff->ModStackAmount(1);

        Aura* updated = player->GetAura(SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF);
        UpdateInstantAimedShot(player, updated ? updated->GetStackAmount() : 0);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        target->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF);
        target->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_SNIPER_TRAINING_INSTANT);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_hunter_sniper_training::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_sod_hunter_sniper_training::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_hunter_sniper_training()
{
    RegisterSpellScript(spell_sod_hunter_sniper_training);
}
