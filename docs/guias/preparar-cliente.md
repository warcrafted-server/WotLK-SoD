# Preparar el cliente

El cliente 3.3.5a no recibe hechizos, iconos ni interfaz del servidor: cada jugador necesita parche y addon. **Nada de esto se ha ejecutado nunca.**

## Generar el parche

**Cliente necesario:** WoW **3.3.5a, build 12340**, instalación completa (`Data/` con sus MPQ y la carpeta de idioma, p. ej. `Data/enUS/`; el idioma se elige con `--locale`). Python 3 y el cliente cerrado. `pympq` solo existe para Windows: en Linux el generador usa `tools/sod-client/stormlib_shim.py` (ctypes sobre `libstorm`; paquete Debian `libstorm-dev`, ya instalado). Probado el 2026-10-05 solo en lectura y con un MPQ de prueba en `/tmp`; **el MPQ final aún no se ha escrito en un cliente**. `--server` debe contener `modules/` y `data/sql/base/db_world/`.

**`pip install -r requirements.txt` falla en Linux** (comprobado el 2026-10-07): el paquete `pympq` que pide no existe en PyPI para esta plataforma (`ERROR: No matching distribution found for pympq`). No hace falta instalarlo: con `libstorm.so` presente en el sistema (`dpkg -l libstorm9`, ya está en este servidor), `build_patch.py` usa el shim propio automáticamente. No crear un venv solo para esto.

Hay un cliente en este servidor: `/home/stark/Documentos/Wow 3.3.5 IceTracks`; su copia de trabajo está en `datos/cliente-sod/` (20 GB, con `enUS` y `esES`, `Config.wtf` en `esES`, parches propios `patch-A.MPQ`, `patch-2/3.MPQ` y `patch.MPQ`). **Es el del reino de producción**: para SoD usar una copia. Su `Data/esES/realmlist.wtf` ya apunta a `logon.warcrafted.com` y `Config.wtf` está en `esES`.

Alternativa: generar en otra máquina con cliente.

Desde `tools/sod-client/`:

```
pip install -r requirements.txt
python build_patch.py --server <raíz de acore-test> --client "<raíz del cliente>" --locale esES
```

Escribe `Data/patch-z.mpq` y `Data/<locale>/patch-<locale>-z.mpq`, y regenera `server/mod-sod-content/data/sql/db-world/base/sod_content_spell_dbc.sql`. `--dry-run` no escribe el MPQ pero **sí reescribe** el SQL del módulo; ya se ha ejecutado así sobre `datos/cliente-sod/`. Es sin estado: parte siempre del cliente limpio y no modifica los MPQ originales.

## Servidor y parche, a la par

Tras cada hechizo nuevo: regenerar, subir ese SQL, aplicarlo al servidor y redistribuir el MPQ. Un desajuste da hechizos sin icono o sin efecto.

**Causó un crash real (2026-10-07):** se añadieron 5 runas de druida (Starsurge, Efflorescence, Elune's Fires, Eclipse, Starfall) con su código C++ y su spec en `sod_spells_druid.py`, pero sin volver a ejecutar `build_patch.py`. `sod_content_spell_dbc.sql` se quedó con la versión vieja, sin esos `spell_id`; el worldserver no los encontraba en `Spell.dbc`, repetía el aviso sin parar durante el login de 200 bots y el hilo del mundo colgó 20 s (`World Thread hangs ... forcing a crash`). **Regla:** cualquier `spell_id` nuevo en `tools/sod_spells_<clase>.py` exige regenerar este SQL (al menos con `--dry-run`) antes de dar el código por terminado, aunque el servidor no se vaya a probar ese mismo día.

Los clones (`template` en `sod_spells.py`) solo heredan los efectos en el DBC del cliente; en el SQL del servidor hay que pedirlo con `"inherit_server": True` en el spec, o la fila queda sin efectos. Lo llevan 400647, 412286, 425121 y 400640 (comprobado en el SQL generado). Los iconos de las runas están verificados con Wowhead (`ability_mage_wintersgrasp`, `ability_mage_burnout`, `spell_frost_coldhearted`, `spell_frost_frostblast`); falta comprobar que el generador los resuelva en el cliente.

**Idioma:** el cliente del usuario es `esES`, así que se genera con `--locale esES` (el parche va a `Data/esES/patch-esES-z.mpq`); los textos salen de `server/mod-sod-content/tools/sod_spells_es.json`. Sin `--locale` se toma la primera carpeta de idioma (`enUS`).

## Copia de seguridad

Tras generar, guardar aparte, en `datos/parche-cliente/<fecha>-<commit corto>/` (ignorada por git):

- `patch-z.mpq` y `<locale>/patch-<locale>-z.mpq`.
- La carpeta del addon.
- Un `LEEME.txt` con el commit de `acore-sod` del que salen y el `sod_content_spell_dbc.sql` usado.

Si se pierde el cliente: reinstalar uno limpio y copiar esos archivos (cada MPQ en su carpeta y el addon en `Interface/AddOns/`). Si el servidor ya cambió de SQL desde esa copia, regenerar el parche en lugar de reutilizarlo.

## Addon y jugador

- **Addon RuneEngraver** (`https://github.com/mod-sod/RuneEngraver`, MIT, v0.1; clonado en `upstream/azerothcore/mod-sod/RuneEngraver/`, commit `500f57e`): copiar esa carpeta a `Interface/AddOns/RuneEngraver/`. Solo Lua, sin parche; **sin traducción** (textos fijos en inglés). Sin él queda el NPC de grabado. Necesita `Addon.Channel` activo (lo está por defecto).
- `patch-z.mpq` a `Data/` y `patch-<locale>-z.mpq` a `Data/<locale>/`; borrar `Cache/WDB` si ya se jugó antes.
- `realmlist` a `logon.warcrafted.com`; el reino 2 (desarrollo) debe salir en la lista.

## Distribución

No se distribuye un cliente completo ni DBC/MPQ derivados de archivos de Blizzard (`AGENTS.md` §4). A terceros, solo el addon y una herramienta que genere el parche en local desde su cliente (similar al `sod-installer` de mod-sod, MIT, aún sin revisar). **Pendiente de decidir.**
