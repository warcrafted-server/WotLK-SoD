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
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "Unit.h"

// Invocación engancha las auras de daño periódico de Corrupción, Inmolar, Maldición de
// agonía, Aflicción inestable, Llama de las Sombras y Succionar vida (ids negativos en
// sod_warlock_runes.sql). Al aplicarse o refrescarse cualquiera de esos DoT sobre el
// objetivo, el brujo con la runa inflige al instante un pulso del propio daño periódico.
// La rama de SoD «refrescar con menos de 6 s restantes inflige el daño periódico restante»
// no se puede resolver desde aquí (el core reinicia la duración antes del aviso); se aplica
// siempre un pulso. Ver TODO.md.
class spell_sod_warlock_invocation : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_invocation);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void HandlePeriodicApplied(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target || !caster->IsPlayer())
            return;

        if (!caster->HasAura(SPELL_SOD_WARLOCK_INVOCATION))
            return;

        int32 const damage = aurEff ? aurEff->GetAmount() : 0;
        if (damage <= 0)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        caster->CastCustomSpell(SPELL_SOD_WARLOCK_INVOCATION_DAMAGE, values, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sod_warlock_invocation::HandlePeriodicApplied,
            EFFECT_ALL, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectApply += AuraEffectApplyFn(spell_sod_warlock_invocation::HandlePeriodicApplied,
            EFFECT_ALL, SPELL_AURA_PERIODIC_LEECH, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

void AddSC_sod_warlock_invocation()
{
    RegisterSpellScript(spell_sod_warlock_invocation);
}
