/* Declaraciones de los hechizos y configuración de las runas de pícaro. */

#ifndef MODULE_SOD_ROGUE_H
#define MODULE_SOD_ROGUE_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodRogueSpells
{
    SPELL_SOD_ROGUE_DEADLY_BREW = 399965,
    SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND = 400014,
    SPELL_SOD_ROGUE_QUICK_DRAW = 398196,
    SPELL_SOD_ROGUE_SLAUGHTER_FROM_THE_SHADOWS = 424925,
    SPELL_SOD_ROGUE_BETWEEN_THE_EYES = 400009,
    SPELL_SOD_ROGUE_BLADE_DANCE = 400012,
    SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND_DODGE = 900066,
    SPELL_ROGUE_DEADLY_POISON = 2818,
    SPELL_ROGUE_TAUNT = 355,
    SPELL_ROGUE_BACKSTAB = 53,
    SPELL_ROGUE_AMBUSH = 8676,
    SPELL_ROGUE_FEINT = 1966,
};

void AddSC_sod_rogue_deadly_brew();
void AddSC_sod_rogue_just_a_flesh_wound();
void AddSC_sod_rogue_quick_draw();
void AddSC_sod_rogue_slaughter_from_the_shadows();
void AddSC_sod_rogue_between_the_eyes();

inline bool SodRogueEnabled()
{
    return sConfigMgr->GetOption<bool>("SodRogue.Enable", true);
}

#endif // MODULE_SOD_ROGUE_H
