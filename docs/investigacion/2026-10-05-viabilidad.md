# Viabilidad: emulador de WoW para la rama Classic

Fecha de consulta de todas las fuentes: **5 de octubre de 2026**.
Elaborado por el orquestador a partir de una investigación delegada, **con verificación
directa de los puntos críticos** (ver §6: el informe delegado contenía errores corregidos aquí).

## 1. La pregunta de partida

Se planteaba si quedarse en **WotLK** o ir a la **última versión** de Classic Era, con la duda
de cómo conseguir el cliente de WotLK Classic. La investigación muestra que la pregunta estaba
mal planteada: los dos extremos son los peores sitios donde situarse, y existe una tercera
opción mucho mejor.

## 2. Estado de los cores (verificado)

| Proyecto | Cliente soportado | Actividad | Sirve para Classic Era |
|---|---|---|---|
| [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk) | WotLK 3.3.5a (12340) | Muy activo | No (es la base ya existente) |
| [TrinityCore](https://github.com/TrinityCore/TrinityCore) `master` | Retail moderno | Muy activo | No |
| TrinityCore rama 3.3.5 | WotLK 3.3.5a | Activo | No |
| [VMaNGOS](https://github.com/vmangos/core) | Vanilla 1.2 – 1.12.1 | Activo (sep. 2026) | Solo con cliente 1.12.1 |
| [CMaNGOS classic](https://github.com/cmangos/mangos-classic) | Vanilla 1.12.1 (5875) | Activo (sep. 2026) | Solo con cliente 1.12.1 |
| [Frostshake/TrinityCoreClassic](https://github.com/Frostshake/TrinityCoreClassic) | **Classic 1.14.0.40618** | Vivo, 25 ★, rama `vanilla_classic` | **Sí, es la vía** |

**Conclusión dura: no existe ningún core open source que soporte el cliente actual de
Classic Era (1.15.x).** Ni uno. Los proyectos serios se quedan en 1.12.1 (MaNGOS) y el único
que habla el protocolo de un cliente *moderno* de Classic llega a **1.14.0**.

## 3. El cliente: aquí está el nudo real

| Versión | Build | Disponibilidad hoy |
|---|---|---|
| Vanilla 1.12.1 | 5875 | No oficial. Custodia comunitaria. Procedencia dudosa. |
| Classic 1.14.x | 40618 y posteriores | No descargable de Battle.net (sustituida) |
| **Classic Era 1.15.9** | ~68824 / 69722 | **Sí, descargable de Battle.net** (requiere suscripción para *jugar* en oficial) |
| WotLK Classic 3.4.x | — | **Retirado por Blizzard.** No descargable. |

Dos consecuencias importantes:

1. **WotLK Classic queda descartado por la propia razón que planteabas**: Blizzard retiró el
   cliente, no hay forma legítima de obtenerlo. (Ojo: WotLK Classic 3.4.x no es lo mismo que
   el 3.3.5a build 12340 de AzerothCore, que es el WotLK *original* de 2010.)
2. **Lo que puedes descargar hoy (1.15.9) es precisamente lo que ningún core soporta.** El
   cliente disponible y el software disponible no coinciden. Ese es el problema central del
   proyecto.

## 4. Piezas de infraestructura que sí existen

La organización [wowemulation-dev](https://github.com/wowemulation-dev) **no tiene ningún core
de Classic** (su único servidor es `wooly-beast`, de Cataclysm 4.4.2), pero sí publica las dos
herramientas sin las que un cliente moderno de Classic no puede conectar a un servidor propio:

- **[wow-patcher](https://github.com/wowemulation-dev/wow-patcher)** (Rust, 27 ★): redirige el
  cliente fuera de la infraestructura de Blizzard, sustituye la clave RSA de 256 bytes que
  valida el Certificate Bundle y reescribe las URL de certificados. Builds **verificados:
  1.13.x, 1.14.x, 2.5.x, 3.4.x, 4.4.x** — **1.15.x no figura como verificado**.
- **[tavern](https://github.com/wowemulation-dev/tavern)** (Rust, 28 ★): reemplazo de los
  servicios de cuenta de Battle.net para clientes Classic.
- **[warcraft-rs](https://github.com/wowemulation-dev/warcraft-rs)** (63 ★): lectura y
  conversión de formatos de archivo del cliente, útil para la extracción de datos.

Requisito nada trivial del patcher: hace falta un **certificado TLS válido que encadene con una
CA de confianza del sistema, y un nombre de host** (no una IP).

## 5. Hasta dónde se puede llegar: respuesta sincera

### Opción A — Cliente 1.14.x sobre Frostshake/TrinityCoreClassic  ← recomendada

Es la única combinación donde core y cliente ya se hablan, y encaja con tu experiencia previa
(TrinityCore y AzerothCore comparten linaje, así que el código te resultará familiar).

- **Viabilidad: alta.** Hay base de la que partir.
- **Riesgos reales:** el fork tiene 25 estrellas y un solo mantenedor principal — si se
  abandona, lo heredamos nosotros. Y hay que conseguir un cliente 1.14.x, que ya no se
  distribuye oficialmente.

### Opción B — Cliente 1.12.1 sobre CMaNGOS o VMaNGOS

La vía más madura y estable de todas, con bases de datos y comunidad reales.

- **Viabilidad: muy alta.** Es un camino trillado desde hace 15 años.
- **Pero:** no es «Classic Era», es vanilla de 2006. Y el cliente 1.12.1 solo existe por
  custodia comunitaria, con procedencia que no podemos verificar.

### Opción C — Cliente 1.15.9 actual (lo que pedías)

- **Viabilidad: baja a medio plazo, y no es un proyecto de fin de semana.** Supondría portar
  el protocolo de 1.14.0 a 1.15.9 sin sniffs públicos, extender el patcher a un build no
  verificado y asumir que cada parche de Blizzard rompe el trabajo. Es un proyecto de
  ingeniería inversa de meses, no una integración.
- Es honesto decirlo claro: **con 1.15.9 no se llega a un servidor jugable en un plazo
  razonable** partiendo de cero.

### Mi recomendación

**Opción A, con el 1.12.1 (B) como red de seguridad.** Empezar por 1.14.x da un servidor
funcionando de verdad y, de paso, construye exactamente el conocimiento (protocolo, patcher,
extracción) que haría falta para intentar 1.15.x más adelante. Ir directo a 1.15.9 es empezar
por la parte más difícil sin haber validado nada.

### Sobre pagar una suscripción

**Todavía no.** Una suscripción sirve para *jugar* en los servidores de Blizzard; descargar el
cliente de Classic Era no requiere jugar en ellos, y en cualquier caso el cliente 1.15.9 es el
que menos nos sirve ahora mismo. Si en el futuro se intentara la opción C, una cuenta activa
sería útil para capturar tráfico del protocolo real (sniffing) — y esa sí sería una razón
concreta para pagarla. Se decidirá entonces, con el motivo por escrito.

### Sobre la versión «forever»

Fuera de alcance, como acordamos. Pero conviene saber que la opción A es la que deja mejor
preparado el terreno, porque el trabajo de protocolo y de patcher es el mismo tipo de trabajo.

## 6. Correcciones al informe delegado

Por transparencia, errores del ejecutor que la verificación directa descartó:

- Afirmaba que `wowemulation-dev` «promete cobertura 1.15.x». **Falso**: no hay ninguna
  referencia a 1.15.x en sus repositorios, y su único core es de Cataclysm 4.4.2.
- Daba por hecho que los extractores funcionan «en general» con 1.15.x. **No verificado**, y
  el propio informe se contradecía al admitirlo después.
- Mezclaba WotLK Classic 3.4.x con WotLK 3.3.5a build 12340 (son cosas distintas).
- Incluía el cierre judicial de Turtle WoW y Everlook con fechas y detalles de sentencia que
  **no he verificado**; no los uso para ninguna decisión. Si resultaran ciertos, serían un
  recordatorio de que un servidor con contenido propio y público atrae atención legal — razón
  más para que esto sea un servidor privado de estudio.

## 7. Incertidumbres pendientes (honestas)

1. Build exacto del cliente Classic Era actual: las fuentes dan 68824 y 69722 para 1.15.9.
   Sin resolver, y **solo se resuelve mirando un cliente real**.
2. Magnitud real del salto de protocolo 1.14.0 → 1.15.9. **Desconocida.** Es la incógnita que
   decide si la opción C es viable algún día.
3. Si los extractores de datos funcionan con clientes 1.14.x/1.15.x o solo con 1.12.1.
4. Procedencia legítima de un cliente 1.14.x. **Es el bloqueante práctico de la opción A** y
   debería ser lo primero que se investigue.
5. Vitalidad real de Frostshake/TrinityCoreClassic (fecha del último commit sin confirmar).

## 8. Siguiente paso propuesto

No escribir código todavía. Resolver primero, por este orden:

1. **Procedencia del cliente** (incertidumbre 4): sin cliente no hay proyecto, y determina
   A vs. B. Es la decisión que bloquea todo lo demás.
2. Clonar `Frostshake/TrinityCoreClassic`, `cmangos/mangos-classic` y `wow-patcher` en
   `upstream/` y auditar de verdad su estado (commits, build, compilabilidad).
3. Registrar la decisión de core y cliente en `docs/decisiones/`.
