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
