-- mod-sod-content: Warrior rune definitions (SoD phase 1).
-- The rune engine is optional, so this file is a no-op when its table is absent.

SET @rune_tbl := (
    SELECT COUNT(*)
    FROM information_schema.tables
    WHERE table_schema = DATABASE()
      AND table_name = 'rune_template'
);

SET @sql := IF(@rune_tbl > 0,
'INSERT INTO `rune_template`
    (`rune_id`, `spell_id`, `class_mask`, `slot_mask`, `name`, `icon`, `description`, `source`, `enabled`)
 VALUES
    (7001001, 403195, 1, 64, ''Devastate'', ''inv_sword_11'',
     ''While you are in Defensive Stance and have a shield equipped, Sunder Armor also deals damage. Devastate damage deals a high amount of threat while you are in Defensive Stance.'',
     ''mod-sod-warrior'', 1),
    (7001002, 412507, 1, 16, ''Blood Frenzy'', ''ability_warrior_bloodfrenzy'',
     ''Rend can now be used in Berserker stance, Rend's damage is increased by 100%, and Rend deals additional damage equal to 4% of your Attack Power each time it deals damage.'',
     ''mod-sod-warrior'', 1),
    (7001003, 402877, 1, 16, ''Flagellation'', ''ability_warrior_bloodbath'',
     ''You gain Rage from Physical damage taken as if you were wearing no armor.'',
     ''mod-sod-warrior'', 1),
    (7001004, 402911, 1, 16, ''Raging Blow'', ''ability_warrior_savageblow'',
     ''A ferocious strike that deals 115% weapon damage, but can only be used while Enrage, Berserker Rage, or Bloodrage is active. Each other melee ability used while Enrage, Berserker Rage, or Bloodrage is active reduces Raging Blow's remaining cooldown by 1 sec.'',
     ''mod-sod-warrior'', 1),
    (7001005, 425421, 1, 16, ''Warbringer'', ''ability_warrior_warbringer'',
     ''Your Charge, Intercept, and Intervene abilities are now usable while in combat and in any stance, and will all remove movement impairing effects when activated.'',
     ''mod-sod-warrior'', 1),
    (7001006, 403215, 1, 256, ''Commanding Shout'', ''ability_warrior_commandingshout'',
     ''The warrior shouts, increasing the Stamina of all party members within 30 yards. Lasts 5 min.'',
     ''mod-sod-warrior'', 1),
    (7001007, 425418, 1, 256, ''Consumed By Rage'', ''ability_warrior_intensifyrage'',
     ''Enrages you for 12 sec after you exceed 60 Rage, allowing abilities that require being Enraged. In addition, Whirlwind also strikes with off-hand melee weapons while you are Enraged.'',
     ''mod-sod-warrior'', 1),
    (7001008, 425412, 1, 256, ''Frenzied Assault'', ''ability_warrior_unrelentingassault'',
     ''While wielding 2-handed weapons, your attack speed is increased by 40% and your successful melee hits generate 2 additional Rage, or 4 additional Rage if they are critical hits.'',
     ''mod-sod-warrior'', 1),
    (7001009, 403219, 1, 256, ''Furious Thunder'', ''ability_thunderclap'',
     ''Thunder Clap now increases the time between attacks by an additional 6%, can be used in any stance, and deals 100% increased damage.'',
     ''mod-sod-warrior'', 1),
    (7001010, 403228, 1, 256, ''Meathook'', ''inv_misc_hook_01'',
     ''Throw out a hooked chain to restrain the target and pull them toward you. May not be used on enemies higher than your level by more than 1, or which are marked as boss enemies.'',
     ''mod-sod-warrior'', 1),
    (7001011, 429765, 1, 64, ''Quick Strike'', ''ability_warrior_decisivestrike'',
     ''A reckless instant melee attack with your two-handed weapon dealing damage based on your Attack Power. This ability benefits from and triggers all effects associated with Heroic Strike.'',
     ''mod-sod-warrior'', 1),
    (7001012, 413404, 1, 64, ''Single-Minded Fury'', ''ability_dualwield'',
     ''While dual-wielding, your movement speed is increased by 10% and you gain 4% attack speed each time your melee auto-attack strikes the same target as your previous auto-attack, stacking up to 5 times. Lasts 10 sec or until your auto-attack strikes a different target.'',
     ''mod-sod-warrior'', 1),
    (7001013, 402927, 1, 64, ''Victory Rush'', ''ability_warrior_devastate'',
     ''Instantly attack the target causing damage based on your Attack Power and healing you for 30% of your maximum health. Only useable within 20 sec after you kill an enemy that yields experience or honor.'',
     ''mod-sod-warrior'', 1),
    (7001014, 413380, 1, 128, ''Blood Surge'', ''ability_warrior_bloodsurge'',
     ''Heroic Strike, Bloodthirst, and Whirlwind have a 30% chance to make your next Slam within 15 sec instant and cost no Rage.'',
     ''mod-sod-warrior'', 1),
    (7001015, 413405, 1, 128, ''Focused Rage'', ''ability_warrior_focusedrage'',
     ''Reduces the rage cost of your offensive abilities by 3.'',
     ''mod-sod-warrior'', 1),
    (7001016, 402922, 1, 128, ''Precise Timing'', ''ability_warrior_decisivestrike'',
     ''Slam is now instant but has a 6 sec cooldown.'',
     ''mod-sod-warrior'', 1),
    (7001017, 402913, 1, 512, ''Enraged Regeneration'', ''ability_warrior_focusedrage'',
     ''Heals you for 3% of your maximum health over 10 sec, but can only be used while Enrage, Berserker Rage, or Bloodrage is active. Useable while Stunned.'',
     ''mod-sod-warrior'', 1),
    (7001018, 412513, 1, 512, ''Gladiator Stance'', ''ability_warrior_offensivestance'',
     ''An aggressive stance: while you are wearing a shield it increases your damage by 10% and your block chance by 10%, but it reduces your armor by 30% and the threat you generate by 30%. While wearing a shield in Gladiator Stance you may use all abilities that are restricted to other stances.'',
     ''mod-sod-warrior'', 1),
    (7001019, 403338, 1, 512, ''Intervene'', ''ability_warrior_intervene'',
     ''Run at high speed towards a party member, intercepting the next melee or ranged attack made against them, and reducing their total threat.'',
     ''mod-sod-warrior'', 1),
    (7001020, 426490, 1, 512, ''Rallying Cry'', ''ability_warrior_rallyingcry'',
     ''Let loose a rallying cry, granting all party and raid members within 40 yards 15% increased maximum health for 10 sec.'',
     ''mod-sod-warrior'', 1),
    (7001021, 403218, 1, 1, ''Endless Rage'', ''ability_warrior_endlessrage'',
     ''You generate 25% more Rage from all damage you deal.'',
     ''mod-sod-warrior'', 1),
    (7001022, 426980, 1, 1, ''Shield Mastery'', ''ability_warrior_shieldmastery'',
     ''Increases all physical damage you deal by 9% while you have a shield equipped, and reduces the duration of all Disarm effects used against you by 51%. This does not stack with other Disarm duration reducing effects.'',
     ''mod-sod-warrior'', 1),
    (7001023, 426953, 1, 1, ''Taste for Blood'', ''ability_rogue_hungerforblood'',
     ''Whenever your Rend ability causes damage, your Overpower ability will activate for 9 sec or 1 attack. This effect will not occur more than once every 6 sec.'',
     ''mod-sod-warrior'', 1),
    (7001024, 426972, 1, 1, ''Vigilance'', ''ability_warrior_vigilance'',
     ''Focus your protective gaze on a party or raid member, reducing their damage taken by 3% and transferring 10% of the threat they cause to you. In addition, each time they are hit by an attack your Taunt cooldown is refreshed. Lasts 30 min. This effect can only be on one target at a time.'',
     ''mod-sod-warrior'', 1),
    (7001025, 426940, 1, 32, ''Rampage'', ''ability_warrior_rampage'',
     ''Go on a rampage, increasing your attack power by 15% for 30 sec. This ability can only be used while Enraged.'',
     ''mod-sod-warrior'', 1),
    (7001026, 426978, 1, 32, ''Sword and Board'', ''ability_warrior_swordandboard'',
     ''When your Devastate and Revenge abilities deal damage they have a 30% chance of refreshing the cooldown of your Shield Slam ability and reducing its Rage cost by 100% for 5 sec.'',
     ''mod-sod-warrior'', 1),
    (7001027, 427065, 1, 32, ''Wrecking Crew'', ''ability_warrior_trauma'',
     ''Your melee critical hits Enrage you (activating abilities which require being Enraged), and increase Mortal Strike, Bloodthirst, and Shield Slam damage by 10% for 12 sec.'',
     ''mod-sod-warrior'', 1),
    (7001028, 440484, 1, 8, ''Fresh Meat'', ''spell_deathknight_butcher'',
     ''Damaging a target with Bloodthirst, Mortal Strike, or Shield Slam has a 100% chance the first time and a 10% chance each subsequent time to Enrage you (activating abilities which requiring being Enraged), and cause you to deal 10% increased Physical damage for 12 sec.'',
     ''mod-sod-warrior'', 1),
    (7001029, 440488, 1, 8, ''Shockwave'', ''ability_warrior_shockwave'',
     ''Sends a wave of force in front of the warrior, causing damage equal to 50% of your Attack Power and stunning all enemy targets within 10 yards in a frontal cone for 4 sec.'',
     ''mod-sod-warrior'', 1),
    (7001030, 440113, 1, 8, ''Sudden Death'', ''ability_warrior_improveddisciplines'',
     ''Your melee hits have a 10% chance to grant Sudden Death. Sudden Death allows one use of Execute regardless of the target''s health state. When Execute is enabled by Sudden Death, you will retain 10 rage after using Execute.'',
     ''mod-sod-warrior'', 1)
 ON DUPLICATE KEY UPDATE
    `spell_id`    = VALUES(`spell_id`),
    `class_mask`  = VALUES(`class_mask`),
    `slot_mask`   = VALUES(`slot_mask`),
    `name`        = VALUES(`name`),
    `icon`        = VALUES(`icon`),
    `description` = VALUES(`description`),
    `source`      = VALUES(`source`),
    `enabled`     = VALUES(`enabled`)'
,'DO 0');

PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Scripts sobre hechizos nativos de WotLK: los ids negativos enlazan todas las filas de rango.
-- Frenesí sangriento engancha Desgarrar (primer rango 772) para añadir el daño por poder de ataque.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (-772, 'spell_sod_warrior_blood_frenzy');

-- Belisario quita los efectos de reducción de movimiento al activar Cargar (100),
-- Interceptar e Intervenir (3411). Interceptar se enlaza rango a rango para no depender
-- de cuál sea su primer rango.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-100, 'spell_sod_warrior_warbringer'),
    (20252, 'spell_sod_warrior_warbringer'),
    (20616, 'spell_sod_warrior_warbringer'),
    (20617, 'spell_sod_warrior_warbringer'),
    (25272, 'spell_sod_warrior_warbringer'),
    (25275, 'spell_sod_warrior_warbringer'),
    (3411, 'spell_sod_warrior_warbringer');

-- Arremetida enfurecida usa su propio script de requisitos (el emisor también lo escribe).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (402911, 'spell_sod_warrior_raging_blow');

-- Golpe rápido activa los efectos asociados a Golpe heroico reutilizando su script del core.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (429765, 'spell_warr_heroic_strike');

-- Maestría con escudos usa su propio script; Vigilancia y Escudo y espada reutilizan los
-- scripts del core (el emisor también escribe estas filas).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (426980, 'spell_sod_warrior_shield_mastery'),
    (426972, 'spell_warr_vigilance'),
    (426978, 'spell_warr_sword_and_board');

-- Sexta tanda: Equipo de demolición engancha su beneficio; Carne fresca y Ola de choque, su
-- script propio. Muerte súbita no necesita C++ (el aura 42 y el script de Ejecutar del core
-- bastan).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (427066, 'spell_sod_warrior_wrecking_crew'),
    (440484, 'spell_sod_warrior_fresh_meat'),
    (440488, 'spell_sod_warrior_shockwave');
