-- mod-sod-druid: Santuario de la Luna (Shrine of the Moon, 441946), parte C de
-- la fuente real de Floración (7009022).
--
-- La lógica va en src/druid/spell_sod_druid_shrine_moon.cpp. Los santuarios, las
-- plantillas de los avatares y de los espíritus, la misión 81924 y los spawns los
-- creó la parte A en sod_druid_efflorescence_source.sql: este fichero NO los
-- toca.
--
-- Aquí solo va el texto del libro, que el santuario muestra como mensaje del
-- sistema al interactuar sin la misión pendiente. Es el texto original de la
-- fuente (misiones.md §3): «The calm comes before the storm.». El C++ del
-- módulo no guarda textos para el jugador (docs/ESTADO.md), así que va en
-- module_string con su fila en esES.
--
-- Idempotente: REPLACE y sin DELETE, como el resto del módulo.

REPLACE INTO `module_string` (`module`, `id`, `string`) VALUES
    ('mod-sod-content', 1010, 'The calm comes before the storm.');

REPLACE INTO `module_string_locale` (`module`, `id`, `locale`, `string`) VALUES
    ('mod-sod-content', 1010, 'esES', 'La calma precede a la tormenta.');
