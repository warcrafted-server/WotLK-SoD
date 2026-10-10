#!/usr/bin/env python3
"""Warrior spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)

# Líneas de habilidad del guerrero (controlan la pestaña del libro de hechizos).
SKILL_ARMS = 26
SKILL_FURY = 256
SKILL_PROTECTION = 257

# Auras nativas de 3.3.5a que usan las runas del guerrero (SpellAuraDefines.h del core).
AURA_MOD_IGNORE_SHAPESHIFT = 275      # anula el requisito de actitud; filtra por máscara de familia
AURA_ABILITY_IGNORE_AURASTATE = 262   # ignora el estado del lanzador; con MiscValue 1 también el combate
AURA_ADD_FLAT_MODIFIER = 107
AURA_ADD_PCT_MODIFIER = 108
AURA_MELEE_HASTE = 138                # % de celeridad cuerpo a cuerpo
AURA_MOD_SPEED_ALWAYS = 129           # % de velocidad de movimiento (Acecho / Furia enfocada)
AURA_PROC_TRIGGER_SPELL = 42          # dispara otro hechizo al procar
AURA_MOD_ATTACK_POWER_PCT = 166       # % de poder de ataque (Desenfreno)
# Duración de un mecánico, sin acumularse con otros reductores (Maestría con escudos).
AURA_MECHANIC_DURATION_MOD_NOT_STACK = 234
MECHANIC_DISARMED = 3                 # índice del mecánico de desarme
SPELLMOD_THREAT = 2                   # SpellModOp 2 de 3.3.5a: amenaza
SPELLMOD_EFFECT1 = 3                  # SpellModOp 3: valor del efecto 1 (daño)
SPELLMOD_CASTING_TIME = 10            # SpellModOp 10: tiempo de lanzamiento (Embate de Sincronización precisa)
SPELLMOD_COOLDOWN = 11                # SpellModOp 11: enfriamiento
SPELLMOD_EFFECT2 = 12                 # SpellModOp 12: valor del efecto 2 (ralentización de Atronar)
SPELLMOD_COST = 14                    # SpellModOp 14: coste de recurso (ira)
SPELLMOD_DOT = 22                     # SpellModOp 22 de 3.3.5a: daño periódico

EFFECT_PULL_TOWARDS = 124             # arrastra al objetivo hacia el lanzador
EFFECT_WEAPON_PERCENT_DAMAGE = 31
EFFECT_HEAL_PCT = 136                 # cura un porcentaje de la salud máxima

# Máscara de familia de Atronar (SpellClassMask_1 0x80), Golpe heroico (0x40) y Embate (0x200000).
MASK_THUNDER_CLAP = 0x80
MASK_HEROIC_STRIKE = 0x40
MASK_SLAM = 0x200000

# Ataques automáticos cuerpo a cuerpo con éxito (para el proc de Furia enfocada).
PROC_MELEE_AUTO_ATTACK = 0x4

# Ataques cuerpo a cuerpo con éxito: automáticos y facultades de escuela física.
PROC_MELEE_HITS = 0x400014

# Máscaras de familia de WotLK (SpellClassSet 4) de los hechizos nativos que se modifican.
MASK_REND = 0x20
MASK_CHARGE = 0x1
MASK_INTERCEPT = 0x40000000
MASK_INTERVENE = 0x10000

# Auras nativas de 3.3.5a que usan las runas de la cuarta tanda.
AURA_MOD_SHAPESHIFT = 36              # actitud (forma)
AURA_MOD_BLOCK_PERCENT = 51           # % de probabilidad de bloqueo
# AURA_MOD_DAMAGE_PERCENT_DONE (79) ya la define sod_dbc.
AURA_MOD_RESISTANCE_PCT = 101         # % de armadura/resistencia; miscvalue = escuela
AURA_MOD_THREAT = 10                  # % de amenaza generada
AURA_MOD_INCREASE_HEALTH_PERCENT = 133  # % de salud máxima

FORM_SOD_GLADIATOR = 24               # forma de Actitud de gladiador (no existe en 3.3.5a)
MASK_ALL_SPELLS = 0xFFFFFFFF          # todas las máscaras de familia (actitud de gladiador)


def build(idx):
    """Return Warrior spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    range_melee = idx["range"][5.0]
    range_30 = idx["range"][30.0]

    return [
        {  # Devastate: retain the WotLK rank effects.
            "id": 403195, "client": True, "template": 47498,
            "skill_line": 257,
            "name": "Devastate", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
        {  # Frenesí sangriento: Desgarrar en actitud rabiosa (aura 275) y +100 % de su daño
           # periódico (aura 108 + SpellModOp 22), ambos sobre la máscara de Desgarrar. El
           # daño extra por poder de ataque lo suma el script `spell_sod_warrior_blood_frenzy`
           # en cada tick de Desgarrar.
            "id": 412507, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Blood Frenzy",
            "desc": "Rend can now be used in Berserker stance, Rend's damage is increased by "
                    "$s2%, and Rend deals additional damage equal to $s3% of your Attack "
                    "Power each time it deals damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_bloodfrenzy"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "EffectSpellClassMaskA_1": MASK_REND,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_ADD_PCT_MODIFIER,
                "EffectBasePoints_2": 100, "EffectDieSides_2": 0, "EffectMiscValue_2": SPELLMOD_DOT,
                "EffectSpellClassMaskA_2": MASK_REND,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_DUMMY,
                "EffectBasePoints_3": 4, "EffectDieSides_3": 0,
                "EffectSpellClassMaskA_3": MASK_REND,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Flagelación: pasiva de marcador; el script de unidad `unit_sod_warrior_flagellation`
           # concede la ira del daño físico recibido como si no hubiera armadura.
            "id": 402877, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Flagellation",
            "desc": "You gain Rage from Physical damage taken as if you were wearing no armor.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_bloodbath"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_DUMMY,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Arremetida enfurecida: 115 % de daño con arma. El script `spell_sod_warrior_raging_blow`
           # exige Enfurecer, Ira rabiosa o Ira sangrienta, y el reductor de enfriamiento vive en
           # `player_sod_warrior_raging_blow`.
            "id": 402911, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Raging Blow", "script": "spell_sod_warrior_raging_blow",
            "desc": "A ferocious strike that deals $s1% weapon damage, but can only be used "
                    "while Enrage, Berserker Rage, or Bloodrage is active. Each other melee "
                    "ability used while Enrage, Berserker Rage, or Bloodrage is active reduces "
                    "Raging Blow's remaining cooldown by $s3 sec.",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_melee, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 8000, "CategoryRecoveryTime": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_savageblow"],
                "Effect_1": EFFECT_WEAPON_PERCENT_DAMAGE, "EffectBasePoints_1": 114,
                "EffectDieSides_1": 1, "EffectAura_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": EFFECT_DUMMY, "EffectBasePoints_2": 1, "EffectDieSides_2": 0,
                "EffectAura_2": 0, "ImplicitTargetA_2": TARGET_UNIT_TARGET_ENEMY,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Belisario: las auras 262 (MiscValue 1) y 275 hacen Cargar, Interceptar e Intervenir
           # usables en combate y en cualquier actitud; el script `spell_sod_warrior_warbringer`
           # quita los efectos de reducción de movimiento al activarlas.
            "id": 425421, "client": True, "template": 774,
            "skill_line": SKILL_PROTECTION,
            "name": "Warbringer",
            "desc": "Your Charge, Intercept, and Intervene abilities are now usable while in "
                    "combat and in any stance, and will all remove movement impairing effects "
                    "when activated.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_warbringer"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_ABILITY_IGNORE_AURASTATE,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0, "EffectMiscValue_1": 1,
                "EffectSpellClassMaskA_1": MASK_CHARGE,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "EffectSpellClassMaskA_2": MASK_CHARGE | MASK_INTERCEPT,
                "EffectSpellClassMaskB_2": MASK_INTERVENE,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Grito de orden: clon del Grito de orden de WotLK (47440), que el core ya implementa.
           # Diferencia conocida: en 3.3.5a el grito sube la salud máxima (aura 230) y SoD el
           # aguante (aura 29); se conserva el comportamiento nativo del cliente.
            "id": 403215, "client": True, "template": 47440,
            "skill_line": SKILL_FURY,
            "name": "Commanding Shout", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
        {  # Consumido por la ira: pasiva de marcador (aura 226 periódica) que engancha
           # `spell_sod_warrior_consumed_by_rage`: al superar 60 de ira aplica Enfurecer nativo
           # (12880), que activa las facultades que lo exigen. El golpe de mano izquierda de
           # Torbellino mientras dura ya lo resuelve el Torbellino nativo (disparo 44949).
            "id": 425418, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Consumed By Rage", "script": "spell_sod_warrior_consumed_by_rage",
            "desc": "Enrages you for 12 sec after you exceed $s1 Rage, allowing abilities that "
                    "require being Enraged. In addition, Whirlwind also strikes with off-hand "
                    "melee weapons while you are Enraged.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_intensifyrage"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_1": 60, "EffectDieSides_1": 0, "EffectAuraPeriod_1": 1000,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Asalto frenético: el aura 226 (periodo 2 s) hace que el script aplique o retire la
           # celeridad auxiliar 900052 según se empuñe un arma a dos manos; el proc del aura
           # dummy 4 añade 2 de ira por golpe (4 en crítico).
            "id": 425412, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Frenzied Assault", "script": "spell_sod_warrior_frenzied_assault",
            "desc": "While wielding 2-handed weapons, your attack speed is increased by $s1% and "
                    "your successful melee hits generate $s2 additional Rage, or ${$m2*2} "
                    "additional Rage if they are critical hits.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_unrelentingassault"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_1": 40, "EffectDieSides_1": 0, "EffectAuraPeriod_1": 2000,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 2, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": PROC_MELEE_HITS, "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Trueno de furia: auras nativas sobre Atronar (máscara 0x80). El efecto 0 sube 6 %
           # la ralentización (SpellModOp 12, el valor del efecto 2) y el efecto 2 aumenta el
           # daño un 100 % (SpellModOp 3); el efecto 1 anula el requisito de actitud. La subida
           # de amenaza del catálogo (SpellModOp 2) no cabe en los 3 efectos de 3.3.5a: ver TODO.
            "id": 403219, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Furious Thunder",
            "desc": "Thunder Clap now increases the time between attacks by an additional $s1%, "
                    "can be used in any stance, and deals $s3% increased damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_thunderclap"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_ADD_FLAT_MODIFIER,
                "EffectBasePoints_1": -6, "EffectDieSides_1": 0,
                "EffectMiscValue_1": SPELLMOD_EFFECT2,
                "EffectSpellClassMaskA_1": MASK_THUNDER_CLAP,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_IGNORE_SHAPESHIFT,
                "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "EffectSpellClassMaskA_2": MASK_THUNDER_CLAP,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_ADD_PCT_MODIFIER,
                "EffectBasePoints_3": 100, "EffectDieSides_3": 0,
                "EffectMiscValue_3": SPELLMOD_EFFECT1,
                "EffectSpellClassMaskA_3": MASK_THUNDER_CLAP,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Gancho: activa; el efecto 124 (arrastre hacia el lanzador) es el nativo de 3.3.5a.
           # El script `spell_sod_warrior_meathook` comprueba el nivel y que no sea un jefe.
            "id": 403228, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Meathook", "script": "spell_sod_warrior_meathook",
            "desc": "Throw out a hooked chain to restrain the target and pull them toward you. "
                    "May not be used on enemies higher than level ${$PL+1} or which are marked "
                    "as boss enemies.",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": 0,
                "RangeIndex": range_30, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 150, "ManaCostPct": 0,
                "RecoveryTime": 35000, "CategoryRecoveryTime": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["inv_misc_hook_01"],
                "Effect_1": EFFECT_PULL_TOWARDS, "EffectBasePoints_1": 0,
                "EffectDieSides_1": 0, "EffectAura_1": 0, "EffectMiscValue_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Golpe rápido: golpe físico basado en el poder de ataque (coeficiente 0,29 tomado del
           # $m1/100 del catálogo; no se pudo verificar el dado). Lleva la máscara de Golpe heroico
           # (0x40) para heredar sus talentos; el script exige un arma a dos manos y en
           # sod_warrior_runes.sql se engancha el script del core `spell_warr_heroic_strike`.
            "id": 429765, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Quick Strike", "script": "spell_sod_warrior_quick_strike",
            "desc": "A reckless instant melee attack with your two-handed weapon dealing damage "
                    "based on your Attack Power. This ability benefits from and triggers all "
                    "effects associated with Heroic Strike.",
            "bonus": {"direct": 0.0, "dot": 0.0, "ap": 0.29, "ap_dot": 0.0},
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": 0,
                "RangeIndex": range_melee, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 200, "ManaCostPct": 0,
                "RecoveryTime": 0, "CategoryRecoveryTime": 0, "DefenseType": 2,
                "SpellClassSet": 4, "SpellClassMask_1": MASK_HEROIC_STRIKE,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_decisivestrike"],
                "Effect_1": EFFECT_SCHOOL_DAMAGE, "EffectBasePoints_1": 0,
                "EffectDieSides_1": 0, "EffectAura_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Furia enfocada: marcador pasivo (aura 226 periódica) y aura dummy para el proc de
           # ataque automático. El script concede la velocidad si hay doble empuñadura y acumula
           # celeridad (461470) al golpear al mismo objetivo que el ataque automático anterior.
            "id": 413404, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Single-Minded Fury", "script": "spell_sod_warrior_single_minded_fury",
            "desc": "While dual-wielding, your movement speed is increased by 10% and you gain "
                    "4% attack speed each time your melee auto-attack strikes the same target as "
                    "your previous auto-attack, stacking up to 5 times. Lasts 10 sec or until "
                    "your auto-attack strikes a different target.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_dualwield"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_1": 10, "EffectDieSides_1": 0, "EffectAuraPeriod_1": 2000,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_DUMMY,
                "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": PROC_MELEE_AUTO_ATTACK, "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Ataque de la victoria: clon del de WotLK (34428), que ya escala con el poder de ataque
           # por los flags de familia del core; se le añaden la sanación de SoD (30 %) y 8 s de
           # enfriamiento. El script del core retira el estado Victorioso al lanzarlo.
            "id": 402927, "client": True, "template": 34428,
            "skill_line": SKILL_ARMS,
            "name": "Victory Rush", "script": "spell_warr_victory_rush",
            "inherit_server": True,
            "desc": "Instantly attack the target causing ${1+$AP*$m3/100} damage and healing you "
                    "for $s2% of your maximum health. Only useable within $32216d after you kill "
                    "an enemy that yields experience or honor.",
            "overrides": {
                "SpellLevel": 0, "RecoveryTime": 8000,
                "Effect_2": EFFECT_HEAL_PCT, "EffectAura_2": 0,
                "EffectBasePoints_2": 30, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_DUMMY, "EffectAura_3": 0,
                "EffectBasePoints_3": 45, "EffectDieSides_3": 0,
                "ImplicitTargetA_3": TARGET_UNIT_TARGET_ENEMY,
            },
        },
        {  # Oleada sangrienta: pasiva con aura 42 que dispara la marca 413399 al acertar Golpe
           # heroico, Sed de sangre o Torbellino. La probabilidad (30 %) va en la fila spell_proc.
            "id": 413380, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Blood Surge",
            "desc": "Heroic Strike, Bloodthirst, and Whirlwind have a $h% chance to make your "
                    "next Slam within $413399d instant and cost no Rage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_bloodsurge"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PROC_TRIGGER_SPELL,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 413399,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 4,
                "SpellFamilyMask0": MASK_HEROIC_STRIKE, "SpellFamilyMask1": 0x404,
                "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 30, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Ira enfocada: clon del talento de WotLK 29787 (aura 107, SpellModOp 14) con el valor de
           # SoD (−30 = −3 de ira). El id de SoD (29787) ya existe en el cliente y el generador no
           # permite crear una fila con un id existente, así que se usa un id nuevo (413405).
            "id": 413405, "client": True, "template": 29787,
            "skill_line": SKILL_FURY,
            "name": "Focused Rage",
            "desc": "Reduces the rage cost of your offensive abilities by $/10;s1.",
            "overrides": {
                "SpellLevel": 0,
                "EffectBasePoints_1": -30, "EffectDieSides_1": 0,
            },
        },
        {  # Sincronización precisa: Embate instantáneo con 6 s de enfriamiento (auras nativas 108 y
           # 107 sobre la máscara de Embate 0x200000).
            "id": 402922, "client": True, "template": 774,
            "skill_line": SKILL_ARMS,
            "name": "Precise Timing",
            "desc": "Slam is now instant but has a ${$m2/1000} sec cooldown.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_decisivestrike"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_ADD_PCT_MODIFIER,
                "EffectBasePoints_1": -100, "EffectDieSides_1": 0,
                "EffectMiscValue_1": SPELLMOD_CASTING_TIME,
                "EffectSpellClassMaskA_1": MASK_SLAM,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_ADD_FLAT_MODIFIER,
                "EffectBasePoints_2": 6000, "EffectDieSides_2": 0,
                "EffectMiscValue_2": SPELLMOD_COOLDOWN,
                "EffectSpellClassMaskA_2": MASK_SLAM,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Furia enfocada (velocidad): +10 % de velocidad de movimiento durante 3 s; el sondeo de
           # 2 s del marcador la renueva mientras haya doble empuñadura.
            "id": 430472, "client": True, "template": 774,
            "name": "Single-Minded Fury",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][3000],
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_SPEED_ALWAYS,
                "EffectBasePoints_1": 10, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Furia enfocada (celeridad): +4 % de velocidad de ataque, hasta 5 acumulaciones, 10 s.
            "id": 461470, "client": True, "template": 774,
            "name": "Single-Minded",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][10000],
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "CumulativeAura": 5, "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MELEE_HASTE,
                "EffectBasePoints_1": 4, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Oleada sangrienta (marca): clon del ¡Embate! de WotLK (46916) que además deja Embate
           # instantáneo lo deja sin coste. Se copia el proc nativo de 46916 para que la marca se
           # consuma al lanzar Embate.
            "id": 413399, "client": True, "template": 46916,
            "name": "Blood Surge",
            "overrides": {
                "SpellLevel": 0, "DurationIndex": idx["dur"][15000],
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_ADD_PCT_MODIFIER,
                "EffectBasePoints_2": -100, "EffectDieSides_2": 0,
                "EffectMiscValue_2": SPELLMOD_COST,
                "EffectSpellClassMaskA_2": MASK_SLAM,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 4,
                "SpellFamilyMask0": MASK_SLAM, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 4,
                "HitMask": 0, "AttributesMask": 2, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Regeneración iracunda: clon del de WotLK (55694), que ya sana un 3 % de la salud
           # máxima cada segundo durante 10 s, exige estar enfurecido (estado de aura 17, que
           # cubren Enfurecer, Ira rabiosa e Ira sangrienta) y es usable aturdido (inmunidad al
           # aturdimiento del efecto 2).
            "id": 402913, "client": True, "template": 55694,
            "skill_line": SKILL_FURY,
            "name": "Enraged Regeneration", "inherit_server": True,
            "desc": "Heals you for $o1% of your maximum health over $d, but can only be used "
                    "while Enrage, Berserker Rage, or Bloodrage is active. Useable while "
                    "Stunned.",
            "overrides": {"SpellLevel": 0},
        },
        {  # Actitud de gladiador: el aura 36 (forma 24) la marca como actitud; el sondeo de 1 s
           # (aura 226) mantiene el auxiliar 900053 (bono con escudo: +10 % de daño y +10 % de
           # bloqueo, más el aura 275 con todas las máscaras para poder usar facultades de otras
           # actitudes) y el auxiliar 900054 (−30 % de armadura y −30 % de amenaza). Diferencias
           # conocidas en TODO.md: la forma 24 no existe en el cliente de 3.3.5a y no se
           # implementa el bono de ira de los ataques automáticos contra quien no te ataca.
            "id": 412513, "client": True, "template": 774,
            "skill_line": SKILL_PROTECTION,
            "name": "Gladiator Stance", "script": "spell_sod_warrior_gladiator_stance",
            "desc": "An aggressive stance: while you are wearing a shield it increases your "
                    "damage by 10% and your block chance by 10%, but it reduces your armor by "
                    "30% and the threat you generate by 30%. While wearing a shield in "
                    "Gladiator Stance you may use all abilities that are restricted to other "
                    "stances.",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 0, "CategoryRecoveryTime": 1000,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_offensivestance"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_SHAPESHIFT,
                "EffectBasePoints_1": -1, "EffectDieSides_1": 1,
                "EffectMiscValue_1": FORM_SOD_GLADIATOR,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_2": 50, "EffectDieSides_2": 0, "EffectAuraPeriod_2": 1000,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_MOD_DAMAGE_PERCENT_DONE,
                "EffectBasePoints_3": 0, "EffectDieSides_3": 0, "EffectMiscValue_3": 127,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Intervenir: clon del de WotLK (3411), que ya corre hacia el aliado, intercepta el
           # siguiente ataque y le reduce la amenaza. Se copia el script del core que lanza el
           # disparo 59667 (el id nuevo no hereda la fila de spell_script_names de 3411).
            "id": 403338, "client": True, "template": 3411,
            "skill_line": SKILL_PROTECTION,
            "name": "Intervene", "script": "spell_warr_intervene",
            "inherit_server": True,
            "desc": "Run at high speed towards a party member, intercepting the next melee or "
                    "ranged attack made against them, and reducing their total threat.",
            "overrides": {"SpellLevel": 0},
        },
        {  # Berrido de convocación: +15 % de salud máxima al grupo y la banda durante 10 s.
           # Clon del Grito de orden (47440) con la salud fija (aura 230) cambiada a porcentaje
           # (aura 133); conserva el objetivo de raid, el radio y el coste nativos.
            "id": 426490, "client": True, "template": 47440,
            "skill_line": SKILL_FURY,
            "name": "Rallying Cry", "inherit_server": True,
            "desc": "Let loose a rallying cry, granting all party and raid members within $a1 "
                    "yards $s1% increased maximum health for $d.",
            "overrides": {
                "SpellLevel": 0, "DurationIndex": idx["dur"][10000],
                "RecoveryTime": 180000,
                "Effect_1": EFFECT_APPLY_AURA,
                "EffectAura_1": AURA_MOD_INCREASE_HEALTH_PERCENT,
                "EffectBasePoints_1": 15, "EffectDieSides_1": 0, "EffectMiscValue_1": 0,
            },
        },
        {  # Ira interminable: clon del talento de WotLK (29623, aura 213) como pasiva gratuita;
           # +25 % de ira por todo el daño infligido.
            "id": 403218, "client": True, "template": 29623,
            "skill_line": SKILL_FURY,
            "name": "Endless Rage", "inherit_server": True,
            "desc": "You generate $s1% more Rage from all damage you deal.",
            "overrides": {"SpellLevel": 0},
        },
        {  # Maestría con escudos: marcador pasivo. El sondeo de 2 s (aura 226) concede el +9 %
           # al daño físico (auxiliar 900055, aura 79 de escuela física) mientras el guerrero
           # empuñe un escudo, y lo retira si no lo lleva; el aura 234 reduce un 51 % la
           # duración de todo desarme (mecánico 3) de forma nativa y sin acumularse.
            "id": 426980, "client": True, "template": 774,
            "skill_line": SKILL_PROTECTION,
            "name": "Shield Mastery", "script": "spell_sod_warrior_shield_mastery",
            "desc": "Increases all physical damage you deal by 9% while you have a shield "
                    "equipped, and reduces the duration of all Disarm effects used against "
                    "you by 51%. This does not stack with other Disarm duration reducing "
                    "effects.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_shieldmastery"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_PERIODIC_DUMMY,
                "EffectBasePoints_1": 9, "EffectDieSides_1": 0, "EffectAuraPeriod_1": 2000,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA,
                "EffectAura_2": AURA_MECHANIC_DURATION_MOD_NOT_STACK,
                "EffectBasePoints_2": -51, "EffectDieSides_2": 0,
                "EffectMiscValue_2": MECHANIC_DISARMED,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Gusto por la sangre: pasiva; el aura 42 dispara la marca 426969 cuando Desgarrar
           # inflige daño. El filtro de proc se copia de la fila spell_proc de -56636 (familia 4,
           # máscara de Desgarrar 0x20, máximo una vez cada 5,8 s).
            "id": 426953, "client": True, "template": 56636,
            "skill_line": SKILL_ARMS,
            "name": "Taste for Blood", "inherit_server": True,
            "desc": "Whenever your Rend ability causes damage, your Overpower ability will "
                    "activate for $426969d or 1 attack. This effect will not occur more than "
                    "once every $s1 sec.",
            "overrides": {
                "SpellLevel": 0, "ProcChance": 100,
                "EffectBasePoints_1": 6, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 426969, "EffectMiscValue_1": 0,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 4,
                "SpellFamilyMask0": MASK_REND, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 5800, "Charges": 0,
            },
        },
        {  # Marca de Gusto por la sangre: clon del beneficio de WotLK 60503 (aura 262 sobre
           # Abrumar), que deja usar Abrumar sin el requisito de estado. La aplica la marca
           # 426953 durante su duración.
            "id": 426969, "client": True, "template": 60503,
            "name": "Taste for Blood", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
            # Copia de spell_proc 60503: consume la marca al usar Abrumar (máscara 0x4). El
            # id nuevo no hereda la fila del core.
            "proc": {
                "SchoolMask": 1, "SpellFamilyName": 4,
                "SpellFamilyMask0": 4, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Vigilancia: clon del de WotLK 50720, cuyo script del core (spell_warr_vigilance)
           # aplica la reducción de daño, redirige el 10 % de la amenaza al guerrero y, al
           # recibir el objetivo un ataque, reinicia Provocar. La duración de 30 min y el
           # límite de un solo objetivo son nativos de la plantilla.
            "id": 426972, "client": True, "template": 50720,
            "skill_line": SKILL_PROTECTION,
            "name": "Vigilance", "script": "spell_warr_vigilance", "inherit_server": True,
            "desc": "Focus your protective gaze on a party or raid member, reducing their "
                    "damage taken by $s1% and transferring $m2% of the threat they cause to "
                    "you. In addition, each time they are hit by an attack your Taunt "
                    "cooldown is refreshed. Lasts $d. This effect can only be on one target "
                    "at a time.",
            "overrides": {
                "SpellLevel": 0, "RecoveryTime": 0,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
            },
        },
        {  # Desenfreno: activa (30 s de duración, 90 s de enfriamiento); +15 % de poder de
           # ataque (aura 166). El requisito «solo mientras estás enfurecido» lo impone el
           # estado de aura 17 (CasterAuraState), que aplican Enfurecer, Ira rabiosa e Ira
           # sangrienta, igual que en Regeneración iracunda.
            "id": 426940, "client": True, "template": 774,
            "skill_line": SKILL_FURY,
            "name": "Rampage",
            "desc": "Go on a rampage, increasing your attack power by $s1% for $d. This "
                    "ability can only be used while Enraged.",
            "overrides": {
                "Attributes": 0,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][30000],
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 1, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 90000, "CategoryRecoveryTime": 0, "CasterAuraState": 17,
                "SpellClassSet": 4, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": idx["icon"]["ability_warrior_rampage"],
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_ATTACK_POWER_PCT,
                "EffectBasePoints_1": 15, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Escudo y espada: pasiva; el aura 42 dispara la marca 426979 cuando Devastar
           # (palabra B 0x40) o Revancha (palabra A 0x400) infligen daño, con el 30 % de
           # probabilidad del hechizo. El script del core spell_warr_sword_and_board reinicia
           # el enfriamiento de Embate con escudo; el filtro de proc se copia de -46951.
            "id": 426978, "client": True, "template": 46951,
            "skill_line": SKILL_PROTECTION,
            "name": "Sword and Board", "script": "spell_warr_sword_and_board",
            "inherit_server": True,
            "desc": "When your Devastate and Revenge abilities deal damage they have a $h% "
                    "chance of refreshing the cooldown of your Shield Slam ability and "
                    "reducing its Rage cost by $426979s1% for $426979d.",
            "overrides": {
                "SpellLevel": 0, "ProcChance": 30,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 426979, "EffectMiscValue_1": 0,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
            },
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 4,
                "SpellFamilyMask0": 1024, "SpellFamilyMask1": 64, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Marca de Escudo y espada: clon del beneficio de WotLK 50227 (aura 108 + SpellModOp
           # 14 sobre Embate con escudo, −100 % de coste de ira) durante 5 s.
            "id": 426979, "client": True, "template": 50227,
            "name": "Sword and Board", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
        # Auxiliares de servidor (client: False): filas sólo en spell_dbc. Celeridad de Asalto
        # frenético, aplicada por el script mientras el guerrero empuñe un arma a dos manos.
        {"id": 900052, "client": False, "template": None, "name": "Frenzied Assault",
         "overrides": {
             "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
             "DurationIndex": duration_perm, "RangeIndex": range_self,
             "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
             "SpellClassSet": 4, "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
             "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MELEE_HASTE,
             "EffectBasePoints_1": 40, "EffectDieSides_1": 0,
             "ImplicitTargetA_1": TARGET_UNIT_CASTER,
             "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
             "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
         }},
        # Bono de Actitud de gladiador mientras se empuña un escudo: +10 % de daño (todas las
        # escuelas), +10 % de bloqueo y el aura 275 con todas las máscaras (deja usar las
        # facultades restringidas a otras actitudes).
        {"id": 900053, "client": False, "template": None, "name": "Gladiator Stance Shield",
         "overrides": {
             "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
             "DurationIndex": duration_perm, "RangeIndex": range_self,
             "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
             "SpellClassSet": 4, "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
             "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_DAMAGE_PERCENT_DONE,
             "EffectBasePoints_1": 10, "EffectDieSides_1": 0, "EffectMiscValue_1": 127,
             "ImplicitTargetA_1": TARGET_UNIT_CASTER,
             "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_BLOCK_PERCENT,
             "EffectBasePoints_2": 10, "EffectDieSides_2": 0,
             "ImplicitTargetA_2": TARGET_UNIT_CASTER,
             "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": AURA_MOD_IGNORE_SHAPESHIFT,
             "EffectBasePoints_3": 0, "EffectDieSides_3": 0,
             "EffectSpellClassMaskA_3": MASK_ALL_SPELLS,
             "EffectSpellClassMaskB_3": MASK_ALL_SPELLS,
             "EffectSpellClassMaskC_3": MASK_ALL_SPELLS,
             "ImplicitTargetA_3": TARGET_UNIT_CASTER,
         }},
        # Penalización de Actitud de gladiador: −30 % de armadura (aura 101, escuela física) y
        # −30 % de amenaza (aura 10, todas las escuelas), mientras la actitud esté activa.
        {"id": 900054, "client": False, "template": None, "name": "Gladiator Stance Penalty",
         "overrides": {
             "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
             "DurationIndex": duration_perm, "RangeIndex": range_self,
             "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
             "SpellClassSet": 4, "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
             "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_RESISTANCE_PCT,
             "EffectBasePoints_1": -30, "EffectDieSides_1": 0, "EffectMiscValue_1": 1,
             "ImplicitTargetA_1": TARGET_UNIT_CASTER,
             "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": AURA_MOD_THREAT,
             "EffectBasePoints_2": -30, "EffectDieSides_2": 0, "EffectMiscValue_2": 127,
             "ImplicitTargetA_2": TARGET_UNIT_CASTER,
             "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
         }},
        # Bono de Maestría con escudos mientras se empuña un escudo: +9 % al daño físico
        # (aura 79 de escuela física), renovado por el sondeo de 2 s del marcador 426980.
        {"id": 900055, "client": False, "template": None, "name": "Shield Mastery",
         "overrides": {
             "Attributes": SPELL_ATTR0_PASSIVE | SPELL_ATTR0_DO_NOT_DISPLAY,
             "DurationIndex": idx["dur"][3000], "RangeIndex": range_self,
             "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0, "SpellLevel": 0,
             "SpellClassSet": 4, "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
             "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": AURA_MOD_DAMAGE_PERCENT_DONE,
             "EffectBasePoints_1": 9, "EffectDieSides_1": 0, "EffectMiscValue_1": 1,
             "ImplicitTargetA_1": TARGET_UNIT_CASTER,
             "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
             "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
         }},
    ]
