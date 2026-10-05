# Classic Era — emulador de servidor de WoW (rama Classic)

Proyecto de emulador de servidor de World of Warcraft para la rama **Classic**
(vanilla 1.x / Classic Era), paralelo e independiente del AzerothCore (WotLK 3.3.5a,
build 12340) que se mantiene por separado.

> **Estado: investigación de viabilidad.** Todavía no se escribe código del servidor.
> Antes hay que decidir, con fundamento y por escrito, el core base y la versión de
> cliente objetivo.

## Estructura

```
docs/investigacion/   Informes de investigación con fuentes
docs/decisiones/      Decisiones registradas (una por archivo, con fecha y motivo)
upstream/             Clones de proyectos de terceros — SOLO LECTURA, no se versionan
server/               Nuestro código propio del emulador
tools/                Nuestros scripts de build, extracción y utilidades
datos/                Datos extraídos del cliente — no se versionan nunca
```

## Normas

Las normas de trabajo obligatorias (idioma, estructura, legalidad, rigor en las fuentes
y flujo de delegación) están en [AGENTS.md](AGENTS.md). Son de aplicación tanto para el
agente orquestador como para los ejecutores.

## Lo que este proyecto NO hace

- No distribuye datos ni binarios del cliente de WoW: el cliente lo aporta el usuario.
- No incluye nada para eludir la autenticación de los servicios de Blizzard.
- No diseña por adelantado la futura variante «forever»: está fuera de alcance.
