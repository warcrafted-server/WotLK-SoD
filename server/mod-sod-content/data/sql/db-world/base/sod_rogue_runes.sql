-- mod-sod-content: definiciones de runas del pícaro (fase 1 de SoD).
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
    (7004001, 399956, 8, 64, ''Mutilate'', ''ability_rogue_shadowstrikes'',
     ''Instantly attacks with both weapons for weapon damage plus additional damage with each weapon. Damage is increased against poisoned targets and awards combo points.'',
     ''mod-sod-rogue'', 1),
    (7004002, 399965, 8, 16, ''Deadly Brew'', ''ability_rogue_deadlybrew'',
     ''Cuando aplicas otro veneno, también aplicas Veneno mortal. El veneno mortal y el instantáneo se benefician del poder de ataque.'',
     ''mod-sod-rogue'', 1),
    (7004003, 400014, 8, 16, ''Just a Flesh Wound'', ''ability_rogue_cheatdeath'',
     ''Mientras Danza de hojas está activa, recibes menos daño físico. También aumenta tu esquiva y amenaza, y Amago provoca al objetivo seleccionado.'',
     ''mod-sod-rogue'', 1),
    (7004004, 398196, 8, 16, ''Quick Draw'', ''ability_impalingbolt'',
     ''Disparas con tu arma a distancia, ralentizas al objetivo y obtienes un punto de combo. Se beneficia de los talentos y efectos de Golpe siniestro.'',
     ''mod-sod-rogue'', 1),
    (7004005, 424925, 8, 16, ''Slaughter from the Shadows'', ''ability_rogue_slaughterfromtheshadows'',
     ''Reduce el coste de energía de Puñalada y Emboscada y aumenta el daño que infligen a objetivos no controlados por jugadores.'',
     ''mod-sod-rogue'', 1),
    (7004006, 400009, 8, 256, ''Between the Eyes'', ''ability_rogue_kidneyshot'',
     ''Remate a distancia que inflige daño según tus puntos de combo y poder de ataque, y aturde al objetivo. Comparte reutilización con Golpe en los riñones.'',
     ''mod-sod-rogue'', 1)
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

-- Puñalada y Emboscada: el id negativo cubre todos los rangos de WotLK.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-53, 'spell_sod_rogue_slaughter_targets'),
    (-8676, 'spell_sod_rogue_slaughter_targets'),
    (-1966, 'spell_sod_rogue_just_a_flesh_wound_feint');
