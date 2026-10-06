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
