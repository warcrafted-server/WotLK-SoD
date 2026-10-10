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
#include "Spell.h"
#include "SpellInfo.h"
#include "Unit.h"

#include <algorithm>

namespace
{
bool HasRequiredEnrage(Unit* unit)
{
    return unit->HasAura(SPELL_WARRIOR_ENRAGE)
        || unit->HasAura(SPELL_WARRIOR_BERSERKER_RAGE)
        || unit->HasAura(SPELL_WARRIOR_BLOODRAGE);
}
}

// Arremetida enfurecida: solo se puede usar mientras Enfurecer, Ira rabiosa o Ira sangrienta
// están activos. El requisito lo comprueba este script; el daño (115 % del arma) es un efecto
// WEAPON_PERCENT_DAMAGE del propio hechizo.
class spell_sod_warrior_raging_blow : public SpellScript
{
    PrepareSpellScript(spell_sod_warrior_raging_blow);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    SpellCastResult CheckRequirement()
    {
        Unit* caster = GetCaster();
        if (!caster || !HasRequiredEnrage(caster))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_warrior_raging_blow::CheckRequirement);
    }
};

// Cada facultad cuerpo a cuerpo usada mientras Enfurecer, Ira rabiosa o Ira sangrienta están
// activos recorta 1 s el enfriamiento restante de Arremetida enfurecida. Se aproxima "facultad
// cuerpo a cuerpo" a los hechizos de escuela física.
class player_sod_warrior_raging_blow : public PlayerScript
{
public:
    player_sod_warrior_raging_blow() : PlayerScript("player_sod_warrior_raging_blow") {}

    void OnPlayerSpellCast(Player* player, Spell* spell, bool /*skipCheck*/) override
    {
        if (!SodWarriorEnabled() || !player || !spell)
            return;

        if (!player->HasSpell(SPELL_SOD_WARRIOR_RAGING_BLOW) || !HasRequiredEnrage(player))
            return;

        SpellInfo const* info = spell->GetSpellInfo();
        if (!info || info->Id == SPELL_SOD_WARRIOR_RAGING_BLOW)
            return;
        if (!(info->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL))
            return;

        uint32 remaining = player->GetSpellCooldownDelay(SPELL_SOD_WARRIOR_RAGING_BLOW);
        if (!remaining)
            return;

        player->ModifySpellCooldown(SPELL_SOD_WARRIOR_RAGING_BLOW,
            -int32(std::min<uint32>(remaining, 1000)));
    }
};

void AddSC_sod_warrior_raging_blow()
{
    RegisterSpellScript(spell_sod_warrior_raging_blow);
    new player_sod_warrior_raging_blow();
}
