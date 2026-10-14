-- mod-sod-content: Priest rune definitions.
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
    (7005001, 401946, 16, 64, ''Circle of Healing'', ''spell_holy_circleofrenewal'',
     ''Heals all of the target player''''s party members around the target player.'',
     ''mod-sod-priest'', 1),
    (7005002, 402174, 16, 64, ''Penance'', ''spell_holy_penance'',
     ''Launches a volley of holy light at the target, damaging an enemy or healing an ally.'',
     ''mod-sod-priest'', 1),
    (7005003, 413248, 16, 16, ''Serendipity'', ''spell_holy_serendipity'',
     ''Healing with Flash Heal reduces the cast time of your next Lesser Heal, Heal, Greater Heal, or Prayer of Healing, stacking up to 3 times.'',
     ''mod-sod-priest'', 1),
    (7005004, 415739, 16, 16, ''Strength of Soul'', ''spell_holy_powerwordshield'',
     ''Lesser Heal, Heal, Greater Heal, and Flash Heal reduce Weakened Soul. Power Word: Shield also lets absorbed damage trigger Rage and Righteous Fury.'',
     ''mod-sod-priest'', 1),
    (7005005, 425198, 16, 16, ''Twisted Faith'', ''spell_shadow_mindtwisting'',
     ''Mind Flay and Mind Blast deal 50% increased damage to targets afflicted with your Shadow Word: Pain.'',
     ''mod-sod-priest'', 1),
    (7005006, 402799, 16, 256, ''Homunculi'', ''spell_shadow_shadowfiend'',
     ''Summons a Shadowfiend as a temporary approximation of the three Homunculi.'',
     ''mod-sod-priest'', 1),
    (7005007, 401859, 16, 256, ''Prayer of Mending'', ''spell_holy_prayerofmendingtga'',
     ''Places a healing spell on the target that jumps to another party or raid member after healing.'',
     ''mod-sod-priest'', 1),
    (7005008, 401969, 16, 256, ''Shared Pain'', ''spell_shadow_shadowwordpain'',
     ''Your Shadow Word: Pain also afflicts up to two additional nearby targets within 15 yards.'',
     ''mod-sod-priest'', 1),
    (7005009, 413259, 16, 64, ''Mind Sear'', ''spell_shadow_mindshear'',
     ''Channels shadow magic that damages enemies near the target for 6 sec.'',
     ''mod-sod-priest'', 1),
    (7005010, 401955, 16, 64, ''Shadow Word: Death'', ''spell_shadow_demonicfortitude'',
     ''Deals Shadow damage to the target. If it survives, the caster takes damage equal to 50% of the attempted damage.'',
     ''mod-sod-priest'', 1),
    (7005011, 425266, 16, 128, ''Empowered Renew'', ''spell_holy_renew'',
     ''Renew heals one additional time immediately and gains increased benefit from healing effects with each tick.'',
     ''mod-sod-priest'', 1),
    (7005012, 431655, 16, 128, ''Mind Spike'', ''spell_shadow_unholyfrenzy'',
     ''Deals Shadowfrost damage and increases the next Mind Blast critical strike chance against the target, stacking up to three times.'',
     ''mod-sod-priest'', 1)
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

INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-589, 'spell_sod_priest_shared_pain'),
    (-139, 'spell_sod_priest_empowered_renew'),
    (-8092, 'spell_sod_priest_mind_spike_mind_blast');
