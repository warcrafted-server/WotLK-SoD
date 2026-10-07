-- Generic rune item requirement strings in English and Spanish (Spain).
REPLACE INTO `module_string` (`module`, `id`, `string`) VALUES
('mod-rune-engraving', 300, 'You have completed the objective: {}.'),
('mod-rune-engraving', 301, 'You still need to complete: {} ({}/{}).'),
('mod-rune-engraving', 302, 'Rune item requirements:'),
('mod-rune-engraving', 303, '  Item {}: {} / {}'),
('mod-rune-engraving', 304, 'You have no rune items with requirements.'),
('mod-rune-engraving', 305, 'Requirement for item {} marked complete.'),
('mod-rune-engraving', 306, 'Progress for item {} reset.'),
('mod-rune-engraving', 307, 'Item {} has no requirement.');

REPLACE INTO `module_string_locale` (`module`, `id`, `locale`, `string`) VALUES
('mod-rune-engraving', 300, 'esES', 'Has completado el objetivo: {}.'),
('mod-rune-engraving', 301, 'esES', 'Todavía tienes que completar: {} ({}/{}).'),
('mod-rune-engraving', 302, 'esES', 'Requisitos de los objetos-runa:'),
('mod-rune-engraving', 303, 'esES', '  Objeto {}: {} / {}'),
('mod-rune-engraving', 304, 'esES', 'No tienes objetos-runa con requisitos.'),
('mod-rune-engraving', 305, 'esES', 'Se ha completado el requisito del objeto {}.'),
('mod-rune-engraving', 306, 'esES', 'Se ha reiniciado el progreso del objeto {}.'),
('mod-rune-engraving', 307, 'esES', 'El objeto {} no tiene ningún requisito.');
