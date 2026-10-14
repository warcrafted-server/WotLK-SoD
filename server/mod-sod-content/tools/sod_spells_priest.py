#!/usr/bin/env python3
"""Priest spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403

SKILL_HOLY = 56
SKILL_DISCIPLINE = 613
SKILL_SHADOW = 78


def build(idx):
    """Return Priest spells cloned from the level-80 WotLK ranks."""
    return [
        {  # Circle of Healing keeps its target filter and healing coefficient.
            "id": 401946, "client": True, "template": 48089,
            "skill_line": SKILL_HOLY,
            "name": "Circle of Healing", "script": "spell_pri_circle_of_healing",
            "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "bonus": {"direct": 0.402, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "ManaCostPct": 56,
                "SpellLevel": 0,
            },
        },
        {  # Penance's core script requires the original WotLK rank chain.
            "id": 402174, "client": True, "template": 53007,
            "skill_line": SKILL_DISCIPLINE,
            "name": "Penance", "inherit_server": True,
            # El script del core va ligado a -47540 (primer rango); el id nuevo no lo hereda.
            "script": "spell_pri_penance",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Serendipia reutiliza el proc de WotLK y su aura de reducción del tiempo de lanzamiento.
            "id": 413248, "client": True, "template": 63737,
            "skill_line": SKILL_HOLY,
            "name": "Serendipity", "inherit_server": True,
            "desc": "Healing with Flash Heal reduces the cast time of your next Lesser Heal, Heal, Greater Heal, or Prayer of Healing by $413247s1% for $413247d, stacking up to $413247u times.",
            "overrides": {
                "SpellLevel": 0,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 413247,
            },
            # Copia de spell_proc -63730; la runa activa el proc en cada Sanación relámpago.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 6,
                "SpellFamilyMask0": 0x800, "SpellFamilyMask1": 0x4,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 100, "Charges": 0,
            },
        },
        {  # Aura de celeridad de lanzamiento que activa Serendipia.
            "id": 413247, "client": True, "template": 63734,
            "skill_line": SKILL_HOLY,
            "name": "Serendipity", "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
                "CumulativeAura": 3,
            },
        },
        {  # La mecánica queda pendiente porque faltan los datos del auxiliar 409317.
            "id": 415739, "client": True, "template": 774,
            "skill_line": SKILL_HOLY,
            "name": "Strength of Soul",
            "desc": "Lesser Heal, Heal, Greater Heal, and Flash Heal reduce the remaining duration of Weakened Soul on targets they heal. Damage absorbed by your Power Word: Shield also generates Rage and triggers Righteous Fury as if it were a heal.",
            "overrides": {
                "SpellLevel": 0,
                "SpellClassSet": 6,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": 0, "EffectAura_1": 0,
                "Effect_2": 0, "EffectAura_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
        {  # Mantiene el modificador nativo de WotLK condicionado por Palabra de las Sombras: dolor.
            "id": 425198, "client": True, "template": 51167,
            "skill_line": SKILL_SHADOW,
            "name": "Twisted Faith", "inherit_server": True,
            "desc": "Mind Flay and Mind Blast deal $s2% increased damage to targets afflicted with your Shadow Word: Pain.",
            "overrides": {
                "SpellLevel": 0,
                # El efecto 2 nativo aplica el aumento de daño; los efectos de intelecto se retiran.
                "Effect_1": 0, "EffectAura_1": 0,
                "Effect_2": 6, "EffectAura_2": 112,
                "EffectBasePoints_2": 50, "EffectDieSides_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
        {  # Aproximación jugable con el esbirro de WotLK más cercano disponible.
            "id": 402799, "client": True, "template": 34433,
            "skill_line": SKILL_SHADOW,
            "name": "Homunculi", "inherit_server": True,
            "desc": "Summons a Shadowfiend to attack your current target. This WotLK approximation summons one familiar instead of three Homunculi.",
            "overrides": {
                "SpellLevel": 0,
                "RecoveryTime": 120000,
                "DurationIndex": idx["dur"][120000],
            },
        },
        {  # El motor nativo de WotLK conserva los saltos y el escudo con cargas de Rezo de alivio.
            "id": 401859, "client": True, "template": 48113,
            "skill_line": SKILL_HOLY,
            "name": "Prayer of Mending", "inherit_server": True,
            "desc": "Places a spell on the target that heals them the next time they take damage or receive healing. When the heal occurs, Prayer of Mending jumps to another party or raid member.",
            "bonus": {"direct": 0.8057, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            # Copia de spell_proc -33076; el id nuevo no hereda el disparador nativo.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 664232, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "overrides": {
                "SpellLevel": 0, "ManaCostPct": 15, "RecoveryTime": 10000,
                "SpellClassSet": 6,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0x20, "SpellClassMask_3": 0x400,
                "EffectBasePoints_1": 74, "EffectDieSides_1": 0,
                "EffectBasePoints_2": 5, "EffectDieSides_2": 0,
            },
        },
        {  # El guion reparte Palabra de las Sombras: dolor a dos enemigos cercanos.
            "id": 401969, "client": True, "template": 774,
            "skill_line": SKILL_SHADOW,
            "name": "Shared Pain",
            "desc": "Your Shadow Word: Pain now also afflicts up to ${$m1-1} additional nearby targets within $s2 yards.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": idx["cast"][0],
                "DurationIndex": idx["dur"][-1],
                "RangeIndex": idx["range"][0.0],
                "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellLevel": 0, "SpellClassSet": 6,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": 6, "EffectAura_1": 4,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
        {  # Mind Sear conserva el filtrado nativo del objetivo de canalización.
            "id": 413259, "client": True, "template": 53023,
            "skill_line": SKILL_SHADOW,
            "name": "Mind Sear", "script": "spell_pri_mind_sear",
            "inherit_server": True,
            "desc": "Causes an explosion of shadow magic damaging the enemy target and other nearby enemies, causing ${$413260m1/100*$<damagepower>} to ${$413260M1/100*$<damagepower>} Shadow damage every $T1 sec for $d to all enemies within $413260a1 yards of the target.",
            "overrides": {
                "SpellLevel": 0,
                "ManaCostPct": 28,
                "RecoveryTime": 0,
                "DurationIndex": idx["dur"][6000],
                "EffectTriggerSpell_1": 413260,
            },
        },
        {  # Hechizo auxiliar real de Mind Sear, clonado para resolver los datos del texto.
            "id": 413260, "client": True, "template": 53022,
            "name": "Mind Sear", "inherit_server": True,
            # El script del core va ligado a -49821 (primer rango); el id nuevo no lo hereda.
            "script": "spell_pri_mind_sear",
            "overrides": {"SpellLevel": 0},
        },
        {  # El script nativo mantiene la represalia de Palabra de las Sombras: muerte.
            "id": 401955, "client": True, "template": 48158,
            "skill_line": SKILL_SHADOW,
            "name": "Shadow Word: Death", "script": "spell_pri_shadow_word_death",
            "inherit_server": True,
            "desc": "A word of dark binding that inflicts ${$<damagepower>*$m1/100} to ${$<damagepower>*$M1/100} Shadow damage to the target. If the target is not killed by Shadow Word: Death, the caster takes damage equal to $m2% of the damage attempted against the target.",
            "overrides": {
                "SpellLevel": 0,
                "ManaCostPct": 12,
                "RecoveryTime": 12000,
            },
        },
        {  # El aura de talento nativa da el golpe de sanación inmediato al aplicar Renovar.
            "id": 425266, "client": True, "template": 63543,
            "skill_line": SKILL_HOLY,
            "name": "Empowered Renew", "inherit_server": True,
            "desc": "Your Renew now heals one extra time immediately when applied, and gains $s1% increased benefit each time it heals from your bonus healing effects. In addition, your Renew can now be active on targets affected by another Priest's Renew.",
            "overrides": {
                "SpellLevel": 0,
                # El manejador nativo de Renovar lee el efecto 2 del talento (índice 1).
                "EffectBasePoints_2": 15, "EffectDieSides_2": 0,
            },
        },
        {  # El aura del objetivo representa las acumulaciones de crítico de Púa mental.
            "id": 431655, "client": True, "template": 48127,
            "skill_line": SKILL_SHADOW,
            "name": "Mind Spike", "script": "spell_sod_priest_mind_spike",
            "desc": "Blasts the target for ${$m1*$<damagepower>/100} to ${$M1*$<damagepower>/100} Shadowfrost damage, and increases the critical strike chance of your next Mind Blast on the target by $s2%, stacking up to $u times.",
            "aura_desc": "Chance for Mind Blast to critically hit from casting Priest increased by $s2%.",
            "bonus": {"direct": 0.429, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "SpellLevel": 0,
                "ManaCostPct": 6,
                "RecoveryTime": 0,
                "DurationIndex": idx["dur"][10000],
                "SchoolMask": 48,
                "Effect_1": 2,
                "EffectBasePoints_1": 121, "EffectDieSides_1": 0,
                "Effect_2": 6, "EffectAura_2": 179,
                "EffectBasePoints_2": 30, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 32,
                "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "EffectSpellClassMaskA_2": 0x2000,
                "CumulativeAura": 3,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
    ]
