/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "Unit.h"

#include "Random.h"

namespace
{
void EnsureStaticShockCharges(Unit* target)
{
    if (!SodShamanEnabled() || !target || !target->HasAura(SPELL_SOD_SHAMAN_STATIC_SHOCK))
        return;

    AuraEffect* lightningShield = target->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL,
        SPELLFAMILY_SHAMAN, 0x400, 0, 0, target->GetGUID());
    if (lightningShield && lightningShield->GetBase()->GetCharges() < 9)
        lightningShield->GetBase()->SetCharges(9);
}
}

class spell_sod_shaman_static_shock : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_static_shock);

    bool chargeRaisedForOverchargedProc = false;

    void HandleRuneApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        EnsureStaticShockCharges(GetTarget());
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!SodShamanEnabled() || !player || eventInfo.GetActor() != player || !eventInfo.GetActionTarget()
            || !eventInfo.GetDamageInfo() || !eventInfo.GetDamageInfo()->GetDamage()
            || !player->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL,
                SPELLFAMILY_SHAMAN, 0x400, 0, 0, player->GetGUID()))
            return false;

        bool const dualWielding = player->GetWeaponForAttack(OFF_ATTACK) != nullptr;
        return roll_chance_i(dualWielding ? 6 : 12);
    }

    void PreserveOverchargedCharge(ProcEventInfo& /*eventInfo*/)
    {
        chargeRaisedForOverchargedProc = false;
        Unit* player = GetTarget();
        if (!player || !player->HasAura(SPELL_SOD_SHAMAN_OVERCHARGED))
            return;

        AuraEffect* lightningShield = player->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL,
            SPELLFAMILY_SHAMAN, 0x400, 0, 0, player->GetGUID());
        if (lightningShield && lightningShield->GetBase()->GetCharges() < 2)
        {
            lightningShield->GetBase()->SetCharges(2);
            chargeRaisedForOverchargedProc = true;
        }
    }

    void RestoreOverchargedCharge(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        Unit* player = GetTarget();
        if (!player || !player->HasAura(SPELL_SOD_SHAMAN_OVERCHARGED))
            return;

        AuraEffect* lightningShield = player->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL,
            SPELLFAMILY_SHAMAN, 0x400, 0, 0, player->GetGUID());
        if (chargeRaisedForOverchargedProc)
        {
            chargeRaisedForOverchargedProc = false;
            return;
        }

        if (lightningShield && lightningShield->GetBase()->GetCharges() < 9)
            lightningShield->GetBase()->SetCharges(lightningShield->GetBase()->GetCharges() + 1);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_static_shock::HandleRuneApply,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_static_shock::CheckProc);
        DoPrepareProc += AuraProcFn(spell_sod_shaman_static_shock::PreserveOverchargedCharge);
        AfterEffectProc += AuraEffectProcFn(
            spell_sod_shaman_static_shock::RestoreOverchargedCharge, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_shaman_static_shock_lightning_shield : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_static_shock_lightning_shield);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleLightningShieldApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        EnsureStaticShockCharges(GetTarget());
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_static_shock_lightning_shield::HandleLightningShieldApply,
            EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_static_shock()
{
    RegisterSpellScript(spell_sod_shaman_static_shock);
    RegisterSpellScript(spell_sod_shaman_static_shock_lightning_shield);
}
