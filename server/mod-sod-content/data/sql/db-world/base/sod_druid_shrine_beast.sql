-- mod-sod-druid: Santuario de la Bestia (Shrine of the Beast, 441947), parte D
-- de la fuente real de Floración (7009022).
--
-- La lógica va en src/druid/spell_sod_druid_shrine_beast.cpp. Los santuarios, las
-- plantillas de los avatares y de los espíritus, el Child of Apa'ro, el Sacred
-- Stag Heart (221326), la misión 81924 y los spawns los creó la parte A en
-- sod_druid_efflorescence_source.sql: este fichero NO los toca.
--
-- La invocación no necesita ningún hechizo propio: el disparo es la interacción
-- con el santuario (OnGossipHello) teniendo el corazón. Aquí solo va el texto
-- del libro, que el santuario muestra como mensaje del sistema al interactuar
-- sin el corazón (o sin la misión pendiente). Es el texto original de la fuente
-- (misiones.md §3): «Hunt the white stag with tooth and claw.». El C++ del
-- módulo no guarda textos para el jugador (docs/ESTADO.md), así que va en
-- module_string con su fila en esES.
--
-- Idempotente: REPLACE y sin DELETE, como el resto del módulo.

REPLACE INTO `module_string` (`module`, `id`, `string`) VALUES
    ('mod-sod-content', 1011, 'Hunt the white stag with tooth and claw.');

REPLACE INTO `module_string_locale` (`module`, `id`, `locale`, `string`) VALUES
    ('mod-sod-content', 1011, 'esES', 'Caza al venado blanco con dientes y garras.');
