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
