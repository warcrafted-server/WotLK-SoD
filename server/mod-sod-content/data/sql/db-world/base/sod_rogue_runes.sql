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
     ''mod-sod-rogue'', 1),
    (7004007, 400012, 8, 256, ''Blade Dance'', ''ability_rogue_eviscerate'',
     ''Aumenta la parada un 10% y otorga 4 p. de poder de ataque por cada punto de Defensa sobre el valor base según el nivel. Dura más con puntos de combo.'',
     ''mod-sod-rogue'', 1),
    (7004008, 399963, 8, 256, ''Envenom'', ''ability_rogue_eviscerate'',
     ''Remate de veneno según las dosis de Veneno mortal. Consume una dosis por punto de combo y aumenta la probabilidad de aplicar Veneno instantáneo.'',
     ''mod-sod-rogue'', 1),
    (7004009, 462708, 8, 64, ''Cutthroat'', ''ability_rogue_ambush'',
     ''Permite usar Emboscada, Puñalada y Garrote sin estar detrás del objetivo. Puñalada puede permitir que la siguiente Emboscada no requiera sigilo.'',
     ''mod-sod-rogue'', 1),
    (7004010, 424919, 8, 64, ''Main Gauche'', ''ability_rogue_eviscerate'',
     ''Golpeas con el arma de mano izquierda, aumentas la parada durante 5 s y obtienes 1 punto de combo.'',
     ''mod-sod-rogue'', 1),
    (7004011, 424785, 8, 64, ''Saber Slash'', ''ability_rogue_eviscerate'',
     ''Tajo con arma que inflige daño y causa un sangrado de 12 s con pulsos cada 2 s. Se beneficia de los efectos de Golpe siniestro.'',
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
