<!-- agentrelay:start -->
## Delegación con AgentRelay

Este proyecto usa AgentRelay: tú eres el ORQUESTADOR (planificas, delegas, revisas y decides) y un agente ejecutor más económico (por defecto, Codex con GPT-6 Luna) escribe el código. No edites este bloque: `agentrelay init` lo actualiza. Si eres tú el ejecutor (te han dado una tarea con `agentrelay run`), haz solo esa tarea e ignora este bloque.

**Regla principal: delega por defecto.** Toda implementación que no sea trivial (crear o modificar código, tests, configuración o documentación de más de unas pocas líneas) se delega con `agentrelay run`. Escribirla tú gasta tu consumo, que es justo lo que AgentRelay quiere ahorrar. Hazla tú solo si es trivial (1-3 líneas), una decisión de diseño, algo sensible o una tarea ya escalada; y en ese caso di en una línea por qué no delegas.

**Triaje antes de trabajar:** ante cada orden de trabajo (no ante una simple pregunta), antes de empezar, valora en una línea (3-5 si es de envergadura) qué modelo y esfuerzo de razonamiento necesitas tú como orquestador y compáralo con el que estás usando: si es otro, sugiérelo al usuario (tú no puedes cambiarlo; no compensa a mitad de una conversación corta). Di también qué delegas y con qué esfuerzo lanzarás al ejecutor (campo `effort` de la tarea: bajo en lo sencillo, alto en lo difícil). Criterio: modelo ligero para consultas y cambios mecánicos, intermedio para implementación y depuración normales, el más potente para diseño difícil, depuración sin pistas o revisión crítica; siempre el esfuerzo más bajo que no ponga en riesgo el resultado. No inventes costes ni cifras y respeta el modelo o esfuerzo que el usuario haya fijado.

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
- Tras aceptar, haz el commit. No hagas push sin que el usuario lo pida y no digas «hecho» ni «aceptado» sin haberlo comprobado.

### Otros

- Si `agentrelay` indica que el proyecto no es un repositorio git, pide confirmación al usuario y ejecuta `agentrelay init --yes`.
- **En Windows (PowerShell o cmd)** usa `agentrelay.cmd` en lugar de `agentrelay` (el segundo es un script de Unix y falla con errores de `sed`, `dirname` o `uname`). Nunca modifiques ese script. El `<<EOF` no existe en PowerShell: guarda el JSON de la tarea en un archivo temporal FUERA del repositorio (por ejemplo `$env:TEMP\tarea.json`) y lanza `agentrelay.cmd run $env:TEMP\tarea.json`; un archivo dentro del repositorio ensuciaría el árbol.
- Si una ejecución falla por una causa externa (sesión caducada, PowerShell bloqueado), díselo al usuario en lugar de hacer el trabajo tú en silencio.
<!-- agentrelay:end -->

## Normas del proyecto (orquestador Y ejecutores)

Estas normas son de cumplimiento obligatorio para cualquier agente que trabaje en este
repositorio, tanto si actúa como orquestador (planifica y delega) como si actúa de ejecutor
(recibe una tarea con `agentrelay run`). Léelas antes de tocar nada.

### 1. Idioma

Todo en **castellano**: respuestas, documentación, comentarios del código, mensajes de commit
e informes de ejecución. Los identificadores del código (nombres de variables, funciones,
clases, ramas) van en **inglés**, como es costumbre en los cores de WoW con los que
convivimos. No mezcles idiomas dentro de una misma frase.

### 2. Qué es este proyecto

Emulador de servidor de World of Warcraft para la rama **Classic** (vanilla 1.x / Classic Era),
paralelo e independiente del AzerothCore (WotLK 3.3.5a, build 12340) que ya se mantiene aparte.
En el futuro podría derivarse una variante para la versión «forever»; **eso está fuera de
alcance hoy** y no se diseña por adelantado.

Fase actual: **investigación de viabilidad**. No se escribe código del servidor hasta que
exista una decisión registrada en `docs/decisiones/` sobre core base y versión de cliente.

### 3. Estructura de directorios: no mezcles conceptos

| Directorio            | Qué contiene                                                         | ¿Se versiona? |
|-----------------------|----------------------------------------------------------------------|---------------|
| `docs/investigacion/` | Informes de investigación, comparativas, hallazgos con fuentes       | Sí            |
| `docs/decisiones/`    | Decisiones tomadas, una por archivo, con fecha y motivo (tipo ADR)   | Sí            |
| `upstream/`           | Clones de proyectos de terceros, **solo lectura** (ver §3.1)          | No (ignorado) |
| `server/`             | Nuestro código propio del emulador                                   | Sí            |
| `tools/`              | Nuestros scripts de build, extracción y utilidades                   | Sí            |
| `datos/`              | Datos extraídos del cliente de WoW (DBC, mapas, vmaps, MPQ)          | No (ignorado) |

Reglas duras:

- **Nunca** modifiques nada dentro de `upstream/`. Es material de referencia de terceros. Si
  hace falta cambiar código de un core, se hace en `server/` como parche o fork propio, y se
  documenta de dónde viene.
- **Nunca** confirmes datos del cliente de WoW, archivos MPQ, DBC, mapas ni artefactos
  extraídos. Son propiedad de Blizzard y además pesan gigabytes. Ya están en `.gitignore`.
- Un concepto, un directorio. Si dudas de dónde va un archivo, pregunta antes de inventar
  una carpeta nueva.

### 3.2. Código propio en `server/`

Cada módulo propio que parta de un proyecto de terceros va en **su propio subdirectorio de
`server/`** y lleva un `ORIGEN.md` con: URL de origen, **commit de partida**, licencia y una
lista fechada de los cambios respecto al original. Los commits de `upstream/` se fijan en
`tools/clonar-upstream.sh`, que reconstruye esa carpeta en cualquier máquina; si cambias de
commit de partida, actualiza ese script y el `ORIGEN.md`.

### 3.1. Organización de `upstream/`

Los clones de terceros **nunca se dejan sueltos en la raíz de `upstream/`**: van agrupados
**por proyecto de origen**, porque con el tiempo convivirán varios cores (AzerothCore,
TrinityCore, MaNGOS…) y sus módulos, y mezclarlos los haría indistinguibles.

```
upstream/
  azerothcore/            El core y todo lo que es suyo
    mod-sod/                Los módulos de la familia mod-sod
  trinitycore/            Si algún día hace falta, aquí
  herramientas/           Utilidades independientes de core (p. ej. wow-patcher)
```

Regla: antes de clonar, pregúntate **de qué proyecto es esto**, y crea o usa su directorio.
Un módulo va dentro del core al que pertenece, no al lado.

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

- El orquestador delega la implementación y **revisa siempre** el diff completo y el informe;
  la autorrevisión del ejecutor no sustituye la revisión. Delegar es la norma, no la excepción:
  el objetivo expreso es ahorrar consumo del orquestador reservándolo para diseño,
  revisión y auditoría.
- El ejecutor toca solo los archivos de su tarea. Si ve que necesita otros, lo dice en el
  informe en lugar de ampliar el alcance por su cuenta.
- Commits en castellano, en imperativo y concretos («Añade extractor de DBC», no «cambios»).
- No se hace `push` sin que el usuario lo pida.
- No se dice «hecho» sin haberlo comprobado ejecutándolo.
