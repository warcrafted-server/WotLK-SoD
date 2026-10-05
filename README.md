# WotLK-SoD

Servidor de World of Warcraft tipo **Season of Discovery**: **AzerothCore (WotLK 3.3.5a,
cliente build 12340) con módulos propios**, sobre un fork nuestro del core con Playerbots.
No es un emulador nuevo ni un fork del core con cambios masivos: el contenido de SoD vive en
módulos, y el core solo se parchea cuando ningún módulo puede hacerlo.

> **Estado: primer hito en construcción. Nada se ha compilado todavía.** El build real está
> pendiente; ver [la guía](docs/guias/compilar-en-linux.md). Todo lo que aquí se dice de
> compatibilidad es comprobación estática (cabeceras, firmas, hooks), no un build.

## Qué hay y de dónde sale

| Pieza | Dónde | Origen |
|---|---|---|
| Core | `core/` (fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD`) | AzerothCore → Playerbots |
| Motor de runas | `server/mod-rune-engraving/` | [mod-sod](https://github.com/mod-sod), GPL v3 |
| Contenido (clases y mundo) | `server/mod-sod-content/` | mod-sod-mage + mod-sod-world, GPL v3 |
| Generador del parche de cliente | `tools/sod-client/` | mod-sod, GPL v3 |
| Bots | `upstream/mod-playerbots/` | [mod-playerbots](https://github.com/mod-playerbots/mod-playerbots) |

Cada copia propia lleva un `ORIGEN.md` con su commit de partida y la lista de cambios.

## Estructura

```
docs/investigacion/   Informes con fuentes y fecha de consulta
docs/decisiones/      Decisiones registradas (0001 … 0004), una por archivo
docs/guias/           Procedimientos (compilar en Linux)
server/               Nuestros módulos
tools/                Nuestras herramientas y scripts
core/                 Fork del core: repositorio independiente, no se versiona aquí
upstream/             Clones de terceros, solo lectura, no se versionan
datos/                Datos extraídos del cliente, no se versionan nunca
```

`core/`, `upstream/` y `datos/` no se suben. En una máquina nueva:
`bash tools/preparar-entorno.sh` reconstruye `core/` y `upstream/` con los commits exactos.

## Alcance

Se empieza en **nivel 60 y se llegará al 80** más adelante. SoD completo (8 fases, 218 runas
como mínimo) no es objetivo; el primer hito es la **fase 1 (nivel 25)**: tres ranuras de grabado
y 12 runas por clase. Hoy solo el mago tiene contenido, y le faltan 4 de sus 12 runas
(Fingers of Frost, Burnout, Ice Lance, Icy Veins). Detalle en
[la auditoría](docs/investigacion/2026-10-05-auditoria-mod-sod.md).

**Los jugadores tendrán que instalar un parche de cliente**: el 3.3.5a no puede aprender
hechizos nuevos en tiempo de ejecución.

## Normas

Las normas de trabajo (idioma, estructura, legalidad, rigor con las fuentes y flujo de
delegación) están en [AGENTS.md](AGENTS.md) y valen tanto para el orquestador como para los
ejecutores.

## Lo que este proyecto NO hace

- No distribuye datos ni binarios del cliente de WoW: el cliente lo aporta el usuario.
- No incluye nada para eludir la autenticación de los servicios de Blizzard.
- No diseña por adelantado la variante «forever».

## Licencia

Comprobado en los ficheros el 2026-10-05:

| Componente | `LICENSE` | Cabeceras de los fuentes |
|---|---|---|
| Core (AzerothCore / Playerbots) | GPL v2 | «GPL v2 o posterior» |
| `mod-playerbots` | GPL v2 | «GPL v2 o posterior» |
| Módulos derivados de `mod-sod` | texto de GPL v3 | «GPL v2 o posterior» |

Todos declaran «v2 o posterior» en el código, de modo que pueden combinarse. **Falta decidir y
declarar la licencia del código original de este repositorio**; lo coherente es GPL v2 o
posterior, igual que el resto. Esto es una lectura técnica de los textos, no asesoramiento
legal: conviene confirmarlo antes de hacer público el repositorio.
