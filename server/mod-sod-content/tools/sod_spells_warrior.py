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
SPELLMOD_THREAT = 2                   # SpellModOp 2 de 3.3.5a: amenaza
SPELLMOD_EFFECT1 = 3                  # SpellModOp 3: valor del efecto 1 (daño)
SPELLMOD_EFFECT2 = 12                 # SpellModOp 12: valor del efecto 2 (ralentización de Atronar)
SPELLMOD_DOT = 22                     # SpellModOp 22 de 3.3.5a: daño periódico

EFFECT_PULL_TOWARDS = 124             # arrastra al objetivo hacia el lanzador
EFFECT_WEAPON_PERCENT_DAMAGE = 31

# Máscara de familia de Atronar (SpellClassMask_1 0x80) y de Golpe heroico (0x40).
MASK_THUNDER_CLAP = 0x80
MASK_HEROIC_STRIKE = 0x40

# Ataques cuerpo a cuerpo con éxito: automáticos y facultades de escuela física.
PROC_MELEE_HITS = 0x400014

# Máscaras de familia de WotLK (SpellClassSet 4) de los hechizos nativos que se modifican.
MASK_REND = 0x20
MASK_CHARGE = 0x1
MASK_INTERCEPT = 0x40000000
MASK_INTERVENE = 0x10000


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
    ]
