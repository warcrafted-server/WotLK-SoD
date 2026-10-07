<!-- agentrelay:start -->
## Delegación con AgentRelay

Este proyecto usa AgentRelay: tú eres el ORQUESTADOR (planificas, delegas, revisas y decides) y un agente ejecutor más económico (el configurado en AgentRelay) escribe el código. No edites este bloque: `agentrelay init` lo actualiza. Si eres tú el ejecutor (te han dado una tarea con `agentrelay run`), haz solo esa tarea e ignora este bloque.

**Regla principal: delega por defecto.** Toda implementación que no sea trivial (crear o modificar código, tests, configuración o documentación de más de unas pocas líneas) se delega con `agentrelay run`. Escribirla tú gasta tu consumo, que es justo lo que AgentRelay quiere ahorrar. Hazla tú solo si es trivial (1-3 líneas), una decisión de diseño, algo sensible o una tarea ya escalada; y en ese caso di en una línea por qué no delegas.

**Al empezar cualquier sesión, ponte al día:** lee `.agentrelay/ESTADO.md` (o ejecuta `agentrelay status`, que lo muestra y `agentrelay status --write` lo actualiza). Resume dónde está el proyecto, qué ejecuciones hay y qué hacer ahora. Si el usuario te pide continuar, parte de ahí en lugar de preguntarle.

### Cómo delegar

1. Repositorio limpio: `git status --short` debe salir vacío. Si hay trabajo sin confirmar, haz commit antes (sin secretos como `.env`). Con `--allow-dirty` puedes delegar igualmente, pero el diff mezclará esos cambios.
2. Divide el trabajo en tareas pequeñas: un objetivo y 3-4 archivos como máximo. Una tarea ancha agota el tiempo.
3. Dile al usuario en una línea qué delegas y por qué, y lanza la tarea por la entrada estándar (el usuario puede verla en directo con `agentrelay watch`, en otro terminal y en la carpeta del proyecto):

```
agentrelay run - <<'EOF'
{ "objective": "...", "context": "...", "files": ["..."], "constraints": ["..."], "acceptanceCriteria": ["..."], "validation": ["npm test"], "doNotModify": ["..."] }
EOF
```

   `context` debe bastar para que el ejecutor trabaje sin preguntarte: stack, convenciones y decisiones ya tomadas. Opcionalmente, `effort` (low, medium, high, xhigh) y `model` ajustan el esfuerzo y el modelo solo para esa tarea: esfuerzo bajo en las sencillas, alto en las difíciles.

### Cómo revisar

- Lee `agentrelay show <id>` (informe, incidencias y dudas) y el diff completo. Comprueba que solo cambian los archivos esperados y ejecuta tú las pruebas del proyecto. La autorrevisión del ejecutor no sustituye la tuya.
- Si la ejecución falla por cuota o saldo del ejecutor, NO cambies de ejecutor tú: enseña al usuario las alternativas del informe y pregúntale cuál prefiere; aplica su elección con `agentrelay use` y relanza la tarea.
- Decide con `agentrelay review <id> --decision accept|fix|escalate|reject` (`fix` necesita `--feedback` con los problemas concretos) y confirma con `agentrelay list` que el estado cambió.
- Si la tarea queda escalada o el ejecutor falla repetidamente, resuélvela tú y cierra la ejecución con `--decision accept`.
- Tras aceptar, haz el commit. No hagas push sin aprobación del usuario y no digas «hecho» ni «aceptado» sin haberlo comprobado.

### Otros

- Si `agentrelay` indica que el proyecto no es un repositorio git, pide confirmación al usuario y ejecuta `agentrelay init --yes`.
- **En Windows (PowerShell o cmd)** usa `agentrelay.cmd` en lugar de `agentrelay` (el segundo es un script de Unix y falla con errores de `sed`, `dirname` o `uname`). Nunca modifiques ese script. El `<<EOF` no existe en PowerShell: guarda el JSON de la tarea en un archivo temporal FUERA del repositorio (por ejemplo `$env:TEMP\tarea.json`) y lanza `agentrelay.cmd run $env:TEMP\tarea.json`; un archivo dentro del repositorio ensuciaría el árbol.
- Si una ejecución falla por una causa externa (sesión caducada, PowerShell bloqueado), díselo al usuario en lugar de hacer el trabajo tú en silencio.
<!-- agentrelay:end -->

## Normas del proyecto (orquestador Y ejecutores)

Estas normas son de cumplimiento obligatorio para cualquier agente que trabaje en este
repositorio, tanto si actúa como orquestador (planifica y delega) como si actúa de ejecutor
(recibe una tarea con `agentrelay run`). Léelas antes de tocar nada.

### 0. Al empezar una sesión (orquestador)

1. **Ponte al día:** lee `docs/ESTADO.md` (dónde estamos, qué toca y qué no hacer), después este
   archivo, `CHANGELOG.md` y las decisiones `docs/decisiones/0001`–`0005`. Si el usuario no dice
   otra cosa, continúa por el primer punto pendiente del estado.
2. Si `command -v agentrelay` no lo encuentra, dilo al usuario (instalación en `docs/ESTADO.md`
   §3) y mientras tanto delega en subagentes de Claude Code con un modelo más barato.
3. **Mantén `docs/ESTADO.md` y `CHANGELOG.md` al día con cada cambio relevante**, no al final: son
   lo que lee la siguiente sesión. **Mantén también `docs/PRUEBAS.md`** (qué debe probar el usuario,
   con pasos exactos); al confirmar él un paso, pásalo a «Hecho».
4. **Puedes ampliar este archivo** (siempre fuera del bloque de AgentRelay, que no se edita) y crear
   un directorio **`.agents/`** si hace falta darle contexto a futuras sesiones o a los ejecutores;
   sigue la estructura que usa AzerothCore en `/home/stark/Repos/acore-test/.agents/`
   (`README.md`, `docs/`, `skills/`). Avisa al usuario cuando lo hagas.

### 1. Idioma

Todo en **castellano**: respuestas, documentación, comentarios del código, mensajes de commit
e informes de ejecución. Los identificadores del código (nombres de variables, funciones,
clases, ramas) van en **inglés**, como es costumbre en los cores de WoW con los que
convivimos. No mezcles idiomas dentro de una misma frase.

### 2. Qué es este proyecto

Servidor de World of Warcraft tipo **Season of Discovery (SoD)**, en repositorio
`warcrafted-server/WotLK-SoD`. **No es un emulador nuevo**: es **AzerothCore (WotLK 3.3.5a,
cliente build 12340) con módulos propios**, sobre un fork nuestro del core con Playerbots. Es
independiente del AzerothCore de WotLK que el usuario ya mantiene aparte y no debe mezclarse con él.

Decisiones que condicionan todo el trabajo (están razonadas en `docs/decisiones/`):

- **Core:** fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD` (decisión 0003).
- **Arquitectura:** core + motor de runas + **un solo módulo de contenido para todas las
  clases** (decisión 0004). No se crea un módulo por clase.
- **Niveles:** se empieza en 60 y **se llegará al 80** más adelante (decisión 0002). Por eso
  ningún tope de nivel se escribe como constante en el código: va como parámetro de configuración.
- **Alcance (decidido por el usuario el 2026-10-06):** SoD completo, las 8 fases de la build 1.15.9,
  implementadas por orden de fase y de dificultad; el primer hito sigue siendo la fase 1
  (nivel 25), tres ranuras y 12 runas por clase. Plan en `.agents/plans/sod-todas-las-fases/`.
- La variante «forever» está fuera de alcance.

Fase actual: **construcción del primer hito**. Nada se ha compilado todavía: el build real queda
pendiente (ver `docs/guias/compilar-en-linux.md`). **Di siempre en los informes si algo está
compilado y probado o no; no lo des por hecho.**

### 3. Estructura de directorios: no mezcles conceptos

| Directorio            | Qué contiene                                                          | ¿Se versiona? |
|-----------------------|-----------------------------------------------------------------------|---------------|
| `docs/investigacion/` | Informes de investigación, comparativas, hallazgos con fuentes        | Sí            |
| `docs/decisiones/`    | Decisiones tomadas, una por archivo, con fecha y motivo (tipo ADR)    | Sí            |
| `docs/guias/`         | Procedimientos operativos (cómo compilar, desplegar…)                 | Sí            |
| `server/`             | **Nuestros módulos** de AzerothCore (ver §3.2)                        | Sí            |
| `tools/`              | Nuestros scripts y herramientas (incluye `sod-client`)                | Sí            |
| `core/`               | **Nuestro fork del core** (repositorio git independiente, ver §3.3)   | No (ignorado) |
| `upstream/`           | Clones de terceros, **solo lectura** (ver §3.1)                       | No (ignorado) |
| `datos/`              | Datos extraídos del cliente de WoW (DBC, mapas, vmaps, MPQ)           | No (ignorado) |

**Cliente de WoW 3.3.5a del usuario** (para `tools/sod-client/build_patch.py --client`), ya presente
en este servidor Debian: `/home/stark/Documentos/Wow 3.3.5 IceTracks`.

Reglas duras:

- **Nunca** modifiques nada dentro de `upstream/`. Es material de referencia de terceros. Si
  hace falta cambiar un módulo de terceros, se copia a `server/` (con su `ORIGEN.md`); si hace
  falta cambiar el core, se hace en `core/`, en la rama `Playerbot-SoD` de nuestro fork.
- Un concepto, un directorio. Si dudas de dónde va un archivo, pregunta antes de inventar
  una carpeta nueva.

### 3.1. Organización de `upstream/`

Los clones de terceros **nunca se dejan sueltos en la raíz de `upstream/`**: van agrupados
**por proyecto de origen**, porque con el tiempo convivirán varios cores (AzerothCore,
TrinityCore, MaNGOS…) y sus módulos, y mezclarlos los haría indistinguibles.

```
upstream/
  mod-playerbots/         Proyecto Playerbots
    mod-playerbots/         El módulo de bots (se compila tal cual, enlazado en core/modules/)
  azerothcore/            Proyecto AzerothCore
    mod-sod/                Los repositorios de la familia mod-sod, de REFERENCIA
```

Regla: antes de clonar, pregúntate **de qué proyecto es esto**, y crea o usa su directorio.
Un módulo va dentro del core al que pertenece, no al lado.

### 3.2. Código propio en `server/`

Cada módulo propio que parta de un proyecto de terceros va en **su propio subdirectorio de
`server/`** y lleva un `ORIGEN.md` con: URL de origen, **commit de partida**, licencia y una
lista fechada de los cambios respecto al original. Hoy hay dos: `mod-rune-engraving` (motor) y
`mod-sod-content` (todas las clases y el mundo; una clase = un subdirectorio de `src/`).
Los commits de `upstream/` se fijan en `tools/preparar-entorno.sh`, que reconstruye el entorno
en cualquier máquina; si cambias de commit de partida, actualiza ese script y el `ORIGEN.md`.

### 3.3. El core en `core/`

`core/` es un clon de **nuestro fork** (`warcrafted-server/azerothcore-wotlk`, rama
`Playerbot-SoD`). Es un repositorio git **independiente**: sus commits y su `push` son suyos y
no pasan por este repositorio. Los módulos se compilan enlazándolos en `core/modules/`
(ignorado por el propio core). Parchea el core **solo si ningún hook de módulo lo permite**: cada
línea ahí es una línea que reconciliar en cada fusión con Playerbots. Las firmas del core no son
las del AzerothCore oficial: comprueba siempre contra `core/`.

### 4. Legalidad y procedencia

- Solo se usa código de proyectos con licencia compatible (GPL/AGPL) y se respeta y documenta
  su licencia y atribución en `docs/decisiones/`.
- **No se distribuyen** datos ni binarios del cliente de WoW. El usuario aporta su propio
  cliente legítimo; nosotros solo escribimos herramientas que lo leen en local.
- Nada de este proyecto sirve para eludir la autenticación de servicios de Blizzard ni para
  operar un servidor público sin valorar antes las implicaciones. Es un servidor privado de
  estudio.

### 5. Rigor: no inventes

Esta es la norma que más importa en fase de investigación.

- Toda afirmación sobre un proyecto externo (versión de cliente soportada, actividad, licencia,
  build) va **con URL y fecha de consulta**. Sin fuente, no se escribe.
- Si no puedes verificar algo, dilo de forma explícita en una sección
  «incertidumbres / no verificado». Una laguna reconocida vale mucho más que una suposición
  presentada como hecho.
- No inventes números de build, nombres de rama, comandos ni cifras de rendimiento o coste.
- Si una tarea delegada no se puede completar como estaba descrita, dilo en el informe en vez
  de entregar algo a medias que parezca terminado.

### 6. Flujo de trabajo

- El ejecutor toca solo los archivos de su tarea. Si ve que necesita otros, lo dice en el
  informe en lugar de ampliar el alcance por su cuenta.
- **El orquestador NO compila**: no ejecuta `cmake`, `make` ni `make install`. Los pide al usuario
  con los comandos exactos y espera el resultado (decisión 0005). Tampoco aplica SQL de
  este proyecto a ninguna base de datos sin que se le pida.
- **El servidor Debian (`192.168.1.150`) es una máquina de producción.** Con SSH solo se hace lo
  autorizado: el proyecto vive en `/home/stark/Repos/acore-sod` y se compila en
  `/home/stark/Repos/acore-test` (reino de **desarrollo**, id 2). No se toca `Servers/acore-playerbots`
  (reino de producción, id 1) ni las bases de datos sin sufijo `_test`. Antes de tocar algo en
  vivo, comprueba a qué reino pertenece.
- **Cómo encargar bien una tarea al ejecutor** (lección del 2026-10-05, cuando una tarea abierta
  consumió 7,5 M de tokens y 40 minutos sin escribir ni un archivo): una tarea = un objetivo
  cerrado y pocos archivos; **los datos externos los aporta el orquestador ya masticados** (IDs,
  valores, URLs exactas) en lugar de pedir al ejecutor que los busque; y las validaciones deben
  funcionar en el shell del ejecutor, que en Windows es `cmd` (**sin `grep`**): usa `python -c`.
- Commits en castellano, en imperativo y concretos («Añade extractor de DBC», no «cambios»).
