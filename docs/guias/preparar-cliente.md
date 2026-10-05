# Preparar el cliente

El cliente 3.3.5a no recibe hechizos, iconos ni interfaz del servidor: cada jugador necesita parche y addon. **Nada de esto se ha ejecutado nunca.**

## Generar el parche

**Cliente necesario:** WoW **3.3.5a, build 12340**, instalación completa (`Data/` con sus MPQ y la carpeta de idioma, p. ej. `Data/enUS/`; el idioma se elige con `--locale`). Python 3 y el cliente cerrado. `pympq` solo existe para Windows: en Linux el generador usa `tools/sod-client/stormlib_shim.py` (ctypes sobre `libstorm`; paquete Debian `libstorm-dev`, ya instalado). Probado el 2026-10-05 solo en lectura y con un MPQ de prueba en `/tmp`; **el MPQ final aún no se ha escrito en un cliente**. `--server` debe contener `modules/` y `data/sql/base/db_world/`.

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

Los clones (`template` en `sod_spells.py`) solo heredan los efectos en el DBC del cliente; en el SQL del servidor hay que pedirlo con `"inherit_server": True` en el spec, o la fila queda sin efectos. Lo llevan 400647, 412286, 425121 y 400640 (comprobado en el SQL generado). Sin comprobar: los nombres de icono de las runas (`spell_frost_chillingblast`, `spell_fire_burnout`, `spell_frost_coldhearted`, `spell_frost_frostblast`).

**Idioma:** el cliente del usuario es `esES`, así que se genera con `--locale esES` (el parche va a `Data/esES/patch-esES-z.mpq`); los textos salen de `server/mod-sod-content/tools/sod_spells_es.json`. Sin `--locale` se toma la primera carpeta de idioma (`enUS`).

## Copia de seguridad

Tras generar, guardar aparte, en `datos/parche-cliente/<fecha>-<commit corto>/` (ignorada por git):

- `patch-z.mpq` y `<locale>/patch-<locale>-z.mpq`.
- La carpeta del addon.
- Un `LEEME.txt` con el commit de `acore-sod` del que salen y el `sod_content_spell_dbc.sql` usado.

Si se pierde el cliente: reinstalar uno limpio y copiar esos archivos (cada MPQ en su carpeta y el addon en `Interface/AddOns/`). Si el servidor ya cambió de SQL desde esa copia, regenerar el parche en lugar de reutilizarlo.

## Addon y jugador

- **Addon RuneEngraver** (repo propio, MIT; URL sin anotar) en `Interface/AddOns/`. Sin él queda el NPC de grabado. Necesita `Addon.Channel` activo (lo está por defecto).
- `patch-z.mpq` a `Data/` y `patch-<locale>-z.mpq` a `Data/<locale>/`; borrar `Cache/WDB` si ya se jugó antes.
- `realmlist` a `logon.warcrafted.com`; el reino 2 (desarrollo) debe salir en la lista.

## Distribución

No se distribuye un cliente completo ni DBC/MPQ derivados de archivos de Blizzard (`AGENTS.md` §4). A terceros, solo el addon y una herramienta que genere el parche en local desde su cliente (similar al `sod-installer` de mod-sod, MIT, aún sin revisar). **Pendiente de decidir.**
