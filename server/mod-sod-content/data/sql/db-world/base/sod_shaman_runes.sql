-- mod-sod-content: Shaman rune definitions.
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
    (7007001, 408514, 64, 256, ''Earth Shield'', ''spell_nature_skinofearth'',
     ''Protects the target with an earthen shield. Earth Shield can only be placed on one target at a time.'',
     ''mod-sod-shaman'', 1),
    (7007002, 408507, 64, 64, ''Lava Lash'', ''ability_shaman_lavalash'',
     ''You charge your off-hand weapon with lava, instantly dealing off-hand weapon damage. Damage is increased if your off-hand weapon is enchanted with Flametongue.'',
     ''mod-sod-shaman'', 1),
    (7007003, 408490, 64, 64, ''Lava Burst'', ''spell_shaman_lavaburst'',
     ''You hurl molten lava at the target, dealing Fire damage. If your Flame Shock is on the target, Lava Burst will deal a critical strike.'',
     ''mod-sod-shaman'', 1),
    (7007004, 408521, 64, 32, ''Riptide'', ''spell_nature_riptide'',
     ''Heals a friendly target and applies a heal over time. Your Chain Heals on that target are more effective. This spell also triggers Ancestral Awakening.'',
     ''mod-sod-shaman'', 1),
    (7007005, 440580, 64, 8, ''Feral Spirit'', ''spell_shaman_feralspirit'',
     ''Summons two Spirit Wolves under the command of the Shaman.'',
     ''mod-sod-shaman'', 1),
    (7007006, 408498, 64, 128, ''Maelstrom Weapon'', ''spell_shaman_maelstromweapon'',
     ''Melee attacks can reduce the cast time and mana cost of your next Lightning Bolt, Chain Lightning, Lesser Healing Wave, or Lava Burst. Stacks up to its maximum.'',
     ''mod-sod-shaman'', 1),
    (7007007, 432042, 64, 1, ''Tidal Waves'', ''spell_shaman_tidalwaves'',
     ''Casting Chain Heal or Riptide grants charges that reduce the cast time of Healing Wave and Chain Heal and increase Lesser Healing Wave critical chance.'',
     ''mod-sod-shaman'', 1),
    (7007008, 425858, 64, 512, ''Ancestral Awakening'', ''spell_shaman_ancestralawakening'',
     ''Critical Healing Wave or Lesser Healing Wave spells heal the lowest-health party member nearby for part of the amount healed.'',
     ''mod-sod-shaman'', 1),
    (7007009, 408496, 64, 16, ''Dual Wield Specialization'', ''ability_dualwield'',
     ''Increases hit chance while dual wielding, enables Stormstrike to hit with both weapons, and increases off-hand weapon damage.'',
     ''mod-sod-shaman'', 1),
    (7007010, 408438, 64, 16, ''Overload'', ''spell_nature_lightningoverload'',
     ''Lightning Bolt, Chain Lightning, Chain Heal, Healing Wave, and Lava Burst have a chance to repeat for half effect without cost or threat.'',
     ''mod-sod-shaman'', 1),
    (7007011, 408524, 64, 16, ''Shield Mastery'', ''spell_nature_lightningshield'',
     ''Blocking restores mana and grants stacking armor; also increases block chance and value. Shock spells grant spell damage based on Defense skill.'',
     ''mod-sod-shaman'', 1),
    (7007012, 436364, 64, 16, ''Two-Handed Mastery'', ''spell_fire_enchantweapon'',
     ''Two-handed weapon hits grant attack speed, attack power, and spell hit for a short time; one-handed weapon hits remove the effect.'',
     ''mod-sod-shaman'', 1),
    (7007013, 415236, 64, 16, ''Healing Rain'', ''spell_nature_tranquility'',
     ''Selects an area around the target player and heals up to five nearby party members every second.'',
     ''mod-sod-shaman'', 1)
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

-- Reutiliza el manejador nativo de AzerothCore para el aura auxiliar de Maelstrom Weapon.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (408505, 'spell_sha_maelstrom_weapon');
