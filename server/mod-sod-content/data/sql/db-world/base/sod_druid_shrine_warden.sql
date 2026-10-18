-- mod-sod-druid: Santuario del Celador (Shrine of the Warden, 441948), parte B
-- de la fuente real de Floración (7009022). La lógica va en
-- src/druid/spell_sod_druid_shrine_warden.cpp; aquí solo van los dos hechizos
-- propios que necesita.
--
-- Los santuarios, las plantillas de los avatares y de los espíritus, la misión
-- 81924 y los spawns los creó la parte A en sod_druid_efflorescence_source.sql:
-- este fichero NO los toca.
--
-- Mecánica (misiones.md §3, Feralas):
--   1. Interactuar con el santuario con 81924 activa aplica «Duty of the
--      Warden» (446448).
--   2. Curarse una maldición y un veneno con Duty activo lo transforma en
--      «Mark of the Warden» (446467).
--   3. Con Mark, acercarse al santuario (o interactuar de nuevo) invoca al
--      Treant Avatar (221935); al morir deja a Blightbark (222705) 60 s.
--   La lógica de los pasos 1 a 3 es del C++.
--
-- Los dos hechizos son auras propias sin efecto de combate: un APPLY_AURA con
-- SPELL_AURA_DUMMY sobre el lanzador, para que solo sirvan de marca. Los
-- índices (CastingTimeIndex 1 = instantáneo, RangeIndex 1 = propio,
-- DurationIndex 30 = 1800000 ms, SpellIconID de SpellIcon.dbc) se han
-- comprobado contra los DBC del cliente. La duración real de SoD no consta.
--
-- OJO (mantenimiento): sod_content_spell_dbc.sql se GENERA con
-- tools/sod_spells_druid.py y tools/sod-data/regenerar_sql_hechizos.sh. Estas
-- dos filas se escriben a mano aquí porque esta tarea no toca el generador;
-- mientras sigan aquí, no se deben añadir también al .py. Para que el cliente
-- muestre el nombre y el icono de los buffs hace falta, además, añadirlos al
-- .py y regenerar el parche de cliente. Sin ese parche el servidor aplica las
-- auras pero el cliente no conoce los hechizos.
--
-- Idempotente: REPLACE y sin DELETE, como el resto del módulo.

REPLACE INTO `spell_dbc`
    (`ID`, `Attributes`, `CastingTimeIndex`, `SpellLevel`, `DurationIndex`,
     `PowerType`, `ManaCost`, `RangeIndex`,
     `Effect_1`, `Effect_2`, `Effect_3`,
     `EffectBasePoints_1`,
     `ImplicitTargetA_1`, `ImplicitTargetA_2`, `ImplicitTargetA_3`,
     `EffectAura_1`, `EffectAura_2`, `EffectAura_3`, `EffectAuraPeriod_1`,
     `SpellIconID`, `Name_Lang_enUS`, `Name_Lang_Mask`, `ManaCostPct`, `SchoolMask`)
VALUES
    -- Duty of the Warden: buff que da el santuario al interactuar.
    (446448, 0, 1, 0, 30,
     0, 0, 1,
     6, 0, 0,
     0,
     1, 0, 0,
     4, 0, 0, 0,
     10, 'Duty of the Warden', 16712190, 0, 8),
    -- Mark of the Warden: el Duty transformado tras curarse maldición y veneno.
    (446467, 0, 1, 0, 30,
     0, 0, 1,
     6, 0, 0,
     0,
     1, 0, 0,
     4, 0, 0, 0,
     2013, 'Mark of the Warden', 16712190, 0, 8);
