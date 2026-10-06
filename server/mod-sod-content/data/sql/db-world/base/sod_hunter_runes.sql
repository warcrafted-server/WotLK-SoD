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
