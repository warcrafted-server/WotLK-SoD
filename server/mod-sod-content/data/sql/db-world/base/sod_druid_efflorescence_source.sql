-- mod-sod-druid: fuente real en SoD de la runa Floración (7009022), parte A.
-- La misión «Wisdom of the Guardians» (81924), el PNJ Tyrisius (221985) y TODAS
-- las plantillas (criatura, objeto y objeto de mundo) que usarán los tres
-- santuarios. La lógica de los santuarios NO va aquí: la añaden tareas
-- posteriores con los ScriptName que este fichero deja ya puestos.
--
-- Datos verificados el 2026-10-18 en el tooltip de Wowhead
-- (nether.wowhead.com/classic/tooltip/...) y en la wiki de Warcraft
-- (warcraft.wiki.gg, con ?action=raw); el detalle está en
-- .agents/plans/druida-fuentes/misiones.md §3. Lo que no consta en ninguna
-- fuente va marcado como «no verificado».
--
-- CADENA
--   1. Tyrisius (221985) da 81924 «Wisdom of the Guardians» y la entrega.
--   2. La misión pide matar a los tres avatares: Treant Avatar (221935) en
--      Feralas, Moonkin Avatar (221933) en Tierras del Interior y Hippogryph
--      Avatar (221928) en Azshara.
--   3. Cada avatar lo invoca su santuario (Shrine of the Warden 441948,
--      Shrine of the Moon 441946 y Shrine of the Beast 441947); al morir
--      aparece el espíritu correspondiente (Blightbark 222705, Sagefeather
--      222704 y Whisperwing 222703).
--   4. El santuario de Azshara exige ofrecer el Child of Apa'ro (222580), un
--      ciervo blanco que suelta el Sacred Stag Heart (221326).
--   Todo lo de los pasos 3 y 4 (santuarios, invocación de avatares y
--   espíritus, ofrenda) es de tareas posteriores: esta parte solo deja las
--   plantillas y los ScriptName de los santuarios. Por eso la misión NO es
--   completable todavía (los avatares no tienen spawn ni forma de aparecer).
--
-- PNJ (todos los ids son reales de SoD y están libres en el core)
--   * Tyrisius (221985): nivel 40, humanoide (type 7), facción 35 (amistosa
--     con los dos bandos, como Orokai), civil y no atacable, con npcflag 2
--     (da y entrega misiones), sin vendedor ni entrenador. Un solo spawn en
--     Feralas (mapa 1, (-5564, 1466), 57.2 69 % de Wowhead). Modelo 1542,
--     un elfo de la noche stock (NightElfMale); el de SoD no está
--     verificado.
--   * Treant Avatar (221935), Moonkin Avatar (221933) y Hippogryph Avatar
--     (221928): nivel 50, no élite (el tooltip de Wowhead los da «Normal»),
--     hostiles (facción 14, hostil a todos), sin botín. Son los objetivos de
--     crédito de muerte de 81924. SIN spawn: los invocan los santuarios en
--     tareas posteriores. Tipos 4 (elemental), 7 (humanoide) y 1 (bestia)
--     según misiones.md §3. Modelos stock 18922 (Antárbol/Ent), 12238 y 3210
--     (los de las criaturas homólogas del core, «Treant» y «Vicious
--     Owlbeast» y «Frayfeather Hippogryph»); los de SoD no están
--     verificados.
--   * Blightbark (222705), Sagefeather (222704) y Whisperwing (222703):
--     espíritus élite (rank 1) de nivel 50, neutrales (facción 35), civiles y
--     no atacables. SIN spawn: aparecen al morir su avatar en tareas
--     posteriores. Se les da el mismo tipo y un modelo stock parecido al de
--     su avatar (2077, 12237 y 6757). misiones.md §3 dice que Blightbark dice
--     tres frases, pero NO las transcribe: no se les pone `creature_text`
--     (no se inventa el texto).
--   * Child of Apa'ro (222580): nivel 50, bestia (type 1), hostil (facción
--     14), desollable e inmune a la magia. Un solo spawn en Azshara (mapa 1,
--     (4293, -5458), centro de los 18 puntos de Wowhead; la criatura patrulla
--     y su ruta no se conoce, así que no se inventa), 1800 s de respawn.
--     «Desollable» se implementa con `skinloot` 222580 y una tabla de
--     desuello copiada de «Hakkari Frostwing» (5291, nivel 48-49), la bestia
--     del core más parecida: el botín real de desuello de SoD no consta.
--     «Inmune a la magia» se implementa con `CreatureImmunitiesId` 222580 y
--     una fila de `creature_immunities` con `SchoolMask` 126 (todas las
--     escuelas mágicas, sin la física): así se puede matar a golpes.
--     Modelo 2161 (Stag), un sustituto stock: el pelaje blanco de SoD no está
--     en el DBC; el modelo real no está verificado.
--
-- OBJETOS
--   * Rune of Efflorescence (220360): ya existe en
--     sod_druid_acquisition_balance_resto.sql (BoP, único, ilvl 50, solo
--     druidas, `item_rune_unlock`), con su traducción y su mapeo
--     `rune_item_unlock` → 7009022. NO se toca: el Grabador sigue vendiéndola
--     para las pruebas. Aquí solo se repite el mapeo guardado (idempotente)
--     para que esta fuente sea autosuficiente.
--   * Seed of Renewal (219326): trinket raro, BoP, requiere nivel 50. Se crea
--     el `item_template` con la descripción real y TODAS las estadísticas a 0:
--     no se conoce ninguna, así que NO se le pone efecto ni hechizo. Queda
--     anotado como pendiente (efecto: 40 % de incrustar una semilla en
--     humanoides, bestias o dragonantes golpeados, 2 min de reutilización).
--     Icono 19492 (el del ítem «Seed of Life» del core), sustituto stock.
--   * Sacred Stag Heart (221326): BoP, único, «Present as an offering at the
--     Shrine of the Beast». Lo suelta Child of Apa'ro al 100 %, solo a druidas
--     y solo con 81924 activa (condiciones: clase 1024 y misión tomada).
--     Icono 1438 (INV_Misc_Organ_06, el de «Bat Heart» del core).
--
-- OBJETOS DE MUNDO (santuarios)
--   * Shrine of the Warden (441948, Feralas, mapa 1, (-4785, 1369)),
--     Shrine of the Moon (441946, Tierras del Interior, mapa 0, (104, -4124))
--     y Shrine of the Beast (441947, Azshara, mapa 1, (3685, -5032)).
--     Son objetos interactivos SIN lógica (tipo 10 GOOBER, todos los Data a 0,
--     como el papel de Azora y los Huesos durmientes del módulo: con type 5
--     GENÉRICO el core no los hace clicables ni despacha el GameObjectScript).
--     Lo que pedía el encargo era un «objeto genérico/botón sin lógica», y
--     esto es exactamente eso en este core. Se les deja ya puesto el
--     ScriptName (sod_druid_shrine_warden / _moon / _beast) que implementarán
--     las tareas siguientes; hoy no existe en C++, así que el arranque avisará
--     de que el script no está asignado (no rompe nada).
--     Displays stock: 2048 («NEShrine», santuario kaldorei de Ashenvale) para
--     el del Celador, y 185 («BookLarge02», un libro) para los de la Luna y la
--     Bestia, que misiones.md §3 describe como «libro». Los modelos de SoD no
--     están en 3.3.5a.
--     La z de los tres, como la de todos los spawns del módulo, sale de un
--     INSERT...SELECT del objeto del mismo mapa más cercano en distancia
--     plana; conviene revisarla en juego (`.gobject move`).
--
-- MISIONES
--   * 81924 «Wisdom of the Guardians»: nivel 50, mínimo 45, categoría Druida
--     (QuestSortID -263, la misma de Nutrir), sin misión previa, sin tiempo
--     límite y sin restricción de clase en `AllowableClasses` (las fuentes no
--     la dan; solo consta la categoría). Se da y se entrega en Tyrisius.
--     Tres objetivos de crédito de muerte (los tres avatares, 1 de cada).
--     Recompensa A ELEGIR (ninguna fija): la runa 220360 o el trinket 219326,
--     4700 XP y dinero 0.
--     XP: en AzerothCore sale de QuestXP.dbc por nivel e índice; para nivel 50
--     los valores son 3400 (índice 3) y 5100 (índice 4). Se elige el índice 4
--     (5100 XP, aproximación de +400 sobre los 4700 de la wiki). El dato de
--     dinero (75) no tiene unidad verificada: se deja 0.
--     Textos: descripción, progreso y finalización de misiones.md §3; los
--     `ObjectiveText` 1-3 son los nombres de los tres guardianes. Wowhead llama
--     a la criatura 221935 «Guardian of Feralas» en el objetivo, pero la wiki
--     la llama «Treant Avatar»: se usa el nombre de la wiki en el
--     `creature_template` y el de Wowhead en el texto del objetivo, como en la
--     fuente.
--     Los marcadores <name> y <class> de la fuente se escriben como $N y $C
--     (la sintaxis del cliente). Nutrir los dejó literales; es un error que no
--     se repite aquí.
--
-- IDIOMA: los nombres y textos esES están en sod_content_locale_world_es.sql
-- (PNJ, santuarios y misión) y aquí (objetos), como el resto del módulo.
--
-- Idempotente: REPLACE para plantillas, modelos, inmunidades, botín,
-- desuello, condiciones, objetos, misiones y textos, e INSERT IGNORE para los
-- spawns (nunca pisa una posición ajustada en juego). Sin DELETE.

-- =====================================================================
-- Tyrisius (221985). Nivel 40, humanoide, civil y no atacable, con npcflag 2
-- (da y entrega misiones). Modelo 1542 (un elfo de la noche stock).
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (221985, 'Tyrisius', '',
     40, 40, 35, 2,
     1.0, 1.14286, 0,
     1, 2, 2048, 7, 0,
     '', 0,
     1, 2);

-- =====================================================================
-- Los tres avatares (objetivos de crédito de muerte de 81924). Nivel 50, no
-- élite, hostiles, sin botín. SIN spawn: los invocan los santuarios.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (221935, 'Treant Avatar', '',
     50, 50, 14, 0,
     1.0, 1.14286, 0,
     1, 0, 2048, 4, 0,
     '', 0,
     1, 0),
    (221933, 'Moonkin Avatar', '',
     50, 50, 14, 0,
     1.0, 1.14286, 0,
     1, 0, 2048, 7, 0,
     '', 0,
     1, 0),
    (221928, 'Hippogryph Avatar', '',
     50, 50, 14, 0,
     1.0, 1.14286, 0,
     1, 0, 2048, 1, 0,
     '', 0,
     1, 0);

-- =====================================================================
-- Los tres espíritus. Élite, nivel 50, neutrales, civiles y no atacables.
-- SIN spawn: aparecen al morir su avatar en tareas posteriores. Sin texto:
-- las frases de Blightbark no constan en la fuente.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`, `lootid`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`)
VALUES
    (222705, 'Blightbark', '',
     50, 50, 35, 0,
     1.0, 1.14286, 1,
     1, 2, 2048, 4, 0,
     '', 0,
     1, 2),
    (222704, 'Sagefeather', '',
     50, 50, 35, 0,
     1.0, 1.14286, 1,
     1, 2, 2048, 7, 0,
     '', 0,
     1, 2),
    (222703, 'Whisperwing', '',
     50, 50, 35, 0,
     1.0, 1.14286, 1,
     1, 2, 2048, 1, 0,
     '', 0,
     1, 2);

-- =====================================================================
-- Child of Apa'ro (222580). Nivel 50, bestia, hostil, desollable (skinloot
-- 222580) e inmune a la magia (CreatureImmunitiesId 222580). lootid 222580
-- para que caiga su tabla de botín.
-- =====================================================================
REPLACE INTO `creature_template`
    (`entry`, `name`, `subname`,
     `minlevel`, `maxlevel`, `faction`, `npcflag`,
     `speed_walk`, `speed_run`, `rank`,
     `unit_class`, `unit_flags`, `unit_flags2`, `type`,
     `lootid`, `skinloot`,
     `AIName`, `MovementType`,
     `RegenHealth`, `flags_extra`, `CreatureImmunitiesId`)
VALUES
    (222580, 'Child of Apa''ro', '',
     50, 50, 14, 0,
     1.0, 1.14286, 0,
     1, 0, 2048, 1,
     222580, 222580,
     '', 0,
     1, 0, 222580);

REPLACE INTO `creature_template_model`
    (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`)
VALUES
    (221985, 0, 1542, 1.0, 1.0),
    (221935, 0, 18922, 1.0, 1.0),
    (221933, 0, 12238, 1.0, 1.0),
    (221928, 0, 3210, 1.0, 1.0),
    (222705, 0, 2077, 1.0, 1.0),
    (222704, 0, 12237, 1.0, 1.0),
    (222703, 0, 6757, 1.0, 1.0),
    (222580, 0, 2161, 1.0, 1.0);

-- =====================================================================
-- Inmunidad a la magia del ciervo. SchoolMask 126 = todas las escuelas
-- mágicas (sagrada, fuego, naturaleza, escarcha, sombra y arcano), sin la
-- física: así se puede matar a golpes.
-- =====================================================================
REPLACE INTO `creature_immunities`
    (`ID`, `SchoolMask`, `DispelTypeMask`, `MechanicsMask`, `Effects`, `Auras`, `ImmuneAoE`, `ImmuneChain`, `Comment`)
VALUES
    (222580, 126, 0, 0, '', '', 0, 0, 'mod-sod-druid: Child of Apa''ro immune to magic, not to physical damage');

-- =====================================================================
-- Botín del Child of Apa'ro: Sacred Stag Heart al 100 %, solo a druidas
-- (condición de clase 1024) y solo con 81924 activa (misión tomada, tipo 9).
-- Las dos condiciones van en el mismo ElseGroup y por tanto se exigen juntas.
-- =====================================================================
REPLACE INTO `creature_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (222580, 221326, 0, 100, 0, 1, 0, 1, 1, 'mod-sod-druid Efflorescence sacred stag heart');

REPLACE INTO `conditions`
    (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`,
     `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`,
     `NegativeCondition`, `Comment`) VALUES
    (1, 222580, 221326, 0, 0, 15, 0, 1024, 0, 0, 0, 'mod-sod-druid: Efflorescence heart for class only'),
    (1, 222580, 221326, 0, 0, 9, 0, 81924, 0, 0, 0, 'mod-sod-druid: Efflorescence heart while quest active');

-- =====================================================================
-- Desuello del Child of Apa'ro. Se copia la tabla de «Hakkari Frostwing»
-- (5291, nivel 48-49), la bestia del core más parecida; el botín de desuello
-- real de SoD no consta.
-- =====================================================================
REPLACE INTO `skinning_loot_template`
    (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
    (222580, 4304, 0, 79.6296, 0, 1, 1, 1, 1, 'mod-sod-druid Child of Apa''ro - Thick Leather'),
    (222580, 8169, 0, 2.037, 0, 1, 1, 1, 1, 'mod-sod-druid Child of Apa''ro - Thick Hide'),
    (222580, 8170, 0, 18.3333, 0, 1, 1, 1, 1, 'mod-sod-druid Child of Apa''ro - Rugged Leather');

-- =====================================================================
-- Spawns. La z sale del `creature` del mismo mapa más cercano en distancia
-- plana al punto; `guid` < 8820000 excluye las bandas propias del módulo,
-- para que la z venga siempre de una criatura real del core. Los avatares y
-- los espíritus no tienen spawn: los invocan los santuarios.
-- =====================================================================

-- Tyrisius, Feralas (mapa 1), 300 s de respawn.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820070, 221985, 1, 0, 0, 1, 1, 0, -5564, 1466, `position_z`, 0, 300, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 5564, 2) + POW(`position_y` - 1466, 2)
LIMIT 1;

-- Child of Apa'ro, Azshara (mapa 1), 1800 s de respawn. Los 18 puntos de
-- Wowhead son la misma criatura patrullando: se crea un solo spawn en el
-- centro aproximado y no se inventa la ruta.
INSERT IGNORE INTO `creature`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`,
     `spawntimesecs`, `wander_distance`, `MovementType`)
SELECT 8820071, 222580, 1, 0, 0, 1, 1, 0, 4293, -5458, `position_z`, 0, 1800, 0, 0
FROM `creature`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` - 4293, 2) + POW(`position_y` + 5458, 2)
LIMIT 1;

-- =====================================================================
-- Objetos. La runa 220360 ya existe (no se toca, el Grabador la sigue
-- vendiendo); aquí se crean el trinket y el corazón del ciervo.
-- =====================================================================
REPLACE INTO `item_template`
    (`entry`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`,
     `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`,
     `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`,
     `maxcount`, `stackable`, `bonding`, `Material`, `sheath`,
     `spellid_1`, `spelltrigger_1`, `ScriptName`, `description`, `startquest`)
VALUES
    -- Seed of Renewal: trinket raro, BoP, nivel 50. Estadísticas desconocidas
    -- a 0 y SIN efecto (pendiente): en SoD da un 40 % de incrustar una semilla
    -- y 2 min de reutilización, pero no se ha verificado cómo representarlo.
    (219326, 4, 0, 'Seed of Renewal', 19492, 3, 0,
     1, 0, 0, 12,
     -1, -1, 50, 50,
     0, 1, 1, 1, 0,
     0, 0, '', 'Chance to embed a seed into enemy humanoids, beasts, or dragonkin hit by your abilities or spells. If the creature is slain within 30 seconds, a Healing Blossom will grow from its corpse.', 0),
    -- Sacred Stag Heart: BoP, único, se ofrece en el Santuario de la Bestia.
    (221326, 15, 0, 'Sacred Stag Heart', 1438, 1, 0,
     1, 0, 0, 0,
     -1, -1, 1, 0,
     1, 1, 1, 1, 0,
     0, 0, '', 'Present as an offering at the Shrine of the Beast.', 0);

REPLACE INTO `item_template_locale` (`ID`, `locale`, `Name`, `Description`, `VerifiedBuild`) VALUES
    (219326, 'esES', 'Semilla de renovación', 'Probabilidad de incrustar una semilla en humanoides, bestias o dragonantes enemigos golpeados por tus facultades o hechizos. Si la criatura muere en 30 segundos, de su cadáver brotará una flor sanadora.', 0),
    (221326, 'esES', 'Corazón de venado sagrado', 'Preséntalo como ofrenda en el Santuario de la Bestia.', 0);

-- =====================================================================
-- Misiones. 81924 la da y la entrega Tyrisius, con tres objetivos de crédito
-- de muerte (los tres avatares) y dos recompensas fijas (la runa y el
-- trinket) (ambas se entregan a la vez).
-- =====================================================================
REPLACE INTO `quest_template`
    (`ID`, `QuestType`, `QuestLevel`, `MinLevel`, `QuestSortID`, `QuestInfoID`,
     `SuggestedGroupNum`, `Flags`, `RewardXPDifficulty`, `RewardMoneyDifficulty`,
     `RewardMoney`, `RewardFactionID1`, `RewardFactionOverride1`, `TimeAllowed`,
     `StartItem`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`,
     `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`,
     `RewardItem1`, `RewardAmount1`, `RewardItem2`, `RewardAmount2`,
     `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`,
     `LogTitle`, `LogDescription`, `QuestDescription`)
VALUES
    (81924, 0, 50, 45, -263, 0,
     0, 0, 4, 0,
     0, 0, 0, 0,
     0, 221935, 221933, 221928, 0,
     1, 1, 1, 0,
     220360, 1, 219326, 1,
     'Guardian of Feralas', 'Guardian of the Hinterlands', 'Guardian of Azshara', '',
     'Wisdom of the Guardians',
     '',
     'Whatever Kaldorei knowledge you seek will not be found among these ruins, $C. Not anymore. However, while the physical lies in ruin, the spiritual remains. Seek the guardian spirits of Azshara, the Hinterlands, and Feralas. You will know them by their shrines. Prove yourself to them, and heed their words. Their wisdom will be passed on to you, so that it will not be lost to time as so much was here.');

REPLACE INTO `quest_template_addon`
    (`ID`, `PrevQuestID`)
VALUES
    (81924, 0);

REPLACE INTO `quest_request_items` (`ID`, `CompletionText`) VALUES
    (81924, 'Have the spirits imparted their wisdom unto you?');

REPLACE INTO `quest_offer_reward` (`ID`, `RewardText`) VALUES
    (81924, 'You have proven a dedicated pupil, $N. The work of preserving ancient knowledge is often arduous, but you have taken on the duty admirably. There are many more mysteries in this world for you to uncover. I hope these tools will aid you in that journey.');

REPLACE INTO `creature_queststarter` (`id`, `quest`) VALUES
    (221985, 81924);

REPLACE INTO `creature_questender` (`id`, `quest`) VALUES
    (221985, 81924);

-- =====================================================================
-- Objetos de mundo: los tres santuarios. Tipo 10 GOOBER, sin lógica (todos
-- los Data a 0) y con el ScriptName ya puesto para las tareas siguientes.
-- =====================================================================
REPLACE INTO `gameobject_template`
    (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `size`,
     `ScriptName`)
VALUES
    (441948, 10, 2048, 'Shrine of the Warden', '', '', 1.0, 'sod_druid_shrine_warden'),
    (441946, 10, 185, 'Shrine of the Moon', '', '', 1.0, 'sod_druid_shrine_moon'),
    (441947, 10, 185, 'Shrine of the Beast', '', '', 1.0, 'sod_druid_shrine_beast');

-- Spawns de los santuarios. La z sale del `gameobject` del mismo mapa más
-- cercano en distancia plana, con el mismo criterio que los PNJ.
INSERT IGNORE INTO `gameobject`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `position_x`, `position_y`, `position_z`, `orientation`,
     `rotation0`, `rotation1`, `rotation2`, `rotation3`,
     `spawntimesecs`, `animprogress`, `state`)
SELECT 8821004, 441948, 1, 0, 0, 1, 1,
       -4785, 1369, `position_z`, 0,
       0, 0, 0, 1,
       300, 100, 1
FROM `gameobject`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` + 4785, 2) + POW(`position_y` - 1369, 2)
LIMIT 1;

-- Shrine of the Moon, Tierras del Interior (mapa 0).
INSERT IGNORE INTO `gameobject`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `position_x`, `position_y`, `position_z`, `orientation`,
     `rotation0`, `rotation1`, `rotation2`, `rotation3`,
     `spawntimesecs`, `animprogress`, `state`)
SELECT 8821005, 441946, 0, 0, 0, 1, 1,
       104, -4124, `position_z`, 0,
       0, 0, 0, 1,
       300, 100, 1
FROM `gameobject`
WHERE `map` = 0 AND `guid` < 8820000
ORDER BY POW(`position_x` - 104, 2) + POW(`position_y` + 4124, 2)
LIMIT 1;

-- Shrine of the Beast, Azshara (mapa 1).
INSERT IGNORE INTO `gameobject`
    (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`,
     `position_x`, `position_y`, `position_z`, `orientation`,
     `rotation0`, `rotation1`, `rotation2`, `rotation3`,
     `spawntimesecs`, `animprogress`, `state`)
SELECT 8821006, 441947, 1, 0, 0, 1, 1,
       3685, -5032, `position_z`, 0,
       0, 0, 0, 1,
       300, 100, 1
FROM `gameobject`
WHERE `map` = 1 AND `guid` < 8820000
ORDER BY POW(`position_x` - 3685, 2) + POW(`position_y` + 5032, 2)
LIMIT 1;

-- =====================================================================
-- Mapeo de desbloqueo (protegido): usar la runa 220360 desbloquea Floración
-- (7009022). Ya está en sod_druid_acquisition_balance_resto.sql; se repite
-- aquí, guardado, para que esta fuente sea autosuficiente. La tabla
-- `rune_item_unlock` es del motor; sin él no hace nada.
-- =====================================================================
SET @item_unlock_tbl := (SELECT COUNT(*) FROM information_schema.tables
                         WHERE table_schema = DATABASE() AND table_name = 'rune_item_unlock');
SET @sql := IF(@item_unlock_tbl > 0,
'INSERT INTO `rune_item_unlock` (`item_id`, `rune_id`) VALUES (220360, 7009022) ON DUPLICATE KEY UPDATE `rune_id` = VALUES(`rune_id`)',
'DO 0');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
