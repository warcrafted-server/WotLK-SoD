/* Declaraciones de hechizos y configuración de las runas de sacerdote. */

#ifndef MODULE_SOD_PRIEST_H
#define MODULE_SOD_PRIEST_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodPriestSpells
{
    SPELL_SOD_PRIEST_SERENDIPITY = 413248,
    SPELL_SOD_PRIEST_SERENDIPITY_BUFF = 413247,
    SPELL_SOD_PRIEST_STRENGTH_OF_SOUL = 415739,
    SPELL_SOD_PRIEST_TWISTED_FAITH = 425198,
    SPELL_SOD_PRIEST_HOMUNCULI = 402799,
    SPELL_SOD_PRIEST_PRAYER_OF_MENDING = 401859,
};

inline bool SodPriestEnabled()
{
    return sConfigMgr->GetOption<bool>("SodPriest.Enable", true);
}

#endif // MODULE_SOD_PRIEST_H
