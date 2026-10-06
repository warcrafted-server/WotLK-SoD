-- esES locales for mod-sod-content world entries.

REPLACE INTO `creature_template_locale`
    (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`)
VALUES
    (211653, 'esES', 'Grizzby', '', 0),
    (212261, 'esES', 'Liche despertado', '', 0),
    (213077, 'esES', 'Elaine Compton', 'Oficial de suministros', 0),
    (214070, 'esES', 'Jornah', 'Oficial de suministros', 0),
    (214096, 'esES', 'Dokimi', 'Oficial de suministros', 0),
    (214098, 'esES', 'Gishah', 'Oficial de suministros', 0),
    (214099, 'esES', 'Tamelyn Aldridge', 'Oficial de suministros', 0),
    (214101, 'esES', 'Marcy Baker', 'Oficial de suministros', 0),
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
    (701102, 'esES', 'Cristal arcano', '', 0);

REPLACE INTO `creature_text_locale`
    (`CreatureID`, `GroupID`, `ID`, `Locale`, `Text`)
VALUES
    (700210, 0, 0, 'esES', '¡He vuelto a ser quien era! ¡Gracias, héroe!');

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
     'Lleva un envío de suministros a un oficial de suministros.', '', '', '', '', '', '', 0);

REPLACE INTO `quest_request_items_locale`
    (`ID`, `locale`, `CompletionText`, `VerifiedBuild`)
VALUES
    (78612, 'esES', '¿Tienes algo para mí?', 0),
    (79103, 'esES', '¿Tienes algo para mí?', 0),
    (80309, 'esES', '¿Tienes algo para mí?', 0),
    (82309, 'esES', '¿Tienes algo para mí?', 0);

REPLACE INTO `quest_offer_reward_locale`
    (`ID`, `locale`, `RewardText`, `VerifiedBuild`)
VALUES
    (78612, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (79103, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (80309, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0),
    (82309, 'esES', '¡Todo está en orden! Gracias, $N. Estos suministros son esenciales para el frente.', 0);
