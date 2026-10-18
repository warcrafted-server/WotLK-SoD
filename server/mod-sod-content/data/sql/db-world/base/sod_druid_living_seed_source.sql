-- mod-sod-druid: fuente real en SoD de la runa Semilla viviente (7009015).
--
-- En SoD la suelta «Unleashed Nature Spirit» (206245): nivel 7, elemental, no
-- élite, en Mulgore y Teldrassil (tooltip de PNJ de Wowhead, consultado el
-- 2026-10-18). Esa criatura no existe en el core, así que se crea aquí con su
-- botín y sus dos spawns verificados de Mulgore. El Grabador (700000) deja de
-- vender el ítem de esta runa: su DELETE va en
-- sod_druid_acquisition_balance_resto.sql, que es el fichero que mantiene esa
-- lista de vendedor.
--
-- Botín: Rune of Natural Potential (206963) al 100 % y solo para druidas, con el
-- mismo mecanismo que los demás botines de runa de druida (condición de clase
-- 1024 en `conditions`). La muestra de Wowhead es 2/2, sin fiabilidad: se deja
-- el 100 % y aquí queda anotado.
--
-- Spawns: dos en Mulgore (mapa 1) en las coordenadas verificadas. La z NO se
-- conoce, así que se toma del `creature` de mapa 1 más cercano en distancia
-- plana con un SELECT; conviene revisarla en juego (`.npc move`). En SoD hay
-- otros dos spawns en Teldrassil cuyas coordenadas no se conocen: quedan
-- pendientes, no se inventan.
--
-- Display: 28980 (Creature\Ent\Ent.mdx, el mismo modelo que usa «Angry Oak
-- Spirit», criatura elemental del core). El modelo real de SoD no está
-- verificado; es un sustituto stock.
--
-- Idempotente: REPLACE para plantilla, modelo, loot y condiciones, e INSERT
-- IGNORE para los spawns (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- Unleashed Nature Spirit (creature 206245, id real de SoD, libre en el core).
-- Nivel 7 normal, elemental (type 4), hostil a todo el mundo (faction 14),
-- cuerpo a cuerpo (unit_class 1), sin AI propia. lootid = 206245 para que caiga
-- su tabla de botín. unit_flags2 2048 (regenerar poder) es lo habitual en las
-- criaturas salvajes de la base. Guids de spawn en la banda 8820010+.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (206245, 'Unleashed Nature Spirit', '',
     7, 7, 14, 0,
     1.0, 1.14286, 0,
     1, 0, 2048, 4, 206245,
     '', 0,
     1, 0);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (206245, 0, 28980, 1.0, 1.0);

-- Botín: la runa, solo para druidas (misma forma que los botines de
-- sod_druid_acquisition.sql y sod_druid_acquisition_balance_resto.sql).
REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (206245, 206963, 0, 100, 0, 1, 0, 1, 1, 'mod-sod-druid Living Seed rune');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 206245, 206963, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Living Seed item for class only');

-- =====================================================================
-- Spawns de Mulgore (mapa 1), 300 s de respawn. La z sale del `creature` de
-- mapa 1 más cercano en distancia plana a cada punto; `guid` < 8820000 excluye
-- la banda de criaturas propias del módulo, para que la z venga siempre de una
-- criatura real del core (en la base, la misma para los dos puntos, a unos 50 m).
-- =====================================================================
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820010, 206245, 1, 0, 0, 1, 1, 0, -1972, 116, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 1972, 2) + POW(`position_y` - 116, 2)
LIMIT 1;

INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820011, 206245, 1, 0, 0, 1, 1, 0, -1965, 106, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 1965, 2) + POW(`position_y` - 106, 2)
LIMIT 1;
