-- mod-sod-content: Priest rune definitions.
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
    (7005001, 401946, 16, 64, ''Circle of Healing'', ''spell_holy_circleofrenewal'',
     ''Heals all of the target player''''s party members around the target player.'',
     ''mod-sod-priest'', 1),
    (7005002, 402174, 16, 64, ''Penance'', ''spell_holy_penance'',
     ''Launches a volley of holy light at the target, damaging an enemy or healing an ally.'',
     ''mod-sod-priest'', 1)
 ON DUPLICATE KEY UPDATE
    `spell_id`    = VALUES(`spell_id`),
    `class_mask`  = VALUES(`class_mask`),
    `slot_mask`   = VALUES(`slot_mask`),
    `name`        = VALUES(`name`),
    `icon`        = VALUES(`icon`),
    `description` = VALUES(`description`),
    `source`      = VALUES(`source`),
    `enabled`     = VALUES(`enabled`)',
'DO 0');

PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
