# 0001 — Core base y versión de cliente

- **Fecha:** 2026-10-05
- **Estado:** PENDIENTE (a la espera de resolver la procedencia del cliente)

## Contexto

Se quiere un emulador para la rama Classic, paralelo al AzerothCore (WotLK 3.3.5a, build
12340) que ya se mantiene aparte. Ver el análisis completo en
[2026-10-05-viabilidad.md](../investigacion/2026-10-05-viabilidad.md).

El hallazgo que condiciona todo: **ningún core open source soporta el cliente actual de
Classic Era (1.15.x)**, y el cliente de WotLK Classic ya no es descargable.

## Opciones

| Opción | Cliente | Core | Viabilidad |
|---|---|---|---|
| A | Classic 1.14.x | Frostshake/TrinityCoreClassic | Alta — **recomendada** |
| B | Vanilla 1.12.1 | CMaNGOS o VMaNGOS | Muy alta, pero no es Classic Era |
| C | Classic Era 1.15.9 | Ninguno — habría que portarlo | Baja; meses de ingeniería inversa |

## Decisión

Sin tomar. Queda **bloqueada por una única incógnita**: de qué versiones de cliente se puede
disponer por una vía legítima. Es lo que separa A de B, y hasta resolverlo cualquier elección
de core sería arbitraria.

Descartado desde ya: **WotLK Classic 3.4.x**, porque Blizzard retiró el cliente.

## Consecuencias

- No se escribe código del servidor hasta cerrar esta decisión.
- La suscripción a WoW **no se contrata todavía**: solo tendría sentido para capturar tráfico
  del protocolo si algún día se intentara la opción C.
- La variante «forever» sigue fuera de alcance. La opción A es la que mejor prepara el terreno.

## Revisar cuando

Se sepa a qué cliente se puede acceder, o si aparece un core que soporte 1.15.x.
