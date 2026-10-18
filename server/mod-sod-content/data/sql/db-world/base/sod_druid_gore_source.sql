-- mod-sod-druid: fuente real en SoD de la runa Cornada (7009008).
--
-- En SoD el ítem Rune of Bloodshed (221517) lo venden cuatro intendentes
-- (Quartermaster) de la facción Guardianes Esmeralda: Falinar (222684, nivel 25,
-- Bosque del Ocaso), Kyleen (222685, nivel 40, Vallefresno), Alandra (222686,
-- nivel 50, Tierras del Interior) y Valdane (222687, nivel 50, Feralas). Los
-- cuatro son PNJ humanos, no élite y vendedores (tooltip de PNJ de Wowhead,
-- consultado el 2026-10-18). El Grabador (700000) deja de vender el ítem de esta
-- runa: su DELETE va en sod_druid_acquisition.sql, que es el fichero que
-- mantiene esa lista de vendedor.
--
-- Facción: 35 para los cuatro, la misma del Grabador: es amistosa con las dos
-- facciones y así la runa queda al alcance tanto de los taurens como de los
-- elfos de la noche (los druidas son de ambas). Civiles y no atacables como
-- Grizzby: unit_flags 2 (NON_ATTACKABLE) y flags_extra 2 (CIVILIAN).
--
-- Subnombre: «Quartermaster» (esES «Intendente»). Wowhead no da el subnombre
-- exacto de estos cuatro PNJ, así que es una suposición razonable, no un dato
-- verificado.
--
-- Modelo: 2217, el de Jaeana (4169), la vendedora de carne de Darnassus. Es una
-- elfa de la noche stock (CreatureModelData.dbc del cliente 3.3.5a: modelo
-- NightElfFemale), encaja con una intendente de los Guardianes Esmeralda y no
-- obliga a inventar un modelo propio (los modelos de SoD no están en 3.3.5a).
--
-- Precio: el core no permite precios distintos por vendedor. El ítem ya tiene
-- BuyPrice 16000 en sod_druid_acquisition.sql. Wowhead da 16000 cobre para
-- Falinar y Valdane y 16842 para Kyleen y Alandra, sin confirmar la unidad; se
-- deja el precio único del ítem (16000) y aquí queda anotada la diferencia de
-- 842 cobre. Requisito de nivel de compra: no verificado, no se inventa.
--
-- Spawns: la z NO se conoce, así que se toma del `creature` del mismo mapa más
-- cercano en distancia plana con un SELECT, igual que en
-- sod_druid_living_seed_source.sql, sod_druid_gale_winds_source.sql y
-- sod_druid_starfall_source.sql; conviene revisarla en juego (`.npc move`).
-- Falinar tiene dos puntos en Wowhead ((-10638, -398) y (-10574, -430)) que son
-- del mismo PNJ: se crea UN solo spawn en el primero. La orientación tampoco se
-- conoce: se deja 0. Guids propios 8820040-8820043.
--
-- Idempotente: REPLACE para plantilla, modelo y stock, e INSERT IGNORE para los
-- spawns (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- Los cuatro intendentes (creature 222684-222687, ids reales de SoD, libres en
-- el core). Vendedores (npcflag 128), facción 35 (amistosa con ambos bandos),
-- no atacables y civiles, humanoide (type 7) sin AI propia ni ScriptName: el
-- core abre la ventana de mercader con las filas de `npc_vendor`.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `flags_extra`,
     `ScriptName`)
VALUES
    (222684, 'Falinar', 'Quartermaster',
     25, 25, 35, 128,
     1.0, 1.14286,
     1, 2, 0, 7, 2,
     ''),
    (222685, 'Kyleen', 'Quartermaster',
     40, 40, 35, 128,
     1.0, 1.14286,
     1, 2, 0, 7, 2,
     ''),
    (222686, 'Alandra', 'Quartermaster',
     50, 50, 35, 128,
     1.0, 1.14286,
     1, 2, 0, 7, 2,
     ''),
    (222687, 'Valdane', 'Quartermaster',
     50, 50, 35, 128,
     1.0, 1.14286,
     1, 2, 0, 7, 2,
     '');

-- Modelo 2217 (elfa de la noche stock, la de Jaeana) para los cuatro.
REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (222684, 0, 2217, 1.0, 1.0),
    (222685, 0, 2217, 1.0, 1.0),
    (222686, 0, 2217, 1.0, 1.0),
    (222687, 0, 2217, 1.0, 1.0);

-- Stock: la runa, con el precio del ítem (16000 cobre). Sin `maxcount` ni
-- reabastecimiento (`incrtime`), como el resto de vendedores del módulo.
REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (222684, 0, 221517, 0, 0, 0),
    (222685, 0, 221517, 0, 0, 0),
    (222686, 0, 221517, 0, 0, 0),
    (222687, 0, 221517, 0, 0, 0);

-- =====================================================================
-- Spawns, uno por intendente; 300 s de respawn (no son élite). La z sale del
-- `creature` del mismo mapa más cercano en distancia plana al punto; `guid`
-- < 8820000 excluye la banda de criaturas propias del módulo, para que la z
-- venga siempre de una criatura real del core.
-- =====================================================================

-- Falinar, Bosque del Ocaso (mapa 0). El segundo punto de Wowhead es el mismo
-- PNJ: no se crea.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820040, 222684, 0, 0, 0, 1, 1, 0, -10638, -398, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` + 10638, 2) + POW(`position_y` + 398, 2)
LIMIT 1;

-- Kyleen, Vallefresno (mapa 1).
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820041, 222685, 1, 0, 0, 1, 1, 0, 3112, -3455, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` - 3112, 2) + POW(`position_y` + 3455, 2)
LIMIT 1;

-- Alandra, Tierras del Interior (mapa 0).
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820042, 222686, 0, 0, 0, 1, 1, 0, 584, -3939, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` - 584, 2) + POW(`position_y` + 3939, 2)
LIMIT 1;

-- Valdane, Feralas (mapa 1).
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820043, 222687, 1, 0, 0, 1, 1, 0, -2941, 2078, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 2941, 2) + POW(`position_y` - 2078, 2)
LIMIT 1;
