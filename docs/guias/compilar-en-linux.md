# Compilar en Linux

**Estado: sin probar.** Nunca se ha compilado este proyecto: la máquina de desarrollo (Windows +
WSL Debian vacío) no tiene toolchain. Los pasos salen de las wikis oficiales, citadas al final;
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

## Fuentes

- [AzerothCore — requisitos en Linux](https://www.azerothcore.org/wiki/linux-requirements)
- [AzerothCore — instalación del core en Linux](https://www.azerothcore.org/wiki/linux-core-installation)
- [mod-playerbots — guía de instalación](https://github.com/mod-playerbots/mod-playerbots/wiki/Installation-Guide)
