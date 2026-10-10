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
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Unit.h"

// SoD hace que Drenar vida sane un 50 % más por tick manteniendo el daño. El aumento de coste de
// maná lo lleva el SpellModOp 14 del propio hechizo de la runa; aquí se añade esa sanación extra
// al brujo en cada tick del canal (WotLK enlaza daño y sanación, por eso se separa).
class spell_sod_warlock_master_channeler : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_master_channeler);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void HandleTick(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer() || !aurEff)
            return;

        Player* player = caster->ToPlayer();
        if (!player->HasAura(SPELL_SOD_WARLOCK_MASTER_CHANNELER))
            return;

        int32 amount = aurEff->GetAmount() / 2;
        if (amount <= 0)
            return;

        HealInfo healInfo(player, player, static_cast<uint32>(amount), GetSpellInfo(), SPELL_SCHOOL_MASK_SHADOW);
        player->HealBySpell(healInfo);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_warlock_master_channeler::HandleTick,
            EFFECT_0, SPELL_AURA_PERIODIC_LEECH);
    }
};

void AddSC_sod_warlock_master_channeler()
{
    RegisterSpellScript(spell_sod_warlock_master_channeler);
}
