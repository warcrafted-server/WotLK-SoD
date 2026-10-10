-- mod-sod-druid: WotLK-supported item acquisition for SoD runes.
-- Real Rune Brokers sell these items throughout the capitals and starting zones;
-- the summoned Rune Engraver is the local substitute. Broker-only vendor stock uses 10000 copper
-- because this core has no per-vendor price hook. Grizzby's recorded coin cost overrides ItemSparse.

REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`)
VALUES
    (206963, 15, 0, 'Rune of Natural Potential', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 1, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (206989, 15, 0, 'Rune of the Sun', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 1, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (208414, 15, 0, 'Lunar Idol', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 5, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Defeat 6 creatures affected by your Moonfire, then use to learn a new ability.'),
    (210500, 15, 0, 'Rune of the Stars', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 20, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (212548, 15, 0, 'Rune of Eclipse', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (213120, 15, 0, 'Rune of the Dreamer', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (220360, 15, 0, 'Rune of Efflorescence', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (220754, 15, 0, 'Rune of the Windstorm', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (220915, 15, 0, 'Idol of the Raging Shambler', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Kill 5 enemies with Nature damage while affected by Barkskin. Then, use this idol to learn a new ability.'),
    (221020, 15, 0, 'Rune of the Moon Goddess', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (227746, 15, 0, 'Rune of the World Tree', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 60, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (227749, 15, 0, 'Rune of the Falling Star', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 60, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.');

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (206963, 'esES', 'Runa de Potencial natural', 'Te enseña una nueva facultad de grabado.', 0),
    (206989, 'esES', 'Runa del Sol', 'Te enseña una nueva facultad de grabado.', 0),
    (208414, 'esES', 'Ídolo lunar', 'Derrota a 6 criaturas afectadas por tu Fuego lunar y después usa este ídolo para aprender una nueva facultad.', 0),
    (210500, 'esES', 'Runa de las estrellas', 'Te enseña una nueva facultad de grabado.', 0),
    (212548, 'esES', 'Runa de Eclipse', 'Te enseña una nueva facultad de grabado.', 0),
    (213120, 'esES', 'Runa del soñador', 'Te enseña una nueva facultad de grabado.', 0),
    (220360, 'esES', 'Runa de Floración', 'Te enseña una nueva facultad de grabado.', 0),
    (220754, 'esES', 'Runa de la tormenta de viento', 'Te enseña una nueva facultad de grabado.', 0),
    (220915, 'esES', 'Ídolo de arrastrapiés furibundo', 'Mata a 5 enemigos con daño de Naturaleza mientras estás bajo los efectos de Piel de corteza. Usa este ídolo para aprender una nueva facultad.', 0),
    (221020, 'esES', 'Runa de la diosa de la luna', 'Te enseña una nueva facultad de grabado.', 0),
    (227746, 'esES', 'Runa del Árbol del Mundo', 'Te enseña una nueva facultad de grabado.', 0),
    (227749, 'esES', 'Runa de la estrella fugaz', 'Te enseña una nueva facultad de grabado.', 0);

REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (1989, 208414, 0, 4, 0, 1, 0, 1, 1, 'mod-sod-druid Fury of Stormrage rune'),
    (5465, 220915, 0, 2.5, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Barkskin rune'),
    (5481, 220915, 0, 2.4778, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Barkskin rune'),
    (5485, 220915, 0, 5.272, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Barkskin rune'),
    (5490, 220915, 0, 4.3365, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Barkskin rune'),
    (9396, 220915, 0, 1.4354, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Barkskin rune');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 1989, 208414, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Fury of Stormrage item for class only'),
    (1, 5465, 220915, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Barkskin item for class only'),
    (1, 5481, 220915, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Barkskin item for class only'),
    (1, 5485, 220915, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Barkskin item for class only'),
    (1, 5490, 220915, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Barkskin item for class only'),
    (1, 9396, 220915, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Barkskin item for class only');

REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (700000, 0, 206963, 0, 0, 0),
    (700000, 0, 206989, 0, 0, 0),
    (700000, 0, 208414, 0, 0, 0),
    (700000, 0, 210500, 0, 0, 0),
    (700000, 0, 212548, 0, 0, 0),
    (700000, 0, 213120, 0, 0, 0),
    (700000, 0, 220360, 0, 0, 0),
    (700000, 0, 220754, 0, 0, 0),
    (700000, 0, 220915, 0, 0, 0),
    (700000, 0, 221020, 0, 0, 0),
    (700000, 0, 227746, 0, 0, 0),
    (700000, 0, 227749, 0, 0, 0);

SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables
                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (206963, 7009015), (206989, 7009017), (208414, 7009018), (210500, 7009021), (212548, 7009024), (213120, 7009019), (220360, 7009022), (220754, 7009016), (220915, 7009014), (221020, 7009023), (227746, 7009020), (227749, 7009025) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
