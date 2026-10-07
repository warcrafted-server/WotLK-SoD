-- Per-character progress for rune item requirements.
CREATE TABLE IF NOT EXISTS `character_rune_progress` (
    `guid`     INT UNSIGNED NOT NULL,
    `item_id`  INT UNSIGNED NOT NULL,
    `progress` INT UNSIGNED NOT NULL,
    PRIMARY KEY (`guid`, `item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
