/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Player.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
constexpr uint32 MASK_EVISCERATE = 0x00020000;
constexpr int32 BLADE_DANCE_MAX_DURATION = 30000;

Aura* GetSliceAndDice(Player* rogue)
{
    AuraEffect const* sliceEffect = rogue ? rogue->GetAuraEffect(SPELL_AURA_MOD_MELEE_HASTE,
        SPELLFAMILY_ROGUE, 0x00040000, 0, 0, rogue->GetGUID()) : nullptr;
    return sliceEffect ? sliceEffect->GetBase() : nullptr;
}

void RefreshShortestFinisherAura(Player* rogue)
{
    if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE)
        || !rogue->HasAura(SPELL_SOD_ROGUE_CUT_TO_THE_CHASE))
        return;

    Aura* sliceAndDice = GetSliceAndDice(rogue);
    Aura* bladeDance = rogue->GetAura(SPELL_SOD_ROGUE_BLADE_DANCE, rogue->GetGUID());

    if (!sliceAndDice && !bladeDance)
        return;

    Aura* selected = nullptr;
    int32 maxDuration = 0;
    if (sliceAndDice && bladeDance)
    {
        if (sliceAndDice->GetDuration() <= bladeDance->GetDuration())
        {
            selected = sliceAndDice;
            maxDuration = sliceAndDice->GetSpellInfo()->GetMaxDuration();
        }
        else
        {
            selected = bladeDance;
            maxDuration = BLADE_DANCE_MAX_DURATION;
        }
    }
    else if (sliceAndDice)
    {
        selected = sliceAndDice;
        maxDuration = sliceAndDice->GetSpellInfo()->GetMaxDuration();
    }
    else
    {
        selected = bladeDance;
        maxDuration = BLADE_DANCE_MAX_DURATION;
    }

    if (selected && maxDuration > 0)
    {
        selected->SetMaxDuration(maxDuration);
        selected->SetDuration(maxDuration);
    }
}
}

class spell_sod_rogue_cut_to_the_chase : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_cut_to_the_chase);

    int32 _sliceDuration = -1;
    int32 _sliceMaxDuration = -1;
    int32 _bladeDanceDuration = -1;
    bool _capturedDurations = false;

    bool Load() override
    {
        Player* rogue = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        return rogue && rogue->IsClass(CLASS_ROGUE);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo || spellInfo->SpellFamilyName != SPELLFAMILY_ROGUE
            || !(spellInfo->SpellFamilyFlags[0] & MASK_EVISCERATE))
            return false;

        Player* rogue = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        Aura* sliceAndDice = GetSliceAndDice(rogue);
        Aura* bladeDance = rogue
            ? rogue->GetAura(SPELL_SOD_ROGUE_BLADE_DANCE, rogue->GetGUID()) : nullptr;
        _sliceDuration = sliceAndDice ? sliceAndDice->GetDuration() : -1;
        _sliceMaxDuration = sliceAndDice ? sliceAndDice->GetMaxDuration() : -1;
        _bladeDanceDuration = bladeDance ? bladeDance->GetDuration() : -1;
        _capturedDurations = true;
        return true;
    }

    void HandleAfterProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        if (!_capturedDurations)
            return;

        _capturedDurations = false;
        Player* rogue = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!rogue)
            return;

        Aura* sliceAndDice = GetSliceAndDice(rogue);
        Aura* bladeDance = rogue->GetAura(SPELL_SOD_ROGUE_BLADE_DANCE, rogue->GetGUID());

        // El script WotLK actualiza Hacer picadillo; se revierte ese cambio cuando Danza de hojas
        // era el aura más corta o cuando el interruptor de runas está desactivado.
        if (_sliceDuration >= 0 && sliceAndDice
            && (!SodRogueEnabled() || (_bladeDanceDuration >= 0
                && _bladeDanceDuration < _sliceDuration)))
        {
            sliceAndDice->SetMaxDuration(_sliceMaxDuration);
            sliceAndDice->SetDuration(_sliceDuration);
        }

        if (!SodRogueEnabled())
            return;

        if (_sliceDuration >= 0 && _bladeDanceDuration >= 0)
        {
            if (_sliceDuration <= _bladeDanceDuration && sliceAndDice)
            {
                int32 const maxDuration = sliceAndDice->GetSpellInfo()->GetMaxDuration();
                if (maxDuration > 0)
                {
                    sliceAndDice->SetMaxDuration(maxDuration);
                    sliceAndDice->SetDuration(maxDuration);
                }
            }
            else if (bladeDance)
            {
                bladeDance->SetMaxDuration(BLADE_DANCE_MAX_DURATION);
                bladeDance->SetDuration(BLADE_DANCE_MAX_DURATION);
            }
        }
        else if (_sliceDuration >= 0 && sliceAndDice)
        {
            int32 const maxDuration = sliceAndDice->GetSpellInfo()->GetMaxDuration();
            if (maxDuration > 0)
            {
                sliceAndDice->SetMaxDuration(maxDuration);
                sliceAndDice->SetDuration(maxDuration);
            }
        }
        else if (_bladeDanceDuration >= 0 && bladeDance)
        {
            bladeDance->SetMaxDuration(BLADE_DANCE_MAX_DURATION);
            bladeDance->SetDuration(BLADE_DANCE_MAX_DURATION);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_rogue_cut_to_the_chase::CheckProc);
        AfterEffectProc += AuraEffectProcFn(spell_sod_rogue_cut_to_the_chase::HandleAfterProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_rogue_cut_to_the_chase_envenom : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_cut_to_the_chase_envenom);

    void HandleHit()
    {
        RefreshShortestFinisherAura(GetCaster() ? GetCaster()->ToPlayer() : nullptr);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_rogue_cut_to_the_chase_envenom::HandleHit);
    }
};

void AddSC_sod_rogue_cut_to_the_chase()
{
    RegisterSpellScript(spell_sod_rogue_cut_to_the_chase);
    RegisterSpellScript(spell_sod_rogue_cut_to_the_chase_envenom);
}
