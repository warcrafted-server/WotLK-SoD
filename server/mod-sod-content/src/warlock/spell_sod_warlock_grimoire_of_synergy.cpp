/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warlock.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

// Grimorio de sinergia: el daño que inflige el brujo o su demonio tiene un 10 % de
// probabilidades de aumentar un 10 % el daño del otro durante 15 s. La runa lleva dos auras
// dummy con este mismo script: 1226981 la tiene el brujo y 900051 el familiar (recibida al
// invocarlo vía spell_pet_auras). El beneficio 426303 se aplica al "otro": si el proc viene
// del brujo, a su mascota; si viene de la mascota, a su dueño.
class spell_sod_warlock_grimoire_of_synergy : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_grimoire_of_synergy);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* target = GetTarget();
        if (!target)
            return;

        Unit* other = nullptr;
        if (target->IsPlayer())
        {
            Player* player = target->ToPlayer();
            if (player->HasAura(SPELL_SOD_WARLOCK_GRIMOIRE_OF_SYNERGY))
                other = player->GetGuardianPet();
        }
        else
        {
            other = target->GetOwner();
        }

        if (!other)
            return;

        other->RemoveAurasDueToSpell(SPELL_SOD_WARLOCK_GRIMOIRE_OF_SYNERGY_BUFF);
        other->CastSpell(other, SPELL_SOD_WARLOCK_GRIMOIRE_OF_SYNERGY_BUFF, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(
            spell_sod_warlock_grimoire_of_synergy::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_warlock_grimoire_of_synergy()
{
    RegisterSpellScript(spell_sod_warlock_grimoire_of_synergy);
}
