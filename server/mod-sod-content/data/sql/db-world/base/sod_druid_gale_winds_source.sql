-- mod-sod-druid: fuente real en SoD de la runa Vientos galernos (7009016).
--
-- En SoD la suelta Namida Grimtotem (222286): nivel 43, humanoide y élite, en
-- Feralas (tooltip de PNJ de Wowhead, consultado el 2026-10-18). Esa criatura no
-- existe en el core, así que se crea aquí con su botín y su spawn verificado. El
-- Grabador (700000) deja de vender el ítem de esta runa: su DELETE va en
-- sod_druid_acquisition_balance_resto.sql, que es el fichero que mantiene esa
-- lista de vendedor.
--
-- Plantilla: se copian los valores de «Grimtotem Shaman» (7727), la criatura del
-- core más parecida que existe: nivel 43-44, humanoide (type 7), facción 16
-- (hostil) y en el mismo campamento de Feralas. De ella se reutilizan su clase de
-- unidad (2, con maná), sus velocidades, su rango de detección, sus modificadores
-- (vida 1,2, maná 1, armadura 1, daño 1) y su modelo (6833). Sobre esa copia solo
-- cambia lo verificado de Namida: el nombre, el nivel fijo (43) y el rango (1,
-- élite). El modelo 6833 es un sustituto stock (el tauren de «Grimtotem Shaman»);
-- el modelo real de SoD no está verificado. Tampoco se le da AI ni hechizos
-- propios, porque los de SoD no se conocen.
--
-- Botín: Rune of the Windstorm (220754) al 100 % y solo para druidas, con el
-- mismo mecanismo que los demás botines de runa de druida (condición de clase
-- 1024 en `conditions`). La muestra de Wowhead es 1/1, sin fiabilidad: se deja
-- el 100 % y aquí queda anotado.
--
-- Spawn: la capa de datos de Wowhead lista tres puntos en Feralas (mapa 1):
-- (-4146, 827), (-4137, 813) y (-4155, 799). Son de la misma criatura única, que
-- patrulla; como su ruta real no se conoce, se crea UN solo spawn en el primero y
-- no se inventa el recorrido. La z NO se conoce, así que se toma del `creature`
-- de mapa 1 más cercano en distancia plana con un SELECT; conviene revisarla en
-- juego (`.npc move`). Respawn de 3600 s por ser élite. Guid en la banda 8820020+.
--
-- Idempotente: REPLACE para plantilla, modelo, loot y condiciones, e INSERT
-- IGNORE para el spawn (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- Namida Grimtotem (creature 222286, id real de SoD, libre en el core).
-- Nivel 43 élite, humanoide (type 7), hostil (faction 16, la del Grimtotem del
-- core), con maná (unit_class 2) y sin AI propia. lootid = 222286 para que caiga
-- su tabla de botín.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `detection_range`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `flags_extra`)
VALUES
    (222286, 'Namida Grimtotem', '',
     43, 43, 16, 0,
     1.0, 1.14286, 18, 1,
     2, 32768, 2048, 7, 222286,
     '', 0,
     1, 1.2, 1.0, 1.0, 1.0, 0);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (222286, 0, 6833, 1.0, 1.0);

-- Botín: la runa, solo para druidas (misma forma que los botines de
-- sod_druid_acquisition.sql y sod_druid_acquisition_balance_resto.sql).
REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (222286, 220754, 0, 100, 0, 1, 0, 1, 1, 'mod-sod-druid Gale Winds rune');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 222286, 220754, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Gale Winds item for class only');

-- =====================================================================
-- Spawn único de Feralas (mapa 1), 3600 s de respawn por ser élite. La z sale del
-- `creature` de mapa 1 más cercano en distancia plana al punto; `guid` < 8820000
-- excluye la banda de criaturas propias del módulo, para que la z venga siempre
-- de una criatura real del core. Los otros dos puntos de Wowhead son el mismo PNJ
-- patrullando: no se crean.
-- =====================================================================
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820020, 222286, 1, 0, 0, 1, 1, 0, -4146, 827, `position_z`, 0, 3600, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 4146, 2) + POW(`position_y` - 827, 2)
LIMIT 1;
