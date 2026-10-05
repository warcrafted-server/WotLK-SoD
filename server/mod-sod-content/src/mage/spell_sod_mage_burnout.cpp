/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
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

#include "spell_sod_mage.h"
#include "Player.h"

class spell_sod_mage_burnout : public AuraScript
{
    PrepareAuraScript(spell_sod_mage_burnout);

    bool Load() override
    {
        return SodMageEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() != nullptr;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        int32 mana = int32(CalculatePct(player->GetCreateMana(), aurEff->GetAmount()));
        player->CastCustomSpell(SPELL_MAGE_BURNOUT_TRIGGER_CORE, SPELLVALUE_BASE_POINT0,
            mana, player, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_mage_burnout::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_mage_burnout::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_mage_burnout()
{
    RegisterSpellScript(spell_sod_mage_burnout);
}
