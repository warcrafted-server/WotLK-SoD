# 0001 — Core base y versión de cliente

- **Fecha:** 2026-10-05
- **Estado:** ACEPTADA — opción D (SoD sobre AzerothCore), con el alcance corregido tras la
  auditoría de `mod-sod`

## Contexto

Se quiere un emulador para la rama Classic, paralelo al AzerothCore (WotLK 3.3.5a, build
12340) que ya se mantiene aparte. Análisis en
[2026-10-05-viabilidad.md](../investigacion/2026-10-05-viabilidad.md) y
[2026-10-05-opcion-sod.md](../investigacion/2026-10-05-opcion-sod.md).

Hallazgo inicial: **ningún core open source soporta el cliente actual de Classic Era (1.15.x)**,
y el cliente de WotLK Classic ya no es descargable. Eso dejaba la decisión bloqueada por la
procedencia del cliente.

**El usuario propuso entonces hacer una Season of Discovery**, y eso disuelve el bloqueante:
SoD se recrea con módulos sobre AzerothCore y **cliente WotLK 3.3.5a build 12340**, el que ya
tiene. No hace falta ningún cliente nuevo.

## Opciones

| Opción | Cliente | Core | Viabilidad |
|---|---|---|---|
| A | Classic 1.14.x | Frostshake/TrinityCoreClassic | Alta, pero cliente de procedencia dudosa |
| B | Vanilla 1.12.1 | CMaNGOS / VMaNGOS | Muy alta; no es Classic Era |
| C | Classic Era 1.15.9 | No existe | Baja; meses de ingeniería inversa |
| **D** | **WotLK 3.3.5a (12340)** | **AzerothCore + [mod-sod](https://github.com/mod-sod)** | **Alta — recomendada** |

## Decisión

**Opción D.** Season of Discovery recreada con los módulos de `mod-sod` sobre AzerothCore.

Motivos: elimina el problema del cliente, reutiliza el core y los conocimientos que ya se
tienen, es aditivo (se conserva el mantenimiento upstream de AzerothCore en lugar de depender de
un fork con pocos mantenedores) y no exige ingeniería inversa de protocolo.

Descartados: **WotLK Classic 3.4.x** (cliente retirado por Blizzard) y la **opción C** (sin core
y con el protocolo 1.14.0 → 1.15.9 sin portar).

Se asume explícitamente que **SoD no es Classic Era fiel**: es contenido propio sobre WotLK.

## Resultado de la auditoría (condición resuelta)

Hecha el 2026-10-05: [2026-10-05-auditoria-mod-sod.md](../investigacion/2026-10-05-auditoria-mod-sod.md).

El contenido **sí estaba casi vacío**, como se temía: de las nueve clases de SoD **solo el mago
tiene contenido** (~11 habilidades, 2.715 líneas); guerrero, druida y chamán son copias
idénticas de la plantilla vacía (31 líneas). El proyecto está **parado desde el 22 de junio de
2026**, con 0 estrellas y 0 forks: hay que asumir su mantenimiento.

Aun así **se mantiene la opción D**, porque lo que se hereda es la parte difícil: un motor de
runas sólido (~2.000 líneas, acoplado por base de datos y no por símbolos, con tests y bandas de
IDs reservadas por clase), el pipeline de parcheo del cliente y un módulo de clase completo como
referencia a imitar.

Obstáculo descubierto en la auditoría: el cliente 3.3.5a **no puede aprender hechizos nuevos en
tiempo de ejecución**, así que cada habilidad son dos mitades sincronizadas (servidor + parche
MPQ del cliente). **Los jugadores tendrán que instalar un parche.**

## Alcance acordado

**No se intenta SoD completo.** Primer hito: **fase 1 (nivel máximo 25) con dos o tres clases**,
partiendo del mago que ya funciona, para validar el pipeline entero antes de comprometer meses.

## Consecuencias

- Cliente objetivo: **WotLK 3.3.5a build 12340**. El mismo del AzerothCore existente, pero este
  proyecto se mantiene **separado** para no contaminarlo.
- Licencias: los módulos de clase son **GPL v3**; `RuneEngraver` y `sod-installer`, MIT. Hay que
  respetar y documentar la atribución.
- La suscripción a WoW **no se contrata**: ya no hay ningún motivo para ello.
- La variante «forever» sigue fuera de alcance.

## Revisar cuando

Termine la auditoría de `mod-sod`, o si `mod-sod` se abandona (habría que asumir su
mantenimiento o rehacer el motor de runas).
