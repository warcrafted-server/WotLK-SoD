-- mod-sod-druid: fuente real en SoD de la runa Nutrir (7009027). La cadena de la
-- fase 2 «The Lost Ancient» (79348) y «The Lost Saplings» (79377), con el objeto-runa
-- real 213074 «Rune of Nourishing» como recompensa.
--
-- Datos verificados el 2026-10-18 en el tooltip de Wowhead
-- (nether.wowhead.com/classic/tooltip/...) y en la wiki de Warcraft
-- (warcraft.wiki.gg, con ?action=raw); el detalle está en
-- .agents/plans/druida-fuentes/misiones.md §2. Lo que no consta en ninguna fuente
-- va marcado como «no verificado».
--
-- CADENA
--   1. Rotting Ancient (216310) suelta Rotten Seed (212693), que inicia 79348.
--   2. 79348 «The Lost Ancient» se entrega a Orokai (216289).
--   3. Orokai da 79377 «The Lost Saplings», que entrega el agua de Elune'ara
--      (213036) al aceptarla y recompensa 213074 (desbloquea la runa 7009027).
--
-- PNJ (los tres ids son reales de SoD y están libres en el core)
--   * Rotting Ancient (216310): nivel 40, tipo gigante, no élite, hostil, en The
--     Quagmire (Dustwallow Marsh, mapa 1). Wowhead da 25 puntos de deambulación
--     entre (40–44.2, 30.8–44.8) %: es UNA criatura patrullando; se crea un solo
--     spawn en el centro aproximado (-3521, -3180) y no se inventa la ruta. La
--     facción 14 (hostil a todos) es la de las fieras salvajes de la zona (p. ej.
--     Noxious Reaver 4347). Modelo 5849 (Decaying Treant): sustituto stock, el
--     modelo de SoD no está en 3.3.5a. unit_class 8 porque Wowhead le da maná
--     (lanza Wild Regeneration 7948, que existe en el core); no se le han puesto
--     hechizos de criatura. Respawn 600 s.
--   * Orokai (216289): nivel 62, humanoide, neutral (facción 35, la misma de
--     Grizzby y los intendentes: amistosa con los dos bandos), civil y no
--     atacable, sin vendedor ni entrenador. Un solo spawn en Moonglade (mapa 1).
--     Modelo 1460 (Ancient of Lore, el mismo de la criatura homónima 3468 de
--     Moonglade): la wiki dice que Orokai es un Ancient of Lore, así que el
--     modelo stock encaja; el de SoD no está verificado.
--   * Ancient Sapling (216437 Invierno, 216445 Primavera, 216448 Verano,
--     216451 Otoño): nivel 10, neutral, civil y no atacable, un solo spawn cada
--     uno, en los Reinos del Este (mapa 0). Las coordenadas salen de los puntos
--     de Wowhead convertidos con WorldMapArea.dbc (misiones.md §2); la z no se
--     conoce y la toma del `creature` de mapa 0 más cercano en distancia plana,
--     como el resto de PNJ del módulo: conviene revisarla en juego (`.npc move`).
--     Modelo 9590 (Sapling): sustituto stock, el de SoD no está verificado.
--
-- NOTA sobre 216445 y 216448: la tabla de enlaces de la wiki cruza Primavera y
-- Verano (deja Primavera en Stranglethorn y Verano en Pantano de las Penas), pero
-- el tooltip de Wowhead es explícito: 216445 está en la zona 8 (Pantano de las
-- Penas, 11.2 38.6 %) y 216448 en la zona 33 (Tierra de Estrangulamiento, 32.6
-- 65 %). Se usan los datos de Wowhead, que coinciden con misiones.md.
--
-- OBJETOS
--   * Rotten Seed (212693): clase 15, BoP, único (maxcount 1), nivel 1, nivel
--     requerido 26 (el tooltip de Wowhead no muestra «Requires Level», pero el de
--     la misión es 26; se aplica el del encargo y queda anotado), solo druidas
--     (misma condición de clase 1024 que los demás botines de druida) y
--     `startquest` 79348, que es lo que hace que el cliente muestre «This Item
--     Begins a Quest». Probabilidad de botín NO verificada: se usa el 100 %.
--     Icono inv_misc_herb_nightmareseed (display 37414).
--   * Water of Elune'ara (213036): clase 12 (objeto de misión), BoP, nivel 1, no
--     único, con el texto de sabor real («A delicate globe of water blessed by
--     the ancient Orokai.») y el hechizo 433551 («Give Water», el id real de SoD,
--     1 s de lanzamiento, 5 m, 1 min de reutilización) en `spellid_1`. Se entrega
--     al aceptar 79377 (`StartItem` + `ProvidedItemCount` 1) y desaparece al
--     terminar o fallar la misión; la «duración: 1 hora» del tooltip es el
--     `TimeAllowed` de la misión, no hay campo de duración de objeto en 3.3.5a.
--     Icono inv_elemental_primal_water (display 38622).
--   * Rune of Nourishing (213074): BoP, único, nivel de objeto 40, solo druidas,
--     con el mismo `item_rune_unlock` que las demás runas del módulo. El Grabador
--     sigue vendiendo el ítem propio 7009027 para las pruebas (no se toca).
--     Icono inv_misc_rune_06 (display 20984).
--
-- MECÁNICA DEL AGUA
--   El hechizo 433551 es un efecto DUMMY sobre una criatura amiga (se clona el
--   patrón de «Feed Captured Animal» 29916, un hechizo de objeto de misión de
--   Blizzard que se usa sobre una criatura amiga, para que el cliente acepte al
--   brote como objetivo). El crédito de misión de cada brote lo da
--   src/druid/spell_sod_druid_water_of_eluneara.cpp: en AzerothCore los objetivos
--   de tipo «lanzar sobre criatura» no existen (el objetivo solo avanza con
--   Player::KilledMonsterCredit) y el efecto KILL_CREDIT solo acredita cuando el
--   objetivo del hechizo es un jugador, así que no se puede hacer solo con datos.
--   El hechizo se declara en tools/sod_spells_druid.py (id real de SoD 433551) y
--   su fila de `spell_dbc` la genera sod-client en sod_content_spell_dbc.sql.
--
-- MISIONES
--   * 79348: nivel 40, mínimo 26, categoría Druida (QuestSortID -263, el mismo de
--     las misiones de clase de druida del core). Se inicia con el objeto y se
--     entrega en Orokai. Recompensa 1550 XP de la wiki: en AzerothCore la XP sale
--     de QuestXP.dbc por nivel e índice, y para nivel 40 los valores son 1090
--     (índice 2) y 2150 (índice 3); se elige el índice 2 por ser el más próximo
--     (1090 XP, aproximación de -460). Dinero: la unidad del dato de SoD (50) no
--     está verificada, se deja 0.
--   * 79377: nivel 40, mínimo 26, previa 79348, `TimeAllowed` 3600 s (la misión
--     falla si se agota la hora). Cuatro objetivos (un brote de cada estación),
--     recompensa el objeto 213074 y 3150 XP de la wiki: índice 4 de nivel 40
--     (3250 XP, aproximación de +100). Dinero 0, por lo mismo.
--     `quest_template_addon.SpecialFlags` se deja 0: AzerothCore marca la misión
--     como KILL|CAST|SPEAKTO al ver `RequiredNpcOrGo`, y el crédito entra por la
--     rama KILL de Player::KilledMonsterCredit.
--   Los textos (descripción, objetivos, progreso y finalización) son los de la
--   wiki; el objetivo de 79377 es literal y los `ObjectiveText` por brote salen
--   de la lista de objetivos. El texto de progreso de 79348 no consta en ninguna
--   fuente: no se inventa (no se escribe fila en `quest_request_items`).
--   `AllowableClasses` se deja 0 (sin restricción): las fuentes no lo dan; la
--   restricción efectiva es el objeto de druida y la runa.
--
-- IDIOMA: los nombres y textos esES están en sod_content_locale_world_es.sql
-- (PNJ, texto del brote y misiones) y aquí (objetos), como el resto del módulo.
--
-- Idempotente: REPLACE para plantillas, modelos, botín, condiciones, objetos,
-- misiones y textos, e INSERT IGNORE para los spawns (nunca pisa una posición
-- ajustada en juego). Sin DELETE.

-- =====================================================================
-- Rotting Ancient (216310). Nivel 40, gigante, no élite, hostil, con maná
-- (unit_class 8) y lootid propio para que caiga su tabla de botín.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (216310, 'Rotting Ancient', '',
     40, 40, 14, 0,
     1.0, 1.14286, 0,
     8, 0, 2048, 5, 216310,
     '', 0,
     1, 0);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (216310, 0, 5849, 1.0, 1.0);

-- =====================================================================
-- Orokai (216289). Nivel 62, humanoide, neutral (facción 35), civil y no
-- atacable, sin vendedor ni entrenador. Da y entrega las dos misiones.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (216289, 'Orokai', '',
     62, 62, 35, 2,
     1.0, 1.14286, 0,
     1, 2, 0, 7,
     '', 0,
     1, 2);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (216289, 0, 1460, 1.0, 1.0);

-- =====================================================================
-- Los cuatro Ancient Sapling (216437, 216445, 216448, 216451). Nivel 10,
-- neutral, civil y no atacables. El hechizo del agua les da el crédito de
-- misión y les hace decir su frase desde `creature_text`.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (216437, 'Ancient Sapling', '',
     10, 10, 35, 0,
     1.0, 1.14286, 0,
     1, 2, 0, 4,
     '', 0,
     1, 2),
    (216445, 'Ancient Sapling', '',
     10, 10, 35, 0,
     1.0, 1.14286, 0,
     1, 2, 0, 4,
     '', 0,
     1, 2),
    (216448, 'Ancient Sapling', '',
     10, 10, 35, 0,
     1.0, 1.14286, 0,
     1, 2, 0, 4,
     '', 0,
     1, 2),
    (216451, 'Ancient Sapling', '',
     10, 10, 35, 0,
     1.0, 1.14286, 0,
     1, 2, 0, 4,
     '', 0,
     1, 2);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (216437, 0, 9590, 1.0, 1.0),
    (216445, 0, 9590, 1.0, 1.0),
    (216448, 0, 9590, 1.0, 1.0),
    (216451, 0, 9590, 1.0, 1.0);

-- La frase de los brotes al regarlos (wiki: «Ah...much better. Thank you,
-- druid.»). Grupo 0, id 0, tipo 12 (decir).
REPLACE INTO `creature_text`
    (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`,
     `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`)
VALUES
    (216437, 0, 0, 'Ah...much better. Thank you, druid.', 12, 0, 100, 0, 0, 0, 0, 0, 'mod-sod-druid Ancient Sapling watered'),
    (216445, 0, 0, 'Ah...much better. Thank you, druid.', 12, 0, 100, 0, 0, 0, 0, 0, 'mod-sod-druid Ancient Sapling watered'),
    (216448, 0, 0, 'Ah...much better. Thank you, druid.', 12, 0, 100, 0, 0, 0, 0, 0, 'mod-sod-druid Ancient Sapling watered'),
    (216451, 0, 0, 'Ah...much better. Thank you, druid.', 12, 0, 100, 0, 0, 0, 0, 0, 'mod-sod-druid Ancient Sapling watered');

-- =====================================================================
-- Botín del Rotting Ancient: Rotten Seed al 100 % (probabilidad NO verificada)
-- y solo para druidas, con el mismo mecanismo que los demás botines de runa de
-- druida (condición de clase 1024 en `conditions`).
-- =====================================================================
REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (216310, 212693, 0, 100, 0, 1, 0, 1, 1, 'mod-sod-druid Nourish rune seed');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 216310, 212693, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Nourish seed for class only');

-- =====================================================================
-- Spawns. La z sale del `creature` del mismo mapa más cercano en distancia
-- plana al punto; `guid` < 8820000 excluye la banda de criaturas propias del
-- módulo, para que la z venga siempre de una criatura real del core.
-- =====================================================================

-- Rotting Ancient, The Quagmire (Dustwallow Marsh, mapa 1), 600 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820060, 216310, 1, 0, 0, 1, 1, 0, -3521, -3180, `position_z`, 0, 600, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 3521, 2) + POW(`position_y` + 3180, 2)
LIMIT 1;

-- Orokai, Moonglade (mapa 1), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820061, 216289, 1, 0, 0, 1, 1, 0, 7820, -2342, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` - 7820, 2) + POW(`position_y` + 2342, 2)
LIMIT 1;

-- Winter Sapling, Alterac Mountains (mapa 0), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820062, 216437, 0, 0, 0, 1, 1, 0, 682, -857, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` - 682, 2) + POW(`position_y` + 857, 2)
LIMIT 1;

-- Autumn Sapling, Arathi Highlands (mapa 0), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820063, 216451, 0, 0, 0, 1, 1, 0, -1852, -2551, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` + 1852, 2) + POW(`position_y` + 2551, 2)
LIMIT 1;

-- Spring Sapling, Swamp of Sorrows (mapa 0), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820064, 216445, 0, 0, 0, 1, 1, 0, -10211, -2480, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` + 10211, 2) + POW(`position_y` + 2480, 2)
LIMIT 1;

-- Summer Sapling, Stranglethorn Vale (mapa 0), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820065, 216448, 0, 0, 0, 1, 1, 0, -13934, 141, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` + 13934, 2) + POW(`position_y` - 141, 2)
LIMIT 1;

-- =====================================================================
-- Objetos. El Rotten Seed inicia la misión 79348 con `startquest`; el agua es
-- el objeto que entrega 79377 al aceptarla; la runa desbloquea la 7009027.
-- =====================================================================
REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`, `startquest`)
VALUES
    (212693, 15, 0, 'Rotten Seed', 37414, 1, 0,
     1, 0, 0, 0,
     1024, -1, 1, 26,
     1, 1, 1, 1, 0,
     0, 0, '', '', 79348),
    (213036, 12, 0, 'Water of Elune''ara', 38622, 1, 0,
     1, 0, 0, 0,
     -1, -1, 1, 0,
     0, 1, 1, 1, 0,
     433551, 0, '', 'A delicate globe of water blessed by the ancient Orokai.', 0),
    (213074, 15, 0, 'Rune of Nourishing', 20984, 2, 0,
     1, 10000, 0, 0,
     1024, -1, 40, 1,
     1, 1, 1, 1, 0,
     55884, 0, 'item_rune_unlock', 'Teaches you a new Engraving ability.', 0);

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (212693, 'esES', 'Semilla podrida', '', 0),
    (213036, 'esES', 'Agua de Elune''ara', 'Un delicado globo de agua bendecido por el anciano Orokai.', 0),
    (213074, 'esES', 'Runa de Nutrición', 'Te enseña una nueva facultad de grabado.', 0);

-- =====================================================================
-- Misiones. 79348 se inicia con el objeto y se entrega en Orokai; 79377 la da
-- y la entrega Orokai, con cuatro objetivos (un brote por estación), una hora
-- de tiempo y el objeto-runa como recompensa.
-- =====================================================================
REPLACE INTO `quest_template`
    (`ID`, `QuestType`, `QuestLevel`, `MinLevel`, `QuestSortID`, `QuestInfoID`,
     `SuggestedGroupNum`, `Flags`, `RewardXPDifficulty`, `RewardMoneyDifficulty`,
     `RewardMoney`, `RewardFactionID1`, `RewardFactionOverride1`, `TimeAllowed`,
     `StartItem`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`,
     `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`,
     `RewardItem1`, `RewardAmount1`,
     `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`,
     `LogTitle`, `LogDescription`, `QuestDescription`)
VALUES
    (79348, 0, 40, 26, -263, 0,
     0, 0, 2, 0,
     0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0,
     0, 0,
     '', '', '', '',
     'The Lost Ancient',
     'Find someone who can tell you more about the rotten ancient seed.',
     'A putrid seed is all that remains of the wandering ancient. Its outer coat is brittle, and the insides emit a foul odor. Given its size, the ancient this seed came from must have been fairly young; at least by ancient standards. One has to wonder why such a creature would be found trudging through The Quagmire. To find your answers, you should take this seed to someone with knowledge in the lore of ancients.'),
    (79377, 0, 40, 26, -263, 0,
     0, 0, 4, 0,
     0, 0, 0, 3600,
     213036, 216448, 216445, 216451, 216437,
     1, 1, 1, 1,
     213074, 1,
     'Find Summer Sapling', 'Find Spring Sapling', 'Find Fall Sapling', 'Find Winter Sapling',
     'The Lost Saplings',
     'Find the four lost saplings in Eastern Kingdoms, and share the Water of Elune''ara with them. Afterwards, return to Orokai, in Moonglade.',
     'In times of unrest, seeds may take root in bitter soil. Ancients born this way are prone to corruption. They wander hostile lands; never finding peace. I have sensed four saplings who may be spared such a fate. They are lost among the Eastern Kingdoms, with leaves like that of each season. Please, take this water to them, so that they may be healed. Be warned, the water''s magic is delicate. Teleportation, or falling in battle, will destroy it. Its potency will also fade over time.');

-- 79377 es la continuación de 79348 y entrega el agua al aceptarla
-- (`ProvidedItemCount` 1, que es el `StartItemCount` que lee el core).
REPLACE INTO `quest_template_addon`
    (`ID`, `PrevQuestID`, `ProvidedItemCount`)
VALUES
    (79348, 0, 0),
    (79377, 79348, 1);

REPLACE INTO `quest_request_items` (`ID`, `CompletionText`) VALUES
    (79377, 'Make haste, <name>. My kin may yet be saved.');

REPLACE INTO `quest_offer_reward` (`ID`, `RewardText`) VALUES
    (79348, 'Ah, another lost youngling...'),
    (79377, 'Your deeds have preserved centuries of life, <name>. I am immensely grateful. May you bring yet more healing upon this land in the times to come.');

REPLACE INTO `creature_queststarter` (`id`, `quest`) VALUES
    (216289, 79377);

REPLACE INTO `creature_questender` (`id`, `quest`) VALUES
    (216289, 79348),
    (216289, 79377);

-- =====================================================================
-- Mapeo de desbloqueo (protegido): usar la runa 213074 desbloquea Nutrir
-- (7009027). Es lo que convierte la runa en «gated». La tabla
-- `rune_item_unlock` es del motor; sin él no hace nada.
-- =====================================================================
SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables
                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (213074, 7009027) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
