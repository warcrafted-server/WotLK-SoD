-- mod-sod-druid: fuente real en SoD de la runa Lluvia de estrellas (7009025).
--
-- En SoD la suelta Arcterris (228814): nivel 58, bestia y élite, en Vallefresno
-- (tooltip de PNJ de Wowhead, consultado el 2026-10-18). Esa criatura no existe
-- en el core, así que se crea aquí con su botín y su spawn. El Grabador (700000)
-- deja de vender el ítem de esta runa: su DELETE va en
-- sod_druid_acquisition_balance_resto.sql, que es el fichero que mantiene esa
-- lista de vendedor.
--
-- Plantilla: se copian los valores de «Elder Shardtooth» (7445), la criatura del
-- core más parecida que existe: bestia (type 1) de nivel 57-58 en Vallefresno y
-- facción 16 (hostil), como Arcterris. De ella se reutilizan su clase de unidad
-- (1), sus velocidades (1.0 / 1.14286), su rango de detección (18), sus
-- modificadores (vida 1.6, maná 1, armadura 1, daño 1), su familia (4, oso) y su
-- modelo (8837). Sobre esa copia solo cambia lo verificado de Arcterris: el
-- nombre, el nivel fijo (58) y el rango (1, élite). El modelo 8837 es un
-- sustituto stock (el oso de «Elder Shardtooth»): el de SoD (121801 en Wowhead)
-- no existe en el cliente 3.3.5a, y la familia real tampoco está verificada.
-- Tampoco se le da AI ni hechizos propios, porque los de SoD no se conocen.
--
-- Botín: Rune of the Falling Star (227749) al 66,67 % y solo para druidas, con
-- el mismo mecanismo que los demás botines de runa de druida (condición de clase
-- 1024 en `conditions`). Wowhead da una muestra de 2 de 3, de donde sale ese
-- 66,67 %; es una muestra mínima y aquí queda anotado.
--
-- Spawn: la capa de datos de Wowhead lista diez puntos de Vallefresno (mapa 1)
-- entre (62,16) y (65,20) % del mapa, repartidos en algo más de 200 m alrededor
-- de (7700, -4860). Son de la misma criatura única, que patrulla o cubre una
-- zona; como su ruta real no se conoce, se crea UN solo spawn en ese centro y no
-- se inventa el recorrido. La z NO se conoce, así que se toma del `creature` de
-- mapa 1 más cercano en distancia plana con un SELECT; conviene revisarla en
-- juego (`.npc move`). Respawn de 3600 s por ser élite. Guid en la banda 8820030+.
--
-- Idempotente: REPLACE para plantilla, modelo, loot y condiciones, e INSERT
-- IGNORE para el spawn (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- Arcterris (creature 228814, id real de SoD, libre en el core).
-- Nivel 58 élite, bestia (type 1), hostil (faction 16), cuerpo a cuerpo
-- (unit_class 1) y sin AI propia. lootid = 228814 para que caiga su tabla de
-- botín.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `detection_range`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `family`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `flags_extra`)
VALUES
    (228814, 'Arcterris', '',
     58, 58, 16, 0,
     1.0, 1.14286, 18, 1,
     1, 0, 2048, 4, 1, 228814,
     '', 0,
     1, 1.6, 1.0, 1.0, 1.0, 0);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (228814, 0, 8837, 1.0, 1.0);

-- Botín: la runa, solo para druidas (misma forma que los botines de
-- sod_druid_acquisition.sql y sod_druid_acquisition_balance_resto.sql).
REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (228814, 227749, 0, 66.67, 0, 1, 0, 1, 1, 'mod-sod-druid Starfall rune');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 228814, 227749, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Starfall item for class only');

-- =====================================================================
-- Spawn único de Vallefresno (mapa 1), 3600 s de respawn por ser élite. La z
-- sale del `creature` de mapa 1 más cercano en distancia plana al punto;
-- `guid` < 8820000 excluye la banda de criaturas propias del módulo, para que la
-- z venga siempre de una criatura real del core. Los otros puntos de Wowhead son
-- el mismo PNJ patrullando: no se crean.
-- =====================================================================
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820030, 228814, 1, 0, 0, 1, 1, 0, 7700, -4860, `position_z`, 0, 3600, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` - 7700, 2) + POW(`position_y` + 4860, 2)
LIMIT 1;
