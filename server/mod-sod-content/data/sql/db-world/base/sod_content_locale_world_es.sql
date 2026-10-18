-- esES locales for mod-sod-content world entries.

REPLACE INTO `creature_template_locale`
    (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`)
VALUES
    (206245, 'esES', 'Espíritu de la naturaleza desatado', '', 0),
    (211653, 'esES', 'Grizzby', '', 0),
    (212261, 'esES', 'Liche despertado', '', 0),
    (213077, 'esES', 'Elaine Compton', 'Oficial de suministros', 0),
    (214070, 'esES', 'Jornah', 'Oficial de suministros', 0),
    (214096, 'esES', 'Dokimi', 'Oficial de suministros', 0),
    (214098, 'esES', 'Gishah', 'Oficial de suministros', 0),
    (214099, 'esES', 'Tamelyn Aldridge', 'Oficial de suministros', 0),
    (214101, 'esES', 'Marcy Baker', 'Oficial de suministros', 0),
    (216289, 'esES', 'Orokai', '', 0),
    (216310, 'esES', 'Anciano podrido', '', 0),
    (216437, 'esES', 'Retoño anciano', '', 0),
    (216445, 'esES', 'Retoño anciano', '', 0),
    (216448, 'esES', 'Retoño anciano', '', 0),
    (216451, 'esES', 'Retoño anciano', '', 0),
    (221928, 'esES', 'Avatar hipogrifo', '', 0),
    (221933, 'esES', 'Avatar lechubestia', '', 0),
    (221935, 'esES', 'Avatar Antárbol', '', 0),
    (221985, 'esES', 'Tyrisius', '', 0),
    (222286, 'esES', 'Namida Tótem Siniestro', '', 0),
    (222580, 'esES', 'Hijo de Apa''ro', '', 0),
    (222684, 'esES', 'Falinar', 'Intendente', 0),
    (222685, 'esES', 'Kyleen', 'Intendente', 0),
    (222686, 'esES', 'Alandra', 'Intendente', 0),
    (222687, 'esES', 'Valdane', 'Intendente', 0),
    (222703, 'esES', 'Whisperwing', '', 0),
    (222704, 'esES', 'Sagefeather', '', 0),
    (222705, 'esES', 'Blightbark', '', 0),
    (228814, 'esES', 'Arcterris', '', 0),
    (700200, 'esES', 'Llama viviente', '', 0),
    (700210, 'esES', 'Aprendiz polimorfado', '', 0);

REPLACE INTO `gameobject_template_locale`
    (`entry`, `locale`, `name`, `castBarCaption`, `VerifiedBuild`)
VALUES
    (411348, 'esES', 'Cofre polvoriento', '', 0),
    (700220, 'esES', 'Notas del aprendiz de Azora', '', 0),
    (701000, 'esES', 'Trono de piedra roto', '', 0),
    (701001, 'esES', 'Huesos durmientes', '', 0),
    (701100, 'esES', 'Cristal arcano', '', 0),
    (701101, 'esES', 'Cristal arcano', '', 0),
    (701102, 'esES', 'Cristal arcano', '', 0),
    (441946, 'esES', 'Santuario de la Luna', '', 0),
    (441947, 'esES', 'Santuario de la Bestia', '', 0),
    (441948, 'esES', 'Santuario del celador', '', 0);

REPLACE INTO `creature_text_locale`
    (`CreatureID`, `GroupID`, `ID`, `Locale`, `Text`)
VALUES
    (700210, 0, 0, 'esES', '¡He vuelto a ser quien era! ¡Gracias, héroe!'),
    (216437, 0, 0, 'esES', 'Ah... mucho mejor. Gracias, druida.'),
    (216445, 0, 0, 'esES', 'Ah... mucho mejor. Gracias, druida.'),
    (216448, 0, 0, 'esES', 'Ah... mucho mejor. Gracias, druida.'),
    (216451, 0, 0, 'esES', 'Ah... mucho mejor. Gracias, druida.');

REPLACE INTO `quest_template_locale`
    (`ID`, `locale`, `Title`, `Details`, `Objectives`, `EndText`, `CompletedText`,
     `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `VerifiedBuild`)
VALUES
    (78612, 'esES', 'Un envío completo',
     'Entrega un envío de suministros a un oficial de suministros a cambio de una generosa recompensa.',
     'Lleva un envío de suministros a un oficial de suministros.', '', '', '', '', '', '', 0),
    (79103, 'esES', 'Un envío completo',
     'Entrega un envío de suministros a un oficial de suministros a cambio de una generosa recompensa.',
     'Lleva un envío de suministros a un oficial de suministros.', '', '', '', '', '', '', 0),
    (80309, 'esES', 'Un envío completo',
     'Entrega un envío de suministros a un oficial de suministros a cambio de una generosa recompensa.',
     'Lleva un envío de suministros a un oficial de suministros.', '', '', '', '', '', '', 0),
    (82309, 'esES', 'Un envío completo',
     'Entrega un envío de suministros a un oficial de suministros a cambio de una generosa recompensa.',
     'Lleva un envío de suministros a un oficial de suministros.', '', '', '', '', '', '', 0),
    (79348, 'esES', 'El anciano perdido',
     'Una semilla pútrida es lo único que queda del anciano errante. Su corteza exterior es quebradiza y su interior desprende un hedor fétido. Por su tamaño, el anciano del que proviene esta semilla debía de ser bastante joven; al menos según los criterios de los ancianos. Cabe preguntarse por qué una criatura así andaría recorriendo El Cenagal. Para hallar tus respuestas, deberías llevar esta semilla a alguien que conozca la sabiduría de los ancianos.',
     'Encuentra a alguien que pueda contarte más sobre la semilla del anciano podrido.', '', '', '', '', '', '', 0),
    (79377, 'esES', 'Los retoños perdidos',
     'En tiempos de inquietud, las semillas pueden echar raíces en tierra amarga. Los ancianos que nacen así son propensos a la corrupción. Vagabundean por tierras hostiles sin encontrar nunca la paz. He percibido a cuatro retoños que podrían librarse de ese destino. Están perdidos por los Reinos del Este, con hojas como las de cada estación. Por favor, llévales esta agua para que puedan sanar. Te advierto que la magia del agua es delicada. El teletransporte, o caer en combate, la destruirán. Su potencia también se desvanecerá con el tiempo.',
     'Encuentra a los cuatro retoños perdidos en los Reinos del Este y comparte con ellos el Agua de Elune''ara. Después, vuelve con Orokai, en Claro de la Luna.',
     '', '', 'Encuentra el retoño de verano', 'Encuentra el retoño de primavera',
     'Encuentra el retoño de otoño', 'Encuentra el retoño de invierno', 0),
    (81924, 'esES', 'La sabiduría de los guardianes',
     'Cualquier conocimiento kaldorei que busques no lo encontrarás entre estas ruinas, $C. Ya no. Sin embargo, aunque lo físico yace en ruinas, lo espiritual permanece. Busca a los espíritus guardianes de Azshara, las Tierras del Interior y Feralas. Los reconocerás por sus santuarios. Demuéstrales tu valía y escucha sus palabras. Su sabiduría se te transmitirá para que no se pierda con el tiempo como tantas otras cosas de aquí.',
     '', '', '', 'Guardián de Feralas', 'Guardián de las Tierras del Interior',
     'Guardián de Azshara', '', 0);

REPLACE INTO `quest_request_items_locale`
    (`ID`, `locale`, `CompletionText`, `VerifiedBuild`)
VALUES
    (78612, 'esES', '¿Tienes algo para mí?', 0),
    (79103, 'esES', '¿Tienes algo para mí?', 0),
    (80309, 'esES', '¿Tienes algo para mí?', 0),
    (82309, 'esES', '¿Tienes algo para mí?', 0),
    (79377, 'esES', 'Date prisa, <name>. Puede que mi estirpe aún pueda salvarse.', 0),
    (81924, 'esES', '¿Te han transmitido los espíritus su sabiduría?', 0);

REPLACE INTO `quest_offer_reward_locale`
    (`ID`, `locale`, `RewardText`, `VerifiedBuild`)
VALUES
    (78612, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (79103, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (80309, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (82309, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (79348, 'esES', 'Ah, otro joven perdido...', 0),
    (79377, 'esES', 'Tus actos han preservado siglos de vida, <name>. Te estoy enormemente agradecido. Que traigas aún más curación a esta tierra en los tiempos venideros.', 0),
    (81924, 'esES', 'Has demostrado ser un alumno entregado, $N. La labor de preservar el conocimiento antiguo a menudo es ardua, pero has asumido ese deber admirablemente. Hay muchos más misterios en este mundo que desvelar. Espero que estas herramientas te ayuden en ese viaje.', 0);
