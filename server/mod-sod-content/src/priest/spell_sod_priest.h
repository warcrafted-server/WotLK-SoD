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
    SPELL_SOD_PRIEST_SHARED_PAIN = 401969,
    SPELL_SOD_PRIEST_MIND_SEAR = 413259,
    SPELL_SOD_PRIEST_SHADOW_WORD_DEATH = 401955,
    SPELL_SOD_PRIEST_EMPOWERED_RENEW = 425266,
    SPELL_SOD_PRIEST_MIND_SPIKE = 431655,
};

void AddSC_sod_priest_shared_pain();
void AddSC_sod_priest_empowered_renew();
void AddSC_sod_priest_mind_spike();

inline bool SodPriestEnabled()
{
    return sConfigMgr->GetOption<bool>("SodPriest.Enable", true);
}

#endif // MODULE_SOD_PRIEST_H
