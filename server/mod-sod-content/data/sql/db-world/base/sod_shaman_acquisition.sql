-- mod-sod-shaman: adquisición de objetos de runa adaptada a WotLK.
-- Los Rune Brokers venden estas runas; el Grabador local hace de sustituto por 1 oro.
-- Lava Lash no tiene objeto asignado en las fuentes consultadas. Las demás fuentes de SoD
-- que dependen de NPC ausentes se documentan en docs/runas/obtencion.md.

REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`)
VALUES
    (210746, 15, 0, 'Rune of Earth Shield', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (206387, 15, 0, 'Kajaric Icon', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (221490, 15, 0, 'Rune of Riptide', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (225914, 15, 0, 'Rune of the Bound Spirit', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (213086, 15, 0, 'Rune of the Storm', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (220612, 15, 0, 'Rune of Tidal Waves', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (212560, 15, 0, 'Rune of Ancestral Awakening', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (210823, 15, 0, 'Rune of Dual Wield Specialization', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (206381, 15, 0, 'Dyadic Icon', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (206386, 15, 0, 'Galvanic Icon', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (216606, 15, 0, 'Rune of Two-Handed Mastery', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (211391, 15, 0, 'Rune of Healing Rain', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (210589, 15, 0, 'Echo of the Ancestors', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (210811, 15, 0, 'Rune of Primordial Fury', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (208758, 15, 0, 'Earthen Rune', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (206388, 15, 0, 'Sulfurous Icon', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (213093, 15, 0, 'Rune of Power', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (213096, 15, 0, 'Rune of Decoys', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (213092, 15, 0, 'Rune of the Alpha', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (221483, 15, 0, 'Rune of Burn', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (220610, 15, 0, 'Rune of Mental Dexterity', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (220616, 15, 0, 'Rune of Overcharged', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (220613, 15, 0, 'Rune of Rolling Thunder', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (220614, 15, 0, 'Rune of Static Shock', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (225740, 15, 0, 'Rune of Composure', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.'),
    (225838, 15, 0, 'Voltaic Icon', 1102, 2, 0, 1, 10000, 0, 0, 64, -1, 60, 1, 1, 1, 1, 1, 0, 55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.');

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (210746, 'esES', 'Runa de Escudo de tierra', 'Te enseña una nueva facultad de grabado.', 0),
    (206387, 'esES', 'Runa de Ráfaga de lava', 'Te enseña una nueva facultad de grabado.', 0),
    (221490, 'esES', 'Runa de Mareas vivas', 'Te enseña una nueva facultad de grabado.', 0),
    (225914, 'esES', 'Runa de Espíritu feral', 'Te enseña una nueva facultad de grabado.', 0),
    (213086, 'esES', 'Runa de Arma vorágine', 'Te enseña una nueva facultad de grabado.', 0),
    (220612, 'esES', 'Runa de Maremotos', 'Te enseña una nueva facultad de grabado.', 0),
    (212560, 'esES', 'Runa de Despertar ancestral', 'Te enseña una nueva facultad de grabado.', 0),
    (210823, 'esES', 'Runa de Especialización en doble empuñadura', 'Te enseña una nueva facultad de grabado.', 0),
    (206381, 'esES', 'Runa de Sobrecarga', 'Te enseña una nueva facultad de grabado.', 0),
    (206386, 'esES', 'Runa de Maestría con escudos', 'Te enseña una nueva facultad de grabado.', 0),
    (216606, 'esES', 'Runa de Maestría con arma a dos manos', 'Te enseña una nueva facultad de grabado.', 0),
    (211391, 'esES', 'Runa de Lluvia de sanación', 'Te enseña una nueva facultad de grabado.', 0),
    (210589, 'esES', 'Runa de Guía ancestral', 'Te enseña una nueva facultad de grabado.', 0),
    (210811, 'esES', 'Runa de Lobo fantasmal superior', 'Te enseña una nueva facultad de grabado.', 0),
    (208758, 'esES', 'Runa de Camino de la tierra', 'Te enseña una nueva facultad de grabado.', 0),
    (206388, 'esES', 'Runa de Explosión de arrabio', 'Te enseña una nueva facultad de grabado.', 0),
    (213093, 'esES', 'Runa de Oleada de poder', 'Te enseña una nueva facultad de grabado.', 0),
    (213096, 'esES', 'Runa de Tótem señuelo', 'Te enseña una nueva facultad de grabado.', 0),
    (213092, 'esES', 'Runa de Espíritu del alfa', 'Te enseña una nueva facultad de grabado.', 0),
    (221483, 'esES', 'Runa de Quemar', 'Te enseña una nueva facultad de grabado.', 0),
    (220610, 'esES', 'Runa de Maña mental', 'Te enseña una nueva facultad de grabado.', 0),
    (220616, 'esES', 'Runa de Sobrecargado', 'Te enseña una nueva facultad de grabado.', 0),
    (220613, 'esES', 'Runa de Trueno ondulante', 'Te enseña una nueva facultad de grabado.', 0),
    (220614, 'esES', 'Runa de Choque estático', 'Te enseña una nueva facultad de grabado.', 0),
    (225740, 'esES', 'Runa de Coherencia', 'Te enseña una nueva facultad de grabado.', 0),
    (225838, 'esES', 'Runa de Tormenta, Tierra y Fuego', 'Te enseña una nueva facultad de grabado.', 0);

REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (700000, 0, 210746, 0, 0, 0),
    (700000, 0, 206387, 0, 0, 0),
    (700000, 0, 221490, 0, 0, 0),
    (700000, 0, 225914, 0, 0, 0),
    (700000, 0, 213086, 0, 0, 0),
    (700000, 0, 220612, 0, 0, 0),
    (700000, 0, 212560, 0, 0, 0),
    (700000, 0, 210823, 0, 0, 0),
    (700000, 0, 206381, 0, 0, 0),
    (700000, 0, 206386, 0, 0, 0),
    (700000, 0, 216606, 0, 0, 0),
    (700000, 0, 211391, 0, 0, 0),
    (700000, 0, 210589, 0, 0, 0),
    (700000, 0, 210811, 0, 0, 0),
    (700000, 0, 208758, 0, 0, 0),
    (700000, 0, 206388, 0, 0, 0),
    (700000, 0, 213093, 0, 0, 0),
    (700000, 0, 213096, 0, 0, 0),
    (700000, 0, 213092, 0, 0, 0),
    (700000, 0, 221483, 0, 0, 0),
    (700000, 0, 220610, 0, 0, 0),
    (700000, 0, 220616, 0, 0, 0),
    (700000, 0, 220613, 0, 0, 0),
    (700000, 0, 220614, 0, 0, 0),
    (700000, 0, 225740, 0, 0, 0),
    (700000, 0, 225838, 0, 0, 0);

REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (2953, 206381, 0, 4.8222, 0, 1, 0, 1, 1, 'mod-sod-shaman: runa Sobrecarga'),
    (3124, 206381, 0, 0.9567, 0, 1, 0, 1, 1, 'mod-sod-shaman: runa Sobrecarga'),
    (2373, 206387, 0, 33.3333, 0, 1, 0, 1, 1, 'mod-sod-shaman: runa Ráfaga de lava'),
    (7158, 225838, 0, 0.0864, 0, 1, 0, 1, 1, 'mod-sod-shaman: runa Tormenta, Tierra y Fuego');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 2953, 206381, 0, 0, 15, 0, 64, 0, 0, 0, 'mod-sod-shaman: botín exclusivo para chamanes'),
    (1, 3124, 206381, 0, 0, 15, 0, 64, 0, 0, 0, 'mod-sod-shaman: botín exclusivo para chamanes'),
    (1, 2373, 206387, 0, 0, 15, 0, 64, 0, 0, 0, 'mod-sod-shaman: botín exclusivo para chamanes'),
    (1, 7158, 225838, 0, 0, 15, 0, 64, 0, 0, 0, 'mod-sod-shaman: botín exclusivo para chamanes');

SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables
                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (210746, 7007001), (206387, 7007003), (221490, 7007004), (225914, 7007005), (213086, 7007006), (220612, 7007007), (212560, 7007008), (210823, 7007009), (206381, 7007010), (206386, 7007011), (216606, 7007012), (211391, 7007013), (210589, 7007014), (210811, 7007015), (208758, 7007016), (206388, 7007017), (213093, 7007018), (213096, 7007019), (213092, 7007020), (221483, 7007021), (220610, 7007022), (220616, 7007023), (220613, 7007024), (220614, 7007025), (225740, 7007026), (225838, 7007027) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
