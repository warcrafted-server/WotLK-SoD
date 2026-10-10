/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Player.h"
#include "SpellInfo.h"
#include "Unit.h"

// Flagelación: el guerrero gana ira por el daño físico recibido como si no llevara armadura.
// El core ya concede ira sobre el daño mitigado (Unit::DealDamage -> RewardRage); aquí se
// suma la ira de la parte que absorbió la armadura. Los ataques automáticos llegan por
// ModifyMeleeDamage (daño antes de la armadura) y las facultades con arma por
// ModifySpellDamageTaken (daño ya mitigado), así que cada enganche calcula la diferencia.
class unit_sod_warrior_flagellation : public UnitScript
{
public:
    unit_sod_warrior_flagellation() : UnitScript("unit_sod_warrior_flagellation", true,
        { UNITHOOK_MODIFY_MELEE_DAMAGE, UNITHOOK_MODIFY_SPELL_DAMAGE_TAKEN }) {}

    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
    {
        if (!CanGainRage(target, attacker) || !damage)
            return;

        uint32 reduced = Unit::CalcArmorReducedDamage(attacker, target, damage, nullptr);
        if (reduced < damage)
            target->RewardRage(damage - reduced, 0, false);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage, SpellInfo const* spellInfo) override
    {
        if (damage <= 0 || !spellInfo || !(spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL))
            return;
        if (!CanGainRage(target, attacker))
            return;

        // El daño ya pasó por la armadura; se reconstruye el daño sin armadura para obtener
        // la parte que habría generado ira de más.
        uint32 probe = Unit::CalcArmorReducedDamage(attacker, target, 10000, spellInfo);
        if (!probe)
            return;

        uint32 unworn = uint32(uint64(damage) * 10000 / probe);
        if (unworn > uint32(damage))
            target->RewardRage(unworn - uint32(damage), 0, false);
    }

private:
    static bool CanGainRage(Unit* victim, Unit* attacker)
    {
        return SodWarriorEnabled() && victim && attacker && attacker != victim
            && victim->HasAura(SPELL_SOD_WARRIOR_FLAGELLATION)
            && victim->HasActivePowerType(POWER_RAGE);
    }
};

void AddSC_sod_warrior_flagellation()
{
    new unit_sod_warrior_flagellation();
}
