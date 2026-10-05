# Opción D: Season of Discovery sobre AzerothCore

Fecha de consulta de las fuentes: **5 de octubre de 2026**. Verificado directamente por el
orquestador. Complementa a [2026-10-05-viabilidad.md](2026-10-05-viabilidad.md).

## 1. Por qué esto cambia el análisis

El informe de viabilidad partía de una premisa que SoD rompe: que hacía falta un cliente
*moderno* de Classic y, por tanto, un core que hablara su protocolo (lo que no existe).

**Season of Discovery no se emula con un cliente de SoD.** La vía real que usa la comunidad es
**recrear el contenido de SoD sobre AzerothCore con cliente WotLK 3.3.5a build 12340** — el
mismo que ya dominas. Las runas, los hechizos nuevos y los encuentros se implementan como
módulos del servidor y parches MPQ del cliente, no portando un protocolo nuevo.

Es decir: **el problema del cliente desaparece.** No hay que conseguir un 1.14.x de procedencia
dudosa ni portar el protocolo de 1.15.9. Ya tienes el cliente y ya tienes el core.

## 2. Qué existe: la organización mod-sod

[github.com/mod-sod](https://github.com/mod-sod) — módulos de AzerothCore, **GPL v3**:

| Repositorio | Contenido |
|---|---|
| `mod-rune-engraving` | Motor de grabado de runas, agnóstico de clase. Pieza central. |
| `mod-sod-{mage,warrior,warlock,shaman,rogue,priest,paladin,hunter,druid,deathknight}` | Un módulo por clase, con hechizos y runas |
| `mod-sod-world` | Cambios de mundo (encuentro del Awakened Lich, iconos de objetos) |
| `sod-class-templates` | Plantillas para crear módulos de clase |
| `sod-client` (Python) | Herramientas de cliente |
| `RuneEngraver` (Lua, MIT) | Addon de interfaz para el grabado |
| `sod-installer` (Shell, MIT) | Instalador que clona módulos, construye los MPQ y coloca el addon |

Detalles técnicos verificados:

- `mod-rune-engraving` es **solo de servidor, sin parche de cliente obligatorio**: el addon es
  opcional y hay un NPC de gossip como alternativa. Eso baja mucho la barrera de entrada.
- El motor **no trae runas**: el contenido viene de los módulos de clase. Arquitectura limpia.
- Tiene **pruebas unitarias y documentación de desarrollo** — hay oficio detrás.
- `sod-installer` requiere árbol de AzerothCore, cliente 3.3.5a, Python y `pympq`. No construye
  los MPQ en CI porque necesita los DBC con copyright del cliente.

## 3. La parte incómoda: madurez

Hay que decirlo sin adornos, porque es el riesgo principal:

| Métrica | `mod-rune-engraving` | `sod-installer` |
|---|---|---|
| Estrellas | **0** | **0** |
| Forks | 0 | — |
| Commits | 22 | 16 |
| Incidencias abiertas | 0 | — |

El propio README se describe como **«early / proof of concept»**, aunque afirma que «el motor
funciona de principio a fin» (catálogo, NPC grabador, persistencia).

Traducción honesta: **es un esqueleto bien construido, no un SoD jugable.** Cero estrellas y
cero forks significa que prácticamente nadie lo usa, y que si el mantenedor lo deja, lo
heredamos nosotros enteros. Que haya diez módulos de clase no quiere decir que las diez clases
estén completas; el informe del instalador solo detallaba contenido real del mago.

**Pendiente de verificar:** cuánto contenido tiene de verdad cada módulo de clase. Es la
pregunta que decide si esto ahorra meses o solo semanas. No se resuelve sin clonar y leer.

## 4. Comparación con las opciones anteriores

| Opción | Cliente | Core | ¿Problema de cliente? | Viabilidad |
|---|---|---|---|---|
| A | Classic 1.14.x | Frostshake/TrinityCoreClassic | Sí, procedencia dudosa | Alta |
| B | Vanilla 1.12.1 | CMaNGOS / VMaNGOS | Sí, custodia comunitaria | Muy alta |
| C | Classic Era 1.15.9 | No existe | No, pero no hay core | Baja |
| **D — SoD** | **WotLK 3.3.5a (12340)** | **AzerothCore + mod-sod** | **No. Ya lo tienes.** | **Alta** |

## 5. Valoración

**SoD es la mejor opción de las cuatro, y por bastante margen.** Razones:

1. **Elimina el bloqueante.** La decisión 0001 estaba parada esperando saber a qué cliente se
   podía acceder. Con SoD la pregunta no se plantea: 3.3.5a build 12340, el que ya usas.
2. **Reutiliza todo lo que ya sabes.** AzerothCore, su sistema de módulos, su proceso de build.
   Cero curva de aprendizaje de core nuevo.
3. **Es aditivo, no un fork.** Módulos sobre un AzerothCore estándar: se sigue recibiendo el
   mantenimiento upstream de AzerothCore, que es muy activo. Las opciones A y B obligaban a
   depender de un core entero mantenido por poca gente.
4. **No hay ingeniería inversa de protocolo.** El trabajo es contenido y lógica de juego, que
   es trabajo acotado y delegable; no desensamblar un cliente.

El riesgo no es técnico, es de madurez: hay que asumir que `mod-sod` es un punto de partida y
que buena parte del contenido habrá que escribirlo. Pero **escribir contenido sobre una base que
arranca es un proyecto que termina**; portar un protocolo a 1.15.9 no lo es.

Matiz sobre el objetivo original: SoD **no es** Classic Era. Es contenido propio sobre WotLK. Si
lo que querías era vanilla fiel, esto no lo es. Si lo que querías era un servidor Classic+
interesante y jugable, es mucho mejor sitio donde estar.

Sobre la suscripción: **sigue sin hacer falta**, y ahora con más razón.

## 6. Siguiente paso propuesto

1. Clonar en `upstream/` (solo lectura): `mod-rune-engraving`, `sod-installer`, dos o tres
   módulos de clase y `sod-class-templates`.
2. **Auditar el contenido real** de los módulos de clase: cuántas runas y hechizos hay
   implementados de verdad frente a los de SoD oficial. Esto es lo que decide el alcance, y es
   trabajo mecánico de lectura: delegable.
3. Comprobar que `mod-rune-engraving` compila contra un AzerothCore actual.
4. Con eso, cerrar la decisión 0001 y acotar fases.
