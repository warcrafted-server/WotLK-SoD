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
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_shaman_rolling_thunder : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_rolling_thunder);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return GetTarget() && GetTarget()->IsPlayer() && spellInfo
            && spellInfo->SpellFamilyName == 11
            && (spellInfo->SpellFamilyFlags[0] & 0x3);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* caster = GetTarget();
        if (!caster)
            return;

        AuraEffect* lightningShield = caster->GetAuraEffect(
            SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_SHAMAN, 0x400, 0, 0, caster->GetGUID());
        if (!lightningShield)
            return;

        Aura* aura = lightningShield->GetBase();
        if (aura->GetCharges() < 9)
            aura->SetCharges(aura->GetCharges() + 1);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_rolling_thunder::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_shaman_rolling_thunder::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_shaman_rolling_thunder_earth_shock : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_rolling_thunder_earth_shock);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void DischargeCharges()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target || !caster->HasAura(SPELL_SOD_SHAMAN_ROLLING_THUNDER))
            return;

        AuraEffect* lightningShield = caster->GetAuraEffect(
            SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_SHAMAN, 0x400, 0, 0, caster->GetGUID());
        if (!lightningShield)
            return;

        Aura* aura = lightningShield->GetBase();
        uint8 const charges = aura->GetCharges();
        if (charges <= 3)
            return;

        uint8 const released = charges - 3;
        aura->SetCharges(3);

        uint32 const damageSpell = sSpellMgr->GetSpellWithRank(
            SPELL_SHAMAN_LIGHTNING_SHIELD_DAMAGE_R1, lightningShield->GetSpellInfo()->GetRank());
        if (!damageSpell)
            return;

        for (uint8 i = 0; i < released; ++i)
            caster->CastSpell(target, damageSpell, TRIGGERED_FULL_MASK, nullptr, lightningShield);

        if (Player* player = caster->ToPlayer())
        {
            int32 const mana = int32(player->GetMaxPower(POWER_MANA) * 0.02f * released);
            if (mana > 0)
                player->ModifyPower(POWER_MANA, mana);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_shaman_rolling_thunder_earth_shock::DischargeCharges);
    }
};

void AddSC_sod_shaman_rolling_thunder()
{
    RegisterSpellScript(spell_sod_shaman_rolling_thunder);
    RegisterSpellScript(spell_sod_shaman_rolling_thunder_earth_shock);
}
