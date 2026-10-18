/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "spell_sod_druid.h"

#include "Creature.h"
#include "CreatureAI.h"

// Water of Elune'ara (433551), the quest item spell of The Lost Saplings (79377).
// In SoD the water credits the sapling it is used on, so the spell itself is a
// dummy aimed at a friendly creature: the credit is granted here for the sapling
// that was actually watered and the sapling says its line. AzerothCore has no
// "cast on creature" objective tracking (the objective only counts through
// Player::KilledMonsterCredit), so this cannot be done from data alone.

namespace
{
constexpr uint8 SOD_DRUID_SAPLING_TEXT_HEALED = 0;

bool IsAncientSapling(uint32 entry)
{
    switch (entry)
    {
        case 216437:  // Winter Sapling, Alterac Mountains
        case 216445:  // Spring Sapling, Swamp of Sorrows
        case 216448:  // Summer Sapling, Stranglethorn Vale
        case 216451:  // Autumn Sapling, Arathi Highlands
            return true;
        default:
            return false;
    }
}
}

class spell_sod_druid_water_of_eluneara : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_water_of_eluneara);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* target = GetHitUnit();
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!target || !caster || !IsAncientSapling(target->GetEntry()))
            return;

        caster->KilledMonsterCredit(target->GetEntry(), target->GetGUID());

        if (Creature* sapling = target->ToCreature())
            if (sapling->IsAIEnabled)
                sapling->AI()->Talk(SOD_DRUID_SAPLING_TEXT_HEALED, caster);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_druid_water_of_eluneara::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_sod_druid_water_of_eluneara()
{
    RegisterSpellScript(spell_sod_druid_water_of_eluneara);
}
