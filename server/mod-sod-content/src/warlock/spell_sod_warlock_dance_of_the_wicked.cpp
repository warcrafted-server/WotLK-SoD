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
#include "UpdateFields.h"

namespace
{
// Esquiva = porcentaje del efecto de la runa (70 % en el catálogo) sobre la probabilidad
// de crítico con hechizos de la escuela de las Sombras del brujo.
int32 CalculateDodgeFromSpellCrit(Player* player, AuraEffect const* runeEffect)
{
    if (!player || !runeEffect)
        return 0;

    float const spellCrit = player->GetFloatValue(
        PLAYER_SPELL_CRIT_PERCENTAGE1 + static_cast<uint8>(SPELL_SCHOOL_SHADOW));
    return int32(spellCrit * runeEffect->GetAmount() / 100.0f);
}
}

// Danza de los malditos: pasiva que proca al asestar un crítico (HitMask crítico en la
// fila spell_proc de 412798). Aplica el beneficio 900050 al brujo y a su mascota con la
// esquiva calculada. La recuperación de maná de SoD (el $412800s2%) no consta en el
// catálogo local y no se implementa; ver TODO.md.
class spell_sod_warlock_dance_of_the_wicked : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_dance_of_the_wicked);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void HandleCriticalStrike(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32 const dodge = CalculateDodgeFromSpellCrit(player, aurEff);
        if (dodge <= 0)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, dodge);
        player->CastCustomSpell(SPELL_SOD_WARLOCK_DANCE_OF_THE_WICKED_BUFF, values, player, TRIGGERED_FULL_MASK);
        if (Unit* pet = player->GetGuardianPet())
            player->CastCustomSpell(SPELL_SOD_WARLOCK_DANCE_OF_THE_WICKED_BUFF, values, pet, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterEffectProc += AuraEffectProcFn(spell_sod_warlock_dance_of_the_wicked::HandleCriticalStrike,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_warlock_dance_of_the_wicked()
{
    RegisterSpellScript(spell_sod_warlock_dance_of_the_wicked);
}
