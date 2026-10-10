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

// El +6 % por efecto de Sombras (hasta el 18 %) y el canal de Drenar alma 3 veces más rápido
// los llevan el manejador nativo del talento Succión de alma (aura 112) y el SpellModOp 19 del
// propio hechizo de la runa. Aquí sólo queda lo que no cubre WotLK: que Drenar alma pueda
// activar el talento Ocaso, reproduciendo su probabilidad por tick.
class spell_sod_warlock_soul_siphon : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_soul_siphon);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void HandleTick(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        Player* player = caster->ToPlayer();
        if (!player->HasAura(SPELL_SOD_WARLOCK_SOUL_SIPHON))
            return;

        Aura* nightfall = player->GetAuraOfRankedSpell(SPELL_WARLOCK_NIGHTFALL);
        if (!nightfall)
            return;

        if (roll_chance_i(static_cast<int32>(nightfall->GetSpellInfo()->ProcChance)))
            player->CastSpell(player, SPELL_WARLOCK_SHADOW_TRANCE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_warlock_soul_siphon::HandleTick,
            EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

void AddSC_sod_warlock_soul_siphon()
{
    RegisterSpellScript(spell_sod_warlock_soul_siphon);
}
