/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_hunter.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

// Bestialidad: además de las mejoras de mascota (aura 900056 vía spell_pet_auras), el Bramido
// de la mascota provoca al objetivo. El hechizo 2649 lo lanza la mascota; si su dueño tiene la
// runa se lanza Provocar (355) sobre el objetivo golpeado. SoD da una duración propia (409372d)
// que no consta en el catálogo local: se conserva la de Provocar de WotLK. Ver TODO.md.
class spell_sod_hunter_beast_mastery_growl : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_beast_mastery_growl);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandleTaunt()
    {
        Unit* pet = GetCaster();
        Unit* target = GetHitUnit();
        if (!pet || !target)
            return;

        Unit* owner = pet->GetOwner();
        if (!owner || !owner->HasAura(SPELL_SOD_HUNTER_BEAST_MASTERY))
            return;

        pet->CastSpell(target, SPELL_SOD_HUNTER_TAUNT, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_sod_hunter_beast_mastery_growl::HandleTaunt);
    }
};

void AddSC_sod_hunter_beast_mastery()
{
    RegisterSpellScript(spell_sod_hunter_beast_mastery_growl);
}
