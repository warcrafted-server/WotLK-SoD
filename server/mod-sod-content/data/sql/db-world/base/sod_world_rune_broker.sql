-- mod-sod-world: el Corredor de runas (Rune Broker), vendedor de runas de las capitales.
--
-- En SoD el Rune Broker es el vendedor de runas que hay en cada capital. Desde la
-- fase 6 las vende a 1 cobre (lo dice una guía de 2024; su URL no está en el
-- repositorio). Aquí se cobra 1 oro por decisión del usuario. Este fichero crea UN solo `creature_template` para las seis
-- capitales y seis spawns, uno por capital, a unas 4 yardas del oficial de
-- suministros de esa ciudad (sod_world_supply_officers.sql): mismas map/x/y/z que
-- el oficial, +4 en x, para no inventar altura.
--
-- Stock: por decisión del usuario, hoy el Corredor solo vende las runas de las que
-- no tenemos otra fuente real, es decir, Rabia (Rune of Berserk, 213117) y
-- Regeneración frenética mejorada (Rune of Primal Energy, 221516). Las demás se
-- irán añadiendo clase a clase: cada clase mete sus propias filas de `npc_vendor`
-- con el entry del Corredor (700201) en su SQL, con REPLACE INTO, sin tocar este
-- fichero ni la plantilla.
--
-- Precio: un vendedor cobra el `BuyPrice` del ítem (este core no tiene gancho de
-- precio por vendedor), así que los dos cuestan 1 oro (10000 cobre) en
-- sod_druid_acquisition.sql, decisión del usuario. Wowhead recoge el coste de Rune of
-- Berserk como «1» y, para Rune of Primal Energy, pide 1 unidad del ítem 232454
-- (Emblem of the Wild Gods) y ningún cobre; esa contradicción queda sin resolver y el
-- ítem 232454 no existe en este core.
--
-- Creature 700201, libre en la banda propia del módulo (700200-700299; usados como
-- criaturas solo 700200 y 700210). Nivel 60, el que da Wowhead para los dos Rune
-- Broker que lista (233335 y 233428). Facción 35 (amistosa con los dos bandos, la
-- misma del Grabador), npcflag 128 (vendedor), no atacable (unit_flags 2), civil
-- (flags_extra 2), humanoide (type 7), subnombre vacío y sin ScriptName: el core
-- abre la ventana de mercader con las filas de `npc_vendor`.
--
-- Modelo 7099: el mercader goblin stock de Ranik, el mismo que usa Grizzby en este
-- módulo. Se elige porque los mercaderes neutrales de las seis capitales ya son
-- goblins (los subastadores), así que el mismo modelo vale para los dos bandos, y
-- porque es un display stock (el cliente HD rompe con displays propios sin hornear).
-- El modelo real de SoD no está en 3.3.5a: es un sustituto, no una copia.
--
-- Idempotente: REPLACE para plantilla, modelo, locale y stock; INSERT IGNORE para
-- los spawns (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- El vendedor. El locale esES va aquí, con la plantilla, para que el fichero sea
-- autosuficiente; el resto de locales de mundo del módulo siguen en
-- sod_content_locale_world_es.sql.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `flags_extra`,
     `ScriptName`)
VALUES
    (700201, 'Rune Broker', NULL, 60, 60, 35, 128, 1.0, 1.14286, 1, 2, 0, 7, 2, '');

REPLACE INTO `creature_template_locale`
    (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`)
VALUES
    (700201, 'esES', 'Corredor de runas', '', 0);

-- Modelo stock 7099 (mercader goblin, el de Grizzby).
REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (700201, 0, 7099, 1.0, 1.0);

-- Stock de hoy: las dos runas sin otra fuente real. Sin `maxcount` ni
-- reabastecimiento (`incrtime`), como el resto de vendedores del módulo.
REPLACE INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
    (700201, 0, 213117, 0, 0, 0),
    (700201, 0, 221516, 0, 0, 0);

-- =====================================================================
-- Spawns, uno por capital: coordenadas del oficial de suministros de esa ciudad
-- (sod_world_supply_officers.sql) con +4 en x, la misma y y la misma z, y la
-- orientación del oficial. 300 s de respawn (no es élite). Guids 8820050-8820055.
-- La posición hay que revisarla en juego (`.npc move`).
-- =====================================================================
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
VALUES
    (8820050, 700201, 0, 0, 0, 1, 1, 0, -8821.063,    649.7763,    94.57176,  4.7048225, 300, 0, 0), -- Stormwind
    (8820051, 700201, 0, 0, 0, 1, 1, 0, -4921.47,    -905.377,    501.66,     5.27789,   300, 0, 0), -- Ironforge
    (8820052, 700201, 1, 0, 0, 1, 1, 0,  9842.5,      2299.63,   1319.82,     1.27235,   300, 0, 0), -- Darnassus
    (8820053, 700201, 1, 0, 0, 1, 1, 0,  1681.4825, -4405.1753,   19.879587, 3.1023214, 300, 0, 0), -- Orgrimmar
    (8820054, 700201, 1, 0, 0, 1, 1, 0, -1218.85,     101.869,   131.966,    4.74774,   300, 0, 0), -- Thunder Bluff
    (8820055, 700201, 0, 0, 0, 1, 1, 0,  1639.27,     252.593,   -43.102,    2.74886,   300, 0, 0); -- Undercity
