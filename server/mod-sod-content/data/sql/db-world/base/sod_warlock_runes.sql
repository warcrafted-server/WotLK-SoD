-- mod-sod-content: Warlock rune definitions (SoD phase 1 pilot).
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
    (7008001, 403629, 256, 64, ''Chaos Bolt'', ''ability_warlock_chaosbolt'',
     ''Sends a bolt of chaotic fire at the enemy, dealing Chaos damage.'',
     ''mod-sod-warlock'', 1),
    (7008002, 403501, 256, 64, ''Haunt'', ''ability_warlock_haunt'',
     ''Unleash a ghostly soul on an enemy, dealing damage and increasing all Shadow damage over time you deal to that target.'',
     ''mod-sod-warlock'', 1),
    (7008003, 412727, 256, 16, ''Demonic Tactics'', ''spell_shadow_demonictactics'',
     ''Increases the melee and spell critical strike chance of you and your pet by 10%.'',
     ''mod-sod-warlock'', 1)
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
