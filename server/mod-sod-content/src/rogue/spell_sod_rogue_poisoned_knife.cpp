/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Item.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellScript.h"

namespace
{
constexpr uint32 MASK_DEADLY_POISON = 0x00010000;
}

class spell_sod_rogue_poisoned_knife : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_poisoned_knife);

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void ApplyOffhandPoison()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetHitUnit();
        Item* offhand = rogue ? rogue->GetWeaponForAttack(OFF_ATTACK, true) : nullptr;
        if (!SodRogueEnabled() || !rogue || !target || !offhand)
            return;

        SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(
            offhand->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT));
        if (!enchant)
            return;

        for (uint8 index = 0; index < 3; ++index)
        {
            if (enchant->type[index] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                continue;

            uint32 const poisonSpellId = enchant->spellid[index];
            SpellInfo const* poison = sSpellMgr->GetSpellInfo(poisonSpellId);
            if (!poison || poison->SpellFamilyName != SPELLFAMILY_ROGUE
                || poison->Dispel != DISPEL_POISON)
                continue;

            Unit* poisonTarget = poison->IsPositive() ? static_cast<Unit*>(rogue) : target;
            SpellCastResult const result = rogue->CastSpell(poisonTarget, poisonSpellId, true, offhand);
            if (result == SPELL_CAST_OK && !poison->IsPositive()
                && (poison->SpellFamilyFlags[0] & MASK_DEADLY_POISON))
                rogue->ModifyPower(POWER_ENERGY, 5);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_poisoned_knife::CheckRogueRune);
        AfterHit += SpellHitFn(spell_sod_rogue_poisoned_knife::ApplyOffhandPoison);
    }
};

void AddSC_sod_rogue_poisoned_knife()
{
    RegisterSpellScript(spell_sod_rogue_poisoned_knife);
}
