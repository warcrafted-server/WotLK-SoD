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
