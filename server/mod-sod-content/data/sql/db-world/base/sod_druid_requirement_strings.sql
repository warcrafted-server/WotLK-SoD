-- Druid idol objectives live in the rune-engine module's reserved string band.
REPLACE INTO `module_string` (`module`, `id`, `string`) VALUES
('mod-rune-engraving', 5000, 'Heal 10 different beasts'),
('mod-rune-engraving', 5001, 'Deal 20 instances of bleeding damage to humanoids'),
('mod-rune-engraving', 5002, 'Keep your Rage at 50 or higher in Bear Form for 60 seconds'),
('mod-rune-engraving', 5003, 'Kill 5 enemies with Nature damage while affected by Barkskin'),
('mod-rune-engraving', 5004, 'Kill 5 sleeping targets while in Cat Form');

REPLACE INTO `module_string_locale` (`module`, `id`, `locale`, `string`) VALUES
('mod-rune-engraving', 5000, 'esES', 'Sana a 10 bestias distintas'),
('mod-rune-engraving', 5001, 'esES', 'Inflige daño de sangrado 20 veces a humanoides'),
('mod-rune-engraving', 5002, 'esES', 'Mantén 50 p. de ira o más en forma de oso durante 60 s'),
('mod-rune-engraving', 5003, 'esES', 'Mata a 5 enemigos con daño de Naturaleza mientras te afecta Piel de corteza'),
('mod-rune-engraving', 5004, 'esES', 'Mata a 5 objetivos dormidos en forma felina');
