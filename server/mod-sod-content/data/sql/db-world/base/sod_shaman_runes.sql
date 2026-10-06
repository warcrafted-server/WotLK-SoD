-- mod-sod-content: Shaman rune definitions.
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
    (7007001, 408514, 64, 256, ''Earth Shield'', ''spell_nature_skinofearth'',
     ''Protects the target with an earthen shield. Earth Shield can only be placed on one target at a time.'',
     ''mod-sod-shaman'', 1),
    (7007002, 408507, 64, 64, ''Lava Lash'', ''ability_shaman_lavalash'',
     ''You charge your off-hand weapon with lava, instantly dealing off-hand weapon damage. Damage is increased if your off-hand weapon is enchanted with Flametongue.'',
     ''mod-sod-shaman'', 1)
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
