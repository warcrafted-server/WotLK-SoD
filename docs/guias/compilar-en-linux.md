# Compilar en Linux

**Estado: sin probar.** Nunca se ha compilado este proyecto. La compilación se hace en el servidor
Debian de pruebas (§7); la máquina de desarrollo (Windows + WSL vacío) no tiene toolchain. Los pasos salen de las wikis oficiales, citadas al final;
lo que es criterio propio va señalado como tal. Si algo falla, el error exacto es lo más valioso
que se puede traer de vuelta.

Referencias de ruta: todo se hace desde la raíz de este repositorio, salvo que se indique.

## 1. Requisitos

Según la [wiki de AzerothCore](https://www.azerothcore.org/wiki/linux-requirements):

| Requisito | Mínimo |
|---|---|
| **Clang** | **≥ 18** (o GCC ≥ 15) |
| MySQL | **8.4 LTS** (MySQL 26.x no está soportado) |
| Boost | ≥ 1.74 |
| CMake | ≥ 3.16 |
| OpenSSL | ≥ 3.0 |

⚠️ **El compilador es el primer obstáculo.** Debian 12 trae Clang 14 y no sirve; hace falta una
distribución con Clang 18 o superior. Comprueba antes de nada con `clang --version`. (Que Debian 13
lo traiga es lo que yo recuerdo; no lo he verificado.)

Paquetes (Debian 12 y 13, tal cual los da la wiki):

```bash
sudo apt-get update && sudo apt-get install -y git cmake make gcc g++ clang libssl-dev \
  libbz2-dev libreadline-dev libncurses-dev libboost-all-dev lsb-release gnupg wget screen
```

MySQL 8.4 LTS **no viene en los repositorios de Debian**: hay que instalarlo desde el repositorio
APT de MySQL, como explica la misma wiki.

## 2. Obtener el código

```bash
git clone https://github.com/warcrafted-server/WotLK-SoD.git
cd WotLK-SoD
bash tools/preparar-entorno.sh
```

El script (idempotente, **sin ejecutar aún**) clona nuestro fork del core en `core/` (rama
`Playerbot-SoD`), los proyectos de terceros en `upstream/` a los commits exactos, y enlaza en
`core/modules/` los tres módulos que se compilan: `mod-playerbots`, `mod-rune-engraving` y
`mod-sod-content`.

## 3. Compilar

Opciones tomadas de la
[guía de instalación de AzerothCore](https://www.azerothcore.org/wiki/linux-core-installation):

```bash
cd core && mkdir -p build && cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=$PWD/../env/dist/ \
  -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
  -DWITH_WARNINGS=1 -DTOOLS_BUILD=all -DSCRIPTS=static -DMODULES=static
make -j$(( $(nproc) - 1 ))
make install
```

La wiki recomienda `nproc - 1` hilos. **Criterio propio, sin verificar:** el compilador puede
gastar más de 1 GB por hilo, así que con poca RAM conviene bajar ese número a la mitad antes que
dejar que el sistema empiece a usar swap.

Hay que repetir los tres pasos cada vez que se actualiza el core o se añade un módulo.

## 4. Bases de datos

Según la [guía de instalación de Playerbots](https://github.com/mod-playerbots/mod-playerbots/wiki/Installation-Guide):

```sql
CREATE DATABASE IF NOT EXISTS acore_playerbots;
GRANT ALL PRIVILEGES ON acore_playerbots.* TO 'acore'@'localhost';
FLUSH PRIVILEGES;
```

Y el SQL del módulo de bots sobre `acore_characters` y `acore_world`
(`core/modules/mod-playerbots/data/sql/{characters,world}/base/*.sql`). Sin la base
`acore_playerbots` el servidor da errores de tablas.

El SQL de nuestro módulo de contenido está en `server/mod-sod-content/data/sql/db-world/base/`.
**Lo que no está comprobado** es si el importador automático de AzerothCore lo aplica solo o
hay que aplicarlo a mano (el README original del módulo de mago lo aplicaba a mano, archivo a
archivo); empieza aplicándolo a mano.

## 5. Datos del cliente

Hace falta el **cliente 3.3.5a (build 12340)**. Con `-DTOOLS_BUILD=all` se compilan los
extractores de DBC, mapas, vmaps y mmaps. Playerbots avisa de que el servidor debe usar los
**DBC en enUS**. Los datos extraídos van a `datos/` o al directorio de datos del servidor, nunca
al repositorio.

## 6. Parche de cliente de las runas (pendiente)

Los hechizos de SoD no existen en el cliente 3.3.5a, así que hay un parche MPQ que generar con
`tools/sod-client/build_patch.py` (necesita `pip install pympq` y el cliente). **No se ha
ejecutado con la estructura nueva**: ver [decisión 0004](../decisiones/0004-arquitectura-de-modulos.md).
Los jugadores tendrán que instalarlo.

## 7. Pasos concretos en el servidor `warcrafted`

Aplica la [decisión 0005](../decisiones/0005-entorno-de-pruebas-en-debian.md). **Instalación nueva
del reino de desarrollo, hecha por el usuario**; el orquestador no borra ni compila.

Ya preparado: `acore-sod` clonado con `core/` y `upstream/`; `acore-test` en la rama
`Playerbot-SoD`, con los módulos `mod-rune-engraving` y `mod-sod-content` enlazados en `modules/`.
El servidor cumple los requisitos (Debian 13, Clang 19, MySQL 8.4, CMake 3.31).

Cosas que **no se deben tocar** al limpiar: `acore_auth` (compartida con producción, con la fila
del reino 2), las bases sin sufijo `_test`, `Servers/acore-playerbots`, y de `Servers/acore-test`
conservar `data/` (3,1 GB de datos del cliente) y `etc/` (configuración).

**1. Bases de datos vacías** (las tres del reino 2). Según la wiki de Playerbots, la de bots hay
que crearla a mano o aparecen errores de tablas; las otras puede crearlas el importador de
AzerothCore si el usuario tiene permiso (no verificado aquí). Con el mismo usuario que ya usa el
reino 2 en `worldserver.conf`:

```sql
CREATE DATABASE IF NOT EXISTS acore_world_test      DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE DATABASE IF NOT EXISTS acore_characters_test DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE DATABASE IF NOT EXISTS acore_playerbots_test DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
-- GRANT ALL PRIVILEGES ON acore_<...>_test.* TO '<usuario>'@'localhost';  (si hiciera falta)
```

**2. Configurar.** El `build/` anterior tenía estas opciones, leídas de su `CMakeCache.txt` antes
de que desaparezca: `CMAKE_INSTALL_PREFIX=/home/stark/Servers/acore-test`, compilador
`/usr/bin/clang++`, `CMAKE_BUILD_TYPE=RelWithDebInfo`, `APPS_BUILD=all`, `TOOLS_BUILD=all`,
`SCRIPTS=static`, `MODULES=static`. (El compilador de C no figuraba; se usa `clang`, en
coherencia con la guía de AzerothCore.)

```bash
cd /home/stark/Repos/acore-test && mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/home/stark/Servers/acore-test   -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++   -DCMAKE_BUILD_TYPE=RelWithDebInfo -DAPPS_BUILD=all -DTOOLS_BUILD=all   -DSCRIPTS=static -DMODULES=static
```

**3. Compilar**, con poca prioridad para no perjudicar al reino en producción:

```bash
nice -n 19 make -j3 2>&1 | tee ~/sod-build.log
```

`-j3` es criterio propio, sin verificar: la máquina tiene 4 núcleos y 15 GB de RAM y sirve un
reino en vivo; con 3 hilos queda un núcleo libre. Si falla por memoria, bájalo a 2.

**4. Instalar**, solo si compila sin errores y con el worldserver de **desarrollo** parado:
`make install`.

Si algo falla, lo más útil es el **primer error**: `grep -n "error:" ~/sod-build.log | head`.

**No se aplica SQL de SoD todavía.** Primero se compila y se comprueba que el servidor arranca; el
orden y las guardas del SQL se preparan juntos después.

## Fuentes

- [AzerothCore — requisitos en Linux](https://www.azerothcore.org/wiki/linux-requirements)
- [AzerothCore — instalación del core en Linux](https://www.azerothcore.org/wiki/linux-core-installation)
- [mod-playerbots — guía de instalación](https://github.com/mod-playerbots/mod-playerbots/wiki/Installation-Guide)
