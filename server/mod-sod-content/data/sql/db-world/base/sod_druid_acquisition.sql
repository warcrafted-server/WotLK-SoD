-- mod-sod-druid: WotLK-supported item acquisition for SoD runes.
-- Real Rune Brokers sell these items throughout the capitals and starting zones;
-- the summoned Rune Engraver is the local substitute. Broker-only vendor stock uses 10000 copper
-- because this core has no per-vendor price hook. Grizzby's recorded coin cost overrides ItemSparse.
-- Shared WotLK gameobject lootid 3318 for SoD objects 3642, 152608, 152618; one loot row uses the first source rate.

REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`)
VALUES
    (7009026, 15, 0, 'Rune of Lifebloom', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (7009027, 15, 0, 'Rune of Nourish', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.');

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (7009026, 'esES', 'Runa de Flor de vida', 'Te enseña una nueva facultad de grabado.', 0),
    (7009027, 'esES', 'Runa de Nutrir', 'Te enseña una nueva facultad de grabado.', 0);

REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (700000, 0, 7009026, 0, 0, 0),
    (700000, 0, 7009027, 0, 0, 0);

REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`)
VALUES
    (206954, 15, 0, 'Idol of Ursine Rage', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 10, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Learn a new ability after keeping your rage in Bear Form at 50 or higher for 60 seconds'),
    (206992, 15, 0, 'Rune of Skull Bash', 1102, 2, 0, 1, 20000, 0, 0,
     1024, -1, 25, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (208687, 15, 0, 'Rune of Lacerate', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 10, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (208689, 15, 0, 'Ferocious Idol', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 20, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Deal 20 instances of bleeding damage to humanoids, then use this idol to learn a new ability.'),
    (210137, 15, 0, 'Rune of Wild Growth', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 25, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (210534, 15, 0, 'Idol of the Wild', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 25, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Heal 10 different beasts, then use this idol to learn a new ability.'),
    (210817, 15, 0, 'Rune of Survival', 1102, 2, 0, 1, 31578, 0, 0,
     1024, -1, 25, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (213117, 15, 0, 'Rune of Berserk', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (213118, 15, 0, 'Rune of the Jungle King', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (213119, 15, 0, 'Rune of Instinct', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (221516, 15, 0, 'Rune of Primal Energy', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (221517, 15, 0, 'Rune of Bloodshed', 1102, 2, 0, 1, 16000, 0, 0,
     1024, -1, 50, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Teaches you a new Engraving ability.'),
    (227444, 15, 0, 'Idol of the Huntress', 1102, 2, 0, 1, 10000, 0, 0,
     1024, -1, 60, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock',
     'Kill 5 sleeping targets while in Cat Form. Then, use this idol to learn a new ability.');

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (206954, 'esES', 'Ídolo de ira osuna', 'Aprendes una nueva facultad tras mantener tu ira en forma de oso en 50 p. o más durante 60 segundos.', 0),
    (206992, 'esES', 'Runa de Testarazo', 'Te enseña una nueva facultad de grabado.', 0),
    (208687, 'esES', 'Runa de Lacerar', 'Te enseña una nueva facultad de grabado.', 0),
    (208689, 'esES', 'Ídolo de ferocidad', 'Inflige daño de sangrado 20 veces a humanoides y después usa este ídolo para aprender una nueva facultad.', 0),
    (210137, 'esES', 'Runa de Crecimiento salvaje', 'Te enseña una nueva facultad de grabado.', 0),
    (210534, 'esES', 'Ídolo de las fieras', 'Sana 10 bestias diferentes y usa este ídolo para aprender una facultad nueva.', 0),
    (210817, 'esES', 'Runa de supervivencia', 'Te enseña una nueva facultad de grabado.', 0),
    (213117, 'esES', 'Runa de Rabia', 'Te enseña una nueva facultad de grabado.', 0),
    (213118, 'esES', 'Runa del rey de la selva', 'Te enseña una nueva facultad de grabado.', 0),
    (213119, 'esES', 'Runa de instinto', 'Te enseña una nueva facultad de grabado.', 0),
    (221516, 'esES', 'Runa de energía primigenia', 'Te enseña una nueva facultad de grabado.', 0),
    (221517, 'esES', 'Runa de Escabechina', 'Te enseña una nueva facultad de grabado.', 0),
    (227444, 'esES', 'Ídolo de la cazadora', 'Mata a 5 objetivos dormidos en mientras estás forma felina. Después, usa este ídolo para aprender una nueva facultad.', 0);

REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (2960, 206954, 0, 0.5054, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (2964, 206954, 0, 0.1638, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (2965, 206954, 0, 0.1474, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (2971, 206954, 0, 0.6246, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (2979, 206954, 0, 1.2687, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (3232, 206954, 0, 1.4916, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (3566, 206954, 0, 0.3878, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (7318, 206954, 0, 28.7535, 0, 1, 0, 1, 1, 'mod-sod-druid Mangle rune'),
    (117, 208689, 0, 0.3503, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (123, 208689, 0, 0.2155, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (124, 208689, 0, 0.436, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (452, 208689, 0, 0.3433, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (500, 208689, 0, 0.2552, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (1065, 208689, 0, 6.6667, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (1972, 208689, 0, 1.5936, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (6788, 208689, 0, 19.7595, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune'),
    (11910, 210534, 0, 2.2115, 0, 1, 0, 1, 1, 'mod-sod-druid Wild Strikes rune'),
    (11911, 210534, 0, 2.5397, 0, 1, 0, 1, 1, 'mod-sod-druid Wild Strikes rune'),
    (11912, 210534, 0, 1.8458, 0, 1, 0, 1, 1, 'mod-sod-druid Wild Strikes rune'),
    (11913, 210534, 0, 1.7765, 0, 1, 0, 1, 1, 'mod-sod-druid Wild Strikes rune'),
    (6505, 227444, 0, 1.5504, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Swipe rune'),
    (6506, 227444, 0, 1.7032, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Swipe rune'),
    (6507, 227444, 0, 2.2936, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Swipe rune'),
    (6508, 227444, 0, 3.6055, 0, 1, 0, 1, 1, 'mod-sod-druid Improved Swipe rune');

REPLACE INTO `gameobject_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (3318, 208689, 0, 33.3333, 0, 1, 0, 1, 1, 'mod-sod-druid Savage Roar rune');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 2960, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 2964, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 2965, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 2971, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 2979, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 3232, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 3566, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 7318, 206954, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Mangle item for class only'),
    (1, 117, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 123, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 124, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 452, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 500, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 1065, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 1972, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 6788, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only'),
    (1, 11910, 210534, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Wild Strikes item for class only'),
    (1, 11911, 210534, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Wild Strikes item for class only'),
    (1, 11912, 210534, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Wild Strikes item for class only'),
    (1, 11913, 210534, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Wild Strikes item for class only'),
    (1, 6505, 227444, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Swipe item for class only'),
    (1, 6506, 227444, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Swipe item for class only'),
    (1, 6507, 227444, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Swipe item for class only'),
    (1, 6508, 227444, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Improved Swipe item for class only'),
    (4, 3318, 208689, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Savage Roar item for class only');

REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (700000, 0, 206954, 0, 0, 0),
    (700000, 0, 206992, 0, 0, 0),
    (700000, 0, 208687, 0, 0, 0),
    (700000, 0, 208689, 0, 0, 0),
    (700000, 0, 210137, 0, 0, 0),
    (700000, 0, 210534, 0, 0, 0),
    (700000, 0, 210817, 0, 0, 0),
    (700000, 0, 213117, 0, 0, 0),
    (700000, 0, 213118, 0, 0, 0),
    (700000, 0, 213119, 0, 0, 0),
    (700000, 0, 221516, 0, 0, 0),
    (700000, 0, 221517, 0, 0, 0),
    (700000, 0, 227444, 0, 0, 0);

INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (211653, 0, 210817, 0, 0, 0)
ON DUPLICATE KEY UPDATE `maxcount` = VALUES(`maxcount`), `incrtime` = VALUES(`incrtime`), `ExtendedCost` = VALUES(`ExtendedCost`);

SET @supply_tbl := (SELECT COUNT(*) FROM information_schema.tables
                    WHERE table_schema = DATABASE() AND table_name = 'sod_world_supply_vendor');
SET @sql := IF(@supply_tbl > 0,
'INSERT INTO `sod_world_supply_vendor` (`item`, `RequiredRank`) VALUES (206992, 4) ON DUPLICATE KEY UPDATE `RequiredRank` = VALUES(`RequiredRank`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables
                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (206954, 7009007), (206992, 7009011), (208687, 7009003), (208689, 7009004), (210137, 7009001), (210534, 7009009), (210817, 7009002), (213117, 7009005), (213118, 7009010), (213119, 7009006), (221516, 7009012), (221517, 7009008), (227444, 7009013) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (7009026, 7009026), (7009027, 7009027) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
