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
     ''mod-sod-paladin'', 1),
    (7002005, 426157, 2, 512, ''The Art of War'', ''ability_paladin_artofwar'',
     ''Melee critical strikes reduce Exorcism''''s remaining cooldown and mana cost.'',
     ''mod-sod-paladin'', 1),
    (7002006, 440672, 2, 8, ''Righteous Vengeance'', ''ability_paladin_righteousvengeance'',
     ''Critical Judgements, Crusader Strikes, and Divine Storms deal additional damage over time.'',
     ''mod-sod-paladin'', 1),
    (7002007, 429152, 2, 32, ''Improved Hammer of Wrath'', ''ability_thunderclap'',
     ''Hammer of Wrath becomes instant and can reset its cooldown against weakened enemies.'',
     ''mod-sod-paladin'', 1),
    (7002008, 429144, 2, 32, ''Purifying Power'', ''spell_holy_excorcism'',
     ''Reduces Exorcism and Holy Wrath cooldowns; Holy Wrath damages any enemy and stuns Demons and Undead.'',
     ''mod-sod-paladin'', 1),
    (7002009, 429142, 2, 1, ''Fanaticism'', ''spell_holy_greaterheal'',
     ''Increases Holy spell critical chance and adds healing over time to critical heals.'',
     ''mod-sod-paladin'', 1),
    (7002010, 429139, 2, 1, ''Wrath'', ''ability_paladin_sanctifiedwrath'',
     ''Consecration can critically strike, and listed Holy damage gains critical chance from melee critical chance.'',
     ''mod-sod-paladin'', 1),
    (7002011, 426065, 2, 128, ''Infusion of Light'', ''ability_paladin_infusionoflight'',
     ''Increases Holy Shock damage and healing by 50%, reduces its cooldown to 6 sec, and critical strikes refund its mana cost and reduce its remaining cooldown by 3 sec.'',
     ''mod-sod-paladin'', 1),
    (7002012, 428909, 2, 32, ''Light''''s Grace'', ''spell_holy_lightsgrace'',
     ''Holy Light reduces the cast time of your next Holy Light by 0.5 sec. Lasts 15 sec.'',
     ''mod-sod-paladin'', 1),
    (7002013, 429133, 2, 1, ''Improved Sanctuary'', ''spell_nature_lightningshield'',
     ''Increases damage prevented by Blessing of Sanctuary by 100%, and its damage by 20% of your shield block value.'',
     ''mod-sod-paladin'', 1),
    (7002014, 425589, 2, 16, ''Aegis'', ''ability_defend'',
     ''Increases block value by 30%. Redoubt gains a 10% chance to trigger from attacks received and always triggers on melee critical strikes; Reckoning gains a 2% proc chance per talent point.'',
     ''mod-sod-paladin'', 1),
    (7002015, 426158, 2, 128, ''Sheath of Light'', ''ability_paladin_sheathoflight'',
     ''Dealing damage with your melee weapon increases your spell damage by 30% of your attack power for 1 min.'',
     ''mod-sod-paladin'', 1),
    (7002016, 415059, 2, 512, ''Guarded by the Light'', ''spell_nature_lightningshield'',
     ''Each melee hit grants 5% of maximum mana every 3 sec for 15 sec; healing done is reduced by 50% during the effect.'',
     ''mod-sod-paladin'', 1),
    (7002017, 462834, 2, 8, ''Shock and Awe'', ''ability_paladin_sanctifiedwrath'',
     ''While Righteous Fury is inactive, Holy Shock damage grants spell damage equal to 200% of Intellect and reduces threat by 30% for 1 min.'',
     ''mod-sod-paladin'', 1),
    (7002018, 458287, 2, 16, ''Hallowed Ground'', ''spell_holy_excorcism'',
     ''Consecration also heals party members in its area for 200% of its damage.'',
     ''mod-sod-paladin'', 1),
    (7002019, 407613, 2, 64, ''Beacon of Light'', ''ability_paladin_beaconoflight'',
     ''Healing your party or raid also heals the Beacon target for 75% of the amount healed. Only one target can be the Beacon at a time. Lasts 60 min.'',
     ''mod-sod-paladin'', 1),
    (7002020, 407632, 2, 32, ''Hammer of the Righteous'', ''ability_paladin_hammeroftherighteous'',
     ''Hammers the current target and up to 2 nearby targets, causing 4 times your main hand damage per second as Holy damage.'',
     ''mod-sod-paladin'', 1),
    (7002021, 440658, 2, 8, ''Shield of Righteousness'', ''ability_defend'',
     ''Slams the target with your shield, causing Holy damage based on your block value plus 179.'',
     ''mod-sod-paladin'', 1),
    (7002022, 458856, 2, 8, ''Divine Light'', ''spell_holy_surgeoflight'',
     ''Heals a friendly target. 50% of any excess healing becomes an absorption shield for 15 sec. Multiple casts do not accumulate this shield. Benefits from Holy Light talents and effects.'',
     ''mod-sod-paladin'', 1),
    (7002023, 425609, 2, 256, ''Rebuke'', ''ability_paladin_judgementred'',
     ''Interrupts spellcasting and prevents spells from that school for 3 sec.'',
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
