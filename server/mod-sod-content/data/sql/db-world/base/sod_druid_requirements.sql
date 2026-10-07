-- Druid idol-use requirements. This file is a no-op without the rune engine.
SET @requirement_tbl := (
    SELECT COUNT(*)
    FROM information_schema.tables
    WHERE table_schema = DATABASE()
      AND table_name = 'rune_item_requirement'
);

SET @sql := IF(@requirement_tbl > 0,
'REPLACE INTO `rune_item_requirement`
    (`item_id`, `req_key`, `param1`, `param2`, `target_count`, `text_id`)
 VALUES
    (210534, ''druid_heal_beasts'', 0, 0, 10, 5000),
    (208689, ''druid_bleed_humanoids'', 0, 0, 20, 5001),
    (206954, ''druid_bear_rage_streak'', 0, 0, 60, 5002),
    (220915, ''druid_barkskin_nature_kill'', 0, 0, 5, 5003),
    (227444, ''druid_cat_sleeping_kill'', 0, 0, 5, 5004)',
'DO 0');

PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
