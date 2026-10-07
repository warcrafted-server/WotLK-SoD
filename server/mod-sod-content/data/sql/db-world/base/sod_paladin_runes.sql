-- mod-sod-content: Paladin rune definitions (SoD phase 1).
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
    (7002001, 407778, 2, 16, ''Divine Storm'', ''ability_paladin_divinestorm'',
     ''An instant weapon attack that damages nearby enemies. It also heals party or raid members for part of the damage caused.'',
     ''mod-sod-paladin'', 1),
    (7002002, 407669, 2, 256, ''Avenger''''s Shield'', ''spell_holy_avengersshield'',
     ''Hurls a holy shield at an enemy, dealing Holy damage, dazing them, then jumping to nearby enemies.'',
     ''mod-sod-paladin'', 1),
    (7002003, 407624, 2, 256, ''Aura Mastery'', ''spell_holy_auramastery'',
     ''Causes your Concentration Aura to make affected targets immune to Silence and Interrupt effects, and improves the effect of your other auras.'',
     ''mod-sod-paladin'', 1),
    (7002004, 407676, 2, 64, ''Crusader Strike'', ''spell_holy_crusaderstrike'',
     ''An instant strike that causes weapon damage as Holy and regenerates mana. It refreshes the duration of all Judgement effects on the target.'',
     ''mod-sod-paladin'', 1)
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
