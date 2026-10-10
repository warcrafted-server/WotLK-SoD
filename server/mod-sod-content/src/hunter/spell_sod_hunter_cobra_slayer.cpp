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
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

#include <algorithm>
#include <map>

namespace
{
constexpr int32 COBRA_SLAYER_CHANCE_STEP = 10;
constexpr int32 COBRA_SLAYER_DAMAGE_PCT = 45;

// Probabilidad acumulada por cazador; se reinicia al activarse.
std::map<ObjectGuid, int32> CobraSlayerChance;

void ResetMongooseBiteCooldown(Player* player)
{
    for (uint32 id = SPELL_SOD_HUNTER_MONGOOSE_BITE_R1; id; id = sSpellMgr->GetNextSpellInChain(id))
        if (player->HasSpell(id))
            player->RemoveSpellCooldown(id, true);
}
}

// Destripacobras: pasiva con proc sobre ataques cuerpo a cuerpo. La probabilidad parte del
// 10 % y sube 10 puntos por cada ataque que no la reinicia; un esquive del enemigo la lleva al
// 100 %. Al activarse se reinicia el enfriamiento de Mordedura de mangosta (que en 3.3.5a ya
// es usable sin requisito, así que aquí sólo se adelanta su reutilización de 5 s).
class spell_sod_hunter_cobra_slayer : public AuraScript
{
    PrepareAuraScript(spell_sod_hunter_cobra_slayer);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetActor() && eventInfo.GetActor()->HasAura(SPELL_SOD_HUNTER_COBRA_SLAYER);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32& chance = CobraSlayerChance[player->GetGUID()];
        bool const dodged = (eventInfo.GetHitMask() & PROC_EX_DODGE) != 0;
        if (!dodged)
        {
            chance = std::min(chance + COBRA_SLAYER_CHANCE_STEP, 100);
            if (!roll_chance_i(chance))
                return;
        }

        chance = 0;
        ResetMongooseBiteCooldown(player);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_hunter_cobra_slayer::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_hunter_cobra_slayer::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Parte de daño de Destripacobras: Mordedura de mangosta (id negativo -1495 enlaza todos los
// rangos) inflige un 45 % adicional del poder de ataque si el cazador tiene la runa.
class spell_sod_hunter_cobra_slayer_mongoose_bite : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_cobra_slayer_mongoose_bite);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void AddAttackPowerDamage(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!caster || !caster->HasAura(SPELL_SOD_HUNTER_COBRA_SLAYER))
            return;

        int32 const bonus = int32(CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK),
            COBRA_SLAYER_DAMAGE_PCT));
        if (bonus > 0)
            SetHitDamage(GetHitDamage() + bonus);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_hunter_cobra_slayer_mongoose_bite::AddAttackPowerDamage,
            EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_sod_hunter_cobra_slayer()
{
    RegisterSpellScript(spell_sod_hunter_cobra_slayer);
    RegisterSpellScript(spell_sod_hunter_cobra_slayer_mongoose_bite);
}
