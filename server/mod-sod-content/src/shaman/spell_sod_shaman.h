/* Declaraciones de los hechizos y la configuración de las runas de chamán. */

#ifndef MODULE_SOD_SHAMAN_H
#define MODULE_SOD_SHAMAN_H

#include "Config.h"

enum SodShamanSpells
{
    SPELL_SOD_SHAMAN_LAVA_BURST = 408490,
    SPELL_SOD_SHAMAN_RIPTIDE = 408521,
    SPELL_SOD_SHAMAN_FERAL_SPIRIT = 440580,
    SPELL_SOD_SHAMAN_MAELSTROM_WEAPON = 408498,
    SPELL_SOD_SHAMAN_MAELSTROM_WEAPON_AURA = 408505,
    SPELL_SOD_SHAMAN_TIDAL_WAVES = 432042,
    SPELL_SOD_SHAMAN_ANCESTRAL_AWAKENING = 425858,
};

inline bool SodShamanEnabled()
{
    return sConfigMgr->GetOption<bool>("SodShaman.Enable", true);
}

#endif // MODULE_SOD_SHAMAN_H
