-- Spanish (Spain) rune names and descriptions. This file sorts before the schema file,
-- so it also creates the table idempotently before inserting its optional locale rows.
CREATE TABLE IF NOT EXISTS `rune_template_locale` (
    `rune_id`     INT UNSIGNED NOT NULL,
    `locale`      ENUM('koKR','frFR','deDE','zhCN','zhTW','esES','esMX','ruRU') NOT NULL,
    `name`        VARCHAR(255) NOT NULL,
    `description` TEXT NOT NULL,
    PRIMARY KEY (`rune_id`, `locale`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

REPLACE INTO `rune_template_locale` (`rune_id`, `locale`, `name`, `description`) VALUES
(7000001, 'esES', 'Regeneración', 'Una sanación canalizada en el tiempo que aplica Baliza temporal al objetivo.'),
(7000002, 'esES', 'Regeneración en masa', 'Una sanación canalizada en el tiempo que aplica Baliza temporal a los aliados cercanos.'),
(7000003, 'esES', 'Llama viva', 'Invoca una llama de Piroarcano que avanza hacia el objetivo e inflige daño de Fuego y Arcano a los enemigos cercanos.'),
(7000004, 'esES', 'Esclarecimiento', 'Infliges un 10% más de daño mientras tienes más del 70% de maná; por debajo del 30% de maná, el 10% de tu regeneración de maná continúa mientras lanzas hechizos.'),
(7000005, 'esES', 'Oleada Arcana', 'Libera todo el maná que te queda para infligir daño Arcano según el maná consumido y, después, aumenta considerablemente tu regeneración de maná durante 8 s.'),
(7000006, 'esES', 'Explosión Arcana', 'Te otorga Explosión Arcana (como Estallido Arcano) hasta que puedas aprender el hechizo real a nivel 64; después, te otorga Vórtice abisal, que hace que Explosión Arcana ralentice a su objetivo.'),
(7000007, 'esES', 'Retroceder en el tiempo', 'Sana al instante a un aliado con tu Baliza temporal por todo el daño que haya recibido en los últimos 5 s. No tiene efecto si la baliza se aplicó hace menos de 5 s.'),
(7000008, 'esES', 'Bomba viva', 'Te otorga Chispa viva (una explosión retardada que no genera amenaza) hasta que aprendas Bomba viva; después, Bomba viva también se beneficia de todos los talentos y efectos que se activan con Abrasar o lo modifican.'),
(7000009, 'esES', 'Dedos de Escarcha', 'Tus efectos de ralentización tienen un 25% de probabilidad de otorgarte Dedos de Escarcha, que hace que tus 2 siguientes hechizos traten al objetivo como si estuviera congelado.'),
(7000010, 'esES', 'Consunción', 'Aumenta un 15% tu probabilidad de golpe crítico con todos los hechizos, pero los golpes críticos no periódicos de tus hechizos cuestan un 1% adicional de tu maná base.'),
(7000011, 'esES', 'Venas heladas', 'Acelera el lanzamiento de tus hechizos, aumenta un 20% tu velocidad de lanzamiento y reduce un 100% el retroceso sufrido por los ataques dañinos durante 20 s.'),
(7000012, 'esES', 'Lanza de hielo', 'Inflige daño de Escarcha a un enemigo. Inflige el triple de daño a los objetivos congelados.'),
(7001001, 'esES', 'Devastar', 'Mientras estés en Actitud defensiva y lleves un escudo, Hender armadura también inflige daño. Devastar genera una gran cantidad de amenaza mientras estás en Actitud defensiva.'),
(7002001, 'esES', 'Tormenta divina', 'Un ataque instantáneo con arma que inflige daño a los enemigos cercanos. También sana a los miembros de tu grupo o banda una parte del daño causado.'),
(7002002, 'esES', 'Escudo de vengador', 'Lanza un escudo sagrado contra un enemigo, le inflige daño Sagrado y lo marea antes de rebotar hacia los enemigos cercanos.'),
(7002003, 'esES', 'Maestría en auras', 'Hace que los objetivos afectados por tu Aura de concentración sean inmunes a los efectos de Silencio e interrupción y mejora el efecto de tus otras auras.'),
(7002004, 'esES', 'Golpe de cruzado', 'Un golpe instantáneo que inflige daño con arma como daño Sagrado y regenera maná. Renueva la duración de todos los efectos de Sentencia sobre el objetivo.'),
(7003001, 'esES', 'Disparo de quimera', 'Infliges daño con arma, renuevas el Aguijón activo sobre tu objetivo y activas un efecto.'),
(7003002, 'esES', 'Maestro tirador', 'Aumenta un 5% tu probabilidad de golpe crítico y reduce un 25% el coste de maná de todas tus facultades de Disparo.'),
(7004001, 'esES', 'Mutilar', 'Ataca al instante con ambas armas e inflige su daño más daño adicional con cada una. El daño aumenta contra objetivos envenenados y otorga puntos de combo.'),
(7005001, 'esES', 'Círculo de sanación', 'Sana a todos los miembros del grupo del jugador objetivo que estén cerca de él.'),
(7005002, 'esES', 'Penitencia', 'Lanza una descarga de luz sagrada contra el objetivo, que inflige daño a un enemigo o sana a un aliado.'),
(7007001, 'esES', 'Escudo de tierra', 'Protege al objetivo con un escudo terrenal. Escudo de tierra solo puede estar activo sobre un objetivo a la vez.'),
(7007002, 'esES', 'Latigazo de lava', 'Imbuyes de lava tu arma de mano izquierda e infliges al instante daño con ella. El daño aumenta si está encantada con Lengua de fuego.'),
(7008001, 'esES', 'Descarga de caos', 'Lanza un proyectil de fuego caótico contra el enemigo que inflige daño de Caos.'),
(7008002, 'esES', 'Poseer', 'Libera un alma espectral contra un enemigo, le inflige daño y aumenta todo el daño de las Sombras en el tiempo que le infliges.'),
(7008003, 'esES', 'Tácticas demoníacas', 'Aumenta un 10% tu probabilidad de golpe crítico cuerpo a cuerpo y con hechizos, y la de tu mascota.'),
(7009001, 'esES', 'Crecimiento salvaje', 'Sana a todos los miembros del grupo del jugador objetivo que estén a su alcance. La sanación se aplica con rapidez al principio y se ralentiza hasta completar la duración de Crecimiento salvaje.'),
(7009002, 'esES', 'Supervivencia del más fuerte', 'Reduce un 7% la probabilidad de que recibas golpes críticos cuerpo a cuerpo y reduce un 10% todo el daño recibido.'),
(7009007, 'esES', 'Destrozar', 'Destroza al objetivo y aumenta el daño que recibe de los efectos de sangrado y Triturar.'),
(7009008, 'esES', 'Cornada', 'Tus facultades ferales pueden reiniciar Destrozar (oso) o Furia del tigre y otorgarte ira.'),
(7009009, 'esES', 'Golpes descontrolados', 'Mientras estés en forma felina, forma de oso o forma de oso temible, otorgas Golpes descontrolados a los miembros cercanos de tu grupo o banda.'),
(7009010, 'esES', 'Rey de la selva', 'Furia del tigre te otorga energía y aumenta el daño físico durante un breve periodo.'),
(7009011, 'esES', 'Testarazo', 'Carga contra el objetivo, interrumpe su lanzamiento y bloquea su escuela de magia.'),
(7009012, 'esES', 'Regeneración frenética mejorada', 'Regeneración frenética consume tu recurso activo para sanarte fuera de la forma de lechúcico lunar.'),
(7009013, 'esES', 'Flagelo mejorado', 'En forma felina, Flagelo se convierte en Flagelo (felino); en forma de oso golpea hasta siete enemigos adicionales.');

REPLACE INTO `creature_template_locale` (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`) VALUES
(700000, 'esES', 'Grabador de runas', 'Grabado', 0);
