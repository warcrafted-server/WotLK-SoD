-- Generic use requirements for rune-unlock items. Content modules own the rows.
CREATE TABLE IF NOT EXISTS `rune_item_requirement` (
    `item_id`      INT UNSIGNED NOT NULL,
    `req_key`      VARCHAR(48)  NOT NULL,
    `param1`       INT UNSIGNED NOT NULL DEFAULT 0,
    `param2`       INT UNSIGNED NOT NULL DEFAULT 0,
    `target_count` INT UNSIGNED NOT NULL,
    `text_id`      INT UNSIGNED NOT NULL,
    PRIMARY KEY (`item_id`, `req_key`, `param1`, `param2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
