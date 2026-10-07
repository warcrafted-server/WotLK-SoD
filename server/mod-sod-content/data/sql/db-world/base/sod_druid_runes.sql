-- mod-sod-content: Druid rune definitions across SoD phases.
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
    (7009001, 408120, 1024, 64, ''Wild Growth'', ''ability_druid_flourish'',
    ''Heals all party members of the target player within range. Healing is applied quickly at first and slows as Wild Growth reaches its full duration.'',
    ''mod-sod-druid'', 1),
    (7009002, 411115, 1024, 16, ''Survival of the Fittest'', ''spell_nature_spiritwolf'',
    ''Reduces the chance you''''ll be critically hit by melee attacks by 7% and reduces all damage taken by 10%.'',
    ''mod-sod-druid'', 1),
    (7009003, 414644, 1024, 256, ''Lacerate'', ''ability_druid_lacerate'',
    ''Lacerates the enemy target, making them bleed for ${$<damagepower>*$m1/100*5} damage over $d plus $s2% weapon damage per existing application of Lacerate on the target. Causes a high amount of threat. This effect stacks up to $u times on the same target.'',
    ''mod-sod-druid'', 1),
    (7009004, 407988, 1024, 256, ''Savage Roar'', ''ability_druid_skinteeth'',
    ''Finishing move that increases physical damage done by $s2% while in Cat Form. Lasts longer per combo point: 1 point 14 seconds, 2 points 19 seconds, 3 points 24 seconds, 4 points 29 seconds, 5 points 34 seconds.'',
    ''mod-sod-druid'', 1),
    (7009005, 417141, 1024, 128, ''Berserk'', ''ability_druid_berserk'',
    ''When activated, this ability causes your Mangle (Bear) and Lacerate abilities to hit up to $s3 targets, Lacerate to cost no Rage, Mangle (Bear) to have no cooldown, and reduces the energy cost of all your Cat Form abilities by $s1%. Lasts $d. Requires Bear Form, Cat Form, or Dire Bear Form to activate. Clears the effect of Fear and makes you immune to Fear for the duration.'',
    ''mod-sod-druid'', 1),
    (7009006, 408024, 1024, 512, ''Survival Instincts'', ''ability_druid_tigersroar'',
    ''When activated, this grants you $408025s1% of your maximum health and increases all non-Physical healing you deal by $s1% for $d. After the effect expires, the health is lost. Useable in all forms except Moonkin Form. In addition, you regenerate $417051s2 rage every time you dodge while in Bear Form or Dire Bear Form, $417051s3 energy while in Cat Form, or $417051s4% of your maximum mana while in any other form.'',
    ''mod-sod-druid'', 1),
    (7009007, 407995, 1024, 64, ''Mangle'', ''ability_druid_mangle2'',
    ''Mangles the target and increases the damage it takes from Bleed effects and Shred.'',
    ''mod-sod-druid'', 1),
    (7009008, 417145, 1024, 1, ''Gore'', ''inv_misc_questionmark'',
    ''Feral attacks can reset Mangle (Bear) or Tiger''''s Fury and grant Rage.'',
    ''mod-sod-druid'', 1),
    (7009009, 407977, 1024, 16, ''Wild Strikes'', ''spell_nature_windfury'',
    ''Grants nearby party and raid members the Wild Strikes effect while you are in a feral form.'',
    ''mod-sod-druid'', 1),
    (7009010, 417046, 1024, 512, ''King of the Jungle'', ''ability_mount_jungletiger'',
    ''Tiger''''s Fury grants energy and increases physical damage for a short time.'',
    ''mod-sod-druid'', 1),
    (7009011, 410176, 1024, 64, ''Skull Bash'', ''spell_druid_feralchargecat'',
    ''Charges and interrupts a spell, locking out that spell''''s school.'',
    ''mod-sod-druid'', 1),
    (7009012, 431389, 1024, 32, ''Improved Frenzied Regeneration'', ''ability_bullrush'',
    ''Frenzied Regeneration restores health from your active resource outside Moonkin Form.'',
    ''mod-sod-druid'', 1),
    (7009013, 439510, 1024, 8, ''Improved Swipe'', ''inv_misc_monsterclaw_03'',
    ''Swipe changes in Cat Form and hits more targets in Bear Form.'',
    ''mod-sod-druid'', 1),
    (7009014, 431388, 1024, 1, ''Improved Barkskin'', ''spell_nature_stoneclawtotem'',
    ''Barkskin can be cast on allies and while shapeshifted, without slowing attacks or spellcasting.'',
    ''mod-sod-druid'', 1),
    (7009015, 414677, 1024, 16, ''Living Seed'', ''spell_nature_rejuvenation'',
    ''Your critical heals plant a Living Seed on the target. It blooms when the target is next attacked.'',
    ''mod-sod-druid'', 1),
    (7009016, 417135, 1024, 1, ''Gale Winds'', ''spell_nature_cyclone'',
    ''Increases the damage done by your Hurricane by 20%, removes its cooldown, and reduces its mana cost by 30%.'',
    ''mod-sod-druid'', 1),
    (7009017, 414684, 1024, 64, ''Sunfire'', ''spell_nature_wrath'',
    ''Burns the enemy for Nature damage and then deals additional Nature damage over 12 sec.'',
    ''mod-sod-druid'', 1),
    (7009018, 414799, 1024, 16, ''Fury of Stormrage'', ''spell_nature_wrath'',
    ''Wrath costs no mana. Wrath damage has a 12% chance to make your next Healing Touch instant and castable in any form for 15 sec.'',
    ''mod-sod-druid'', 1),
    (7009019, 408258, 1024, 512, ''Dreamstate'', ''inv_misc_questionmark'',
    ''Damaging spell critical strikes and Starsurge damage restore 50% of your mana regeneration while casting for 8 sec and make non-player targets take 20% more Arcane and Nature damage for 12 sec.'',
    ''mod-sod-druid'', 1),
    (7009020, 439733, 1024, 8, ''Tree of Life'', ''spell_nature_rejuvenation'',
    ''Increases healing received by 10% for party members within 45 yards, Wild Growth healing by 60%, reduces heal over time mana costs by 20%, increases Spirit by 25% and armor by 200%.'',
    ''mod-sod-druid'', 1)
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

INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (-5217, 'spell_sod_druid_king_of_the_jungle');

INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(22842, 'spell_sod_druid_improved_frenzied_regeneration_cast'),
(428708, 'spell_sod_druid_improved_frenzied_regeneration_aura'),
(-779, 'spell_sod_druid_swipe_bear_targets'),
(62078, 'spell_sod_druid_swipe_cat_redirect');

INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (22812, 'spell_sod_druid_improved_barkskin');
