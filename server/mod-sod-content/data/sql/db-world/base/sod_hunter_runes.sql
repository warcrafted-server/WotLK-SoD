-- mod-sod-content: Hunter rune definitions.
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
    (7003001, 409433, 4, 64, ''Chimera Shot'', ''ability_hunter_chimerashot2'',
    ''You deal weapon damage, refreshing the current Sting on your target and triggering an effect.'',
    ''mod-sod-hunter'', 1),
    (7003002, 409428, 4, 16, ''Master Marksman'', ''ability_hunter_mastermarksman'',
    ''Increases your critical strike chance by 5%, and reduces the Mana cost of all your Shot abilities by 25%.'',
    ''mod-sod-hunter'', 1),
    (7003003, 409552, 4, 64, ''Explosive Shot'', ''ability_hunter_explosiveshot'',
     ''Fires an explosive charge that deals Fire damage to nearby enemies, repeating every second for 2 seconds.'',
     ''mod-sod-hunter'', 1),
    (7003004, 409368, 4, 16, ''Beast Mastery'', ''ability_hunter_beastmastery'',
     ''Your pet's damage and health are increased by 15%, and its Focus regeneration by 50%. In addition, your pet's Growl now also Taunts the target to attack it.'',
     ''mod-sod-hunter'', 1),
    (7003005, 425713, 4, 16, ''Cobra Strikes'', ''ability_hunter_cobrastrikes'',
     ''Your critical hits with Shot and Strike abilities and with Mongoose Bite cause your pet's next 2 special attacks to critically hit.'',
     ''mod-sod-hunter'', 1),
    (7003006, 415370, 4, 16, ''Lone Wolf'', ''ability_hunter_pet_wolf'',
     ''You deal 25% increased damage with all attacks while you do not have an active pet.'',
     ''mod-sod-hunter'', 1),
    (7003007, 415320, 4, 256, ''Flanking Strike'', ''ability_hunter_swiftstrike'',
     ''You and your pet deal simultaneous instant 100% melee damage. Afterward, you deal 8% increased damage for 10 sec, stacking up to 5 times. Your pet's Basic attacks have a 50% chance to reset the cooldown on Flanking Strike.'',
     ''mod-sod-hunter'', 1),
    (7003008, 409593, 4, 256, ''Kill Shot'', ''ability_hunter_assassinate2'',
     ''You attempt to finish off a wounded target with a ranged attack that has no minimum range. Kill Shot's cooldown is reset if used on an enemy that has 20% or less health.'',
     ''mod-sod-hunter'', 1)
 ON DUPLICATE KEY UPDATE
    `spell_id`    = VALUES(`spell_id`),
    `class_mask`  = VALUES(`class_mask`),
    `slot_mask`   = VALUES(`slot_mask`),
    `name`        = VALUES(`name`),
    `icon`        = VALUES(`icon`),
    `description` = VALUES(`description`),
    `source`      = VALUES(`source`),
    `enabled`     = VALUES(`enabled`)','DO 0');

PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Scripts propios sobre hechizos de SoD de esta tanda. El emisor (sod-client) también escribe
-- las filas de 425713, 415370 y 409593; aquí quedan para que el módulo sea autosuficiente.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (425713, 'spell_hun_cobra_strikes'),
    (415370, 'spell_sod_hunter_lone_wolf'),
    (409593, 'spell_sod_hunter_kill_shot');

-- Bestialidad hace que el Bramido de la mascota provoque al objetivo (id negativo = todos los
-- rangos de 2649).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-2649, 'spell_sod_hunter_beast_mastery_growl');

-- Aura de mascota de Bestialidad: el familiar la recibe al tener la runa (spell_pet_auras es
-- tabla base del core). No se toca ninguna fila de Blizzard: sólo se inserta la nuestra.
DELETE FROM `spell_pet_auras` WHERE `spell` IN (409368);
INSERT INTO `spell_pet_auras` (`spell`, `effectId`, `pet`, `aura`) VALUES
    (409368, 0, 0, 900056);
