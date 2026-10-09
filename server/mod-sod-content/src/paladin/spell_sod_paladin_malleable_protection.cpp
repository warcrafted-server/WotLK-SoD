/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "Player.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellInfo.h"

#include <algorithm>
#include <limits>

class spell_sod_paladin_malleable_divine_protection : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_malleable_divine_protection);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    // Enganchado a Protección divina (498) por spell_script_names: solo actúa si el lanzador
    // tiene grabada la runa.
    void SetDuration(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Aura* aura = GetAura();
        Unit* caster = GetCaster();
        if (!aura || !caster || !caster->HasAura(SPELL_SOD_PALADIN_MALLEABLE_PROTECTION))
            return;

        int32 baseDuration = aura->GetMaxDuration();
        uint32 increasePct = std::min<uint32>(
            SodPaladinMalleableProtectionDurationIncreasePct(), 1000);
        int32 duration = baseDuration + int32(CalculatePct(
            uint32(baseDuration), increasePct));
        aura->SetMaxDuration(duration);
        aura->SetDuration(duration);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_malleable_divine_protection::SetDuration,
            EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
    }
};

class player_sod_paladin_malleable_protection : public PlayerScript
{
public:
    player_sod_paladin_malleable_protection()
        : PlayerScript("player_sod_paladin_malleable_protection") { }

    void OnPlayerSpellCast(Player* player, Spell* spell, bool /*skipCheck*/) override
    {
        if (!player || !spell || !SodPaladinEnabled()
            || !player->HasAura(SPELL_SOD_PALADIN_MALLEABLE_PROTECTION))
            return;

        SpellInfo const* spellInfo = spell->GetSpellInfo();
        if (!spellInfo || std::find(std::begin(SPELL_PALADIN_HOLY_SHIELD_RANKS),
                std::end(SPELL_PALADIN_HOLY_SHIELD_RANKS), spellInfo->Id)
                == std::end(SPELL_PALADIN_HOLY_SHIELD_RANKS))
            return;

        uint32 defenseSkill = player->GetSkillValue(SKILL_DEFENSE);
        uint32 defensePerLevel = SodPaladinMalleableProtectionDefenseSkillPerLevel();
        uint32 baseDefense = uint32(player->GetLevel()) * defensePerLevel;
        uint32 excessDefense = defenseSkill > baseDefense ? defenseSkill - baseDefense : 0;
        uint64 attackPower = uint64(excessDefense)
            * SodPaladinMalleableProtectionAttackPowerPerDefense();
        int32 attackPowerAmount = int32(std::min<uint64>(attackPower,
            uint64(std::numeric_limits<int32>::max())));

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, attackPowerAmount);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, attackPowerAmount);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION, int32(
            SodPaladinMalleableProtectionAttackPowerDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_PALADIN_MALLEABLE_PROTECTION_AP,
            values, player, TRIGGERED_FULL_MASK);
    }
};

void AddSC_sod_paladin_malleable_protection()
{
    RegisterSpellScript(spell_sod_paladin_malleable_divine_protection);
    new player_sod_paladin_malleable_protection();
}
