-- mod-sod-content: Warlock rune definitions (SoD phase 1 pilot).
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
    (7008001, 403629, 256, 64, ''Chaos Bolt'', ''ability_warlock_chaosbolt'',
     ''Sends a bolt of chaotic fire at the enemy, dealing Chaos damage.'',
     ''mod-sod-warlock'', 1),
    (7008002, 403501, 256, 64, ''Haunt'', ''ability_warlock_haunt'',
     ''Unleash a ghostly soul on an enemy, dealing damage and increasing all Shadow damage over time you deal to that target.'',
     ''mod-sod-warlock'', 1),
    (7008003, 412727, 256, 16, ''Demonic Tactics'', ''spell_shadow_demonictactics'',
     ''Increases the melee and spell critical strike chance of you and your pet by 10%.'',
     ''mod-sod-warlock'', 1),
    (7008004, 427717, 256, 32, ''Unstable Affliction'', ''spell_shadow_unstableaffliction_3'',
     ''Deals Shadow damage over time. If dispelled, it damages and silences the dispeller.'',
     ''mod-sod-warlock'', 1),
    (7008005, 427733, 256, 32, ''Summon Felguard'', ''spell_shadow_summonfelguard'',
     ''Summons a Felguard under your command.'',
     ''mod-sod-warlock'', 1),
    (7008006, 403789, 256, 64, ''Metamorphosis'', ''spell_shadow_demonform'',
     ''Transform into a Demon and gain a tanking form.'',
     ''mod-sod-warlock'', 1),
    (7008007, 412758, 256, 32, ''Incinerate'', ''spell_fire_burnout'',
     ''Burns the enemy and increases your Fire damage for 15 sec.'',
     ''mod-sod-warlock'', 1),
    (7008008, 426320, 256, 512, ''Shadowflame'', ''ability_warlock_shadowflame'',
     ''Deals Shadowflame damage and applies additional damage over time.'',
     ''mod-sod-warlock'', 1),
    (7008009, 427713, 256, 1, ''Backdraft'', ''ability_warlock_backdraft'',
     ''Your Conflagrate also grants spellcasting haste and no longer consumes Immolate.'',
     ''mod-sod-warlock'', 1),
    (7008010, 440870, 256, 512, ''Decimation'', ''spell_fire_fireball02'',
     ''Your Soul Fire has no cooldown, and hitting a low-health target shortens its cast time. Costs no shard.'',
     ''mod-sod-warlock'', 1),
    (7008011, 425464, 256, 256, ''Demonic Pact'', ''spell_shadow_demonicpact'',
     ''Your Fire and Shadow spells deal more damage, and your pet critical strikes grant your party spell damage and healing.'',
     ''mod-sod-warlock'', 1),
    (7008012, 412689, 256, 256, ''Everlasting Affliction'', ''ability_warlock_everlastingaffliction'',
     ''Drain Life, Drain Soul, Shadowbolt, Shadow Cleave, Searing Pain, Incinerate and Haunt refresh your Corruption.'',
     ''mod-sod-warlock'', 1),
    (7008013, 412732, 256, 512, ''Demonic Knowledge'', ''spell_shadow_improvedvampiricembrace'',
     ''Increases your spell damage and healing by 3% of your demon pet total Stamina plus Intellect.'',
     ''mod-sod-warlock'', 1)
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

-- Reutiliza los manejadores nativos del core para los clones de Aflicción inestable, Llama de las
-- Sombras, Exterminio, Aflicción eterna y Conocimiento demoníaco. El emisor (sod-client) también
-- escribe estas filas; aquí quedan como en 427717/426320, para que el módulo sea autosuficiente.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (427717, 'spell_warl_unstable_affliction'),
    (426320, 'spell_warl_shadowflame'),
    (440870, 'spell_warl_decimation'),
    (412698, 'spell_warl_everlasting_affliction'),
    (900048, 'spell_warl_demonic_knowledge');

-- Auras que el familiar hereda al invocarse (spell_pet_auras es tabla base del core, no la
-- genera el emisor): 54909 es el aura nativa que dispara Pacto demoníaco desde el familiar, y
-- 900048 es la copia de servidor del aura de Conocimiento demoníaco (WotLK usa 35696 con 12 %,
-- SoD pide 3 %). No se toca ninguna fila de Blizzard: sólo se insertan las dos nuestras.
DELETE FROM `spell_pet_auras` WHERE `spell` IN (425464, 412732);
INSERT INTO `spell_pet_auras` (`spell`, `effectId`, `pet`, `aura`) VALUES
    (425464, 0, 0, 54909),
    (412732, 0, 0, 900048);
