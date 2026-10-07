/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifndef MODULE_SOD_PALADIN_H
#define MODULE_SOD_PALADIN_H

#include "Config.h"
#include "Define.h"

enum SodPaladinSpells
{
    SPELL_SOD_PALADIN_ART_OF_WAR = 426157,
    SPELL_SOD_PALADIN_RIGHTEOUS_VENGEANCE = 440672,
};

constexpr uint32 SPELL_PALADIN_EXORCISM_RANKS[] = {
    879, 5614, 5615, 10312, 10313, 10314, 27138, 48800, 48801
};

inline bool SodPaladinEnabled()
{
    return sConfigMgr->GetOption<bool>("SodPaladin.Enable", true);
}

inline int32 SodPaladinArtOfWarCooldownReductionMs()
{
    return sConfigMgr->GetOption<int32>("SodPaladin.ArtOfWar.CooldownReductionMs", 2000);
}

#endif // MODULE_SOD_PALADIN_H
