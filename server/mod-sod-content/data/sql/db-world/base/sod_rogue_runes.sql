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
     ''mod-sod-rogue'', 1),
    (7004012, 399985, 8, 64, ''Shadowstrike'', ''ability_rogue_shadowstep'',
     ''Te teletransportas detrás de tu objetivo y lo golpeas para infligir un 150% de daño con arma. Requiere sigilo y otorga 1 p. de combo.'',
     ''mod-sod-rogue'', 1),
    (7004013, 425012, 8, 128, ''Poisoned Knife'', ''ability_throw'',
     ''Lanzas el arma de la mano izquierda, aplicas su veneno y obtienes 1 p. de combo. Cada aplicación de Veneno mortal devuelve 5 p. de energía.'',
     ''mod-sod-rogue'', 1),
    (7004014, 400029, 8, 128, ''Shadowstep'', ''ability_rogue_shadowstep'',
     ''Te teletransportas detrás del enemigo y aumentas un 70% tu velocidad de movimiento durante 3 s.'',
     ''mod-sod-rogue'', 1),
    (7004015, 399986, 8, 128, ''Shuriken Toss'', ''ability_throw'',
     ''Lanzas un shuriken que inflige daño equivalente al 50% de tu poder de ataque y puede golpear hasta 4 objetivos adicionales cercanos.'',
     ''mod-sod-rogue'', 1),
    (7004016, 425096, 8, 512, ''Master of Subtlety'', ''ability_rogue_masterofsubtlety'',
     ''Tus ataques infligen un 10% más de daño mientras estás en sigilo y durante 6 s después de salir de él.'',
     ''mod-sod-rogue'', 1),
    (7004017, 400016, 8, 512, ''Rolling with the Punches'', ''ability_rogue_cheatdeath'',
     ''Cada vez que esquivas o paras, acumulas una bonificación de salud hasta 5 veces.'',
     ''mod-sod-rogue'', 1),
    (7004018, 408700, 8, 512, ''Waylay'', ''ability_rogue_waylay'',
     ''Emboscada y Puñalada aumentan un 20% el tiempo entre los ataques cuerpo a cuerpo del objetivo y reducen un 50% su velocidad de movimiento durante 8 s.'',
     ''mod-sod-rogue'', 1),
    (7004019, 432259, 8, 1, ''Combat Potency'', ''inv_weapon_shortblade_38'',
     ''Tus ataques cuerpo a cuerpo con el arma de mano izquierda tienen un 20% de probabilidad de otorgarte 15 p. de energía.'',
     ''mod-sod-rogue'', 1),
    (7004020, 432256, 8, 1, ''Focused Attacks'', ''ability_rogue_focusedattacks'',
     ''Tus golpes críticos cuerpo a cuerpo y a distancia te otorgan energía.'',
     ''mod-sod-rogue'', 1),
    (7004021, 432264, 8, 1, ''Honor Among Thieves'', ''ability_rogue_honoramongstthieves'',
     ''Cuando un jugador de tu grupo asesta un golpe crítico con una facultad o hechizo, obtienes un punto de combo en tu objetivo actual. No puede ocurrir más de una vez por segundo.'',
     ''mod-sod-rogue'', 1),
    (7004022, 432276, 8, 32, ''Carnage'', ''ability_rogue_rupture'',
     ''Tus facultades infligen más daño a objetivos con un sangrado tuyo. Ruptura te sana un 40% del daño que inflige.'',
     ''mod-sod-rogue'', 1),
    (7004023, 432271, 8, 32, ''Cut to the Chase'', ''ability_rogue_cuttothechase'',
     ''Eviscerar y Envenenar restauran Hacer picadillo o Danza de hojas hasta la duración máxima de 5 puntos de combo. Si ambos están activos, se restaura el que tiene menos tiempo restante.'',
     ''mod-sod-rogue'', 1),
    (7004024, 432273, 8, 32, ''Unfair Advantage'', ''ability_rogue_unfairadvantage'',
     ''Esquivar o parar un ataque te permite contraatacar con el arma de mano principal y obtener puntos de combo. Solo puede ocurrir una vez por segundo.'',
     ''mod-sod-rogue'', 1),
    (7004025, 436564, 8, 8, ''Blunderbuss'', ''ability_rogue_fanofknives'',
     ''Disparas un trabuco a un máximo de 10 enemigos en un cono frente a ti e infliges daño físico.'',
     ''mod-sod-rogue'', 1),
    (7004026, 412096, 8, 8, ''Crimson Tempest'', ''ability_rogue_rupture'',
     ''Remate que aplica un sangrado a todos los enemigos en 8 m. El daño y la duración aumentan con los puntos de combo y se beneficia de los efectos de Ruptura.'',
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
    (-1966, 'spell_sod_rogue_just_a_flesh_wound_feint'),
    (-32645, 'spell_sod_rogue_cut_to_the_chase_envenom'),
    (432271, 'spell_sod_rogue_cut_to_the_chase'),
    (412096, 'spell_sod_rogue_crimson_tempest');
