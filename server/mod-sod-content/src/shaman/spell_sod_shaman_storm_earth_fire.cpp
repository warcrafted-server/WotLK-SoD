/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_shaman_storm_earth_fire_earthbind : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_storm_earth_fire_earthbind);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void RootNearbyTargets(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* totem = GetCaster();
        Player* owner = totem ? totem->GetCharmerOrOwnerPlayerOrPlayerItself() : nullptr;
        if (totem && owner && owner->HasAura(SPELL_SOD_SHAMAN_STORM_EARTH_FIRE))
            totem->CastSpell(totem, SPELL_SHAMAN_EARTHGRAB, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_storm_earth_fire_earthbind::RootNearbyTargets,
            EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_storm_earth_fire()
{
    RegisterSpellScript(spell_sod_shaman_storm_earth_fire_earthbind);
}
