# WarCrafted Launcher

Instrucciones propias de `launcher/`, subproyecto independiente dentro del repositorio
`warcrafted-server/WotLK-SoD`. El [AGENTS.md raíz](../AGENTS.md) trata del servidor AzerothCore/SoD
(otro lenguaje, otro ciclo de vida, otras normas de `upstream/`/`core/`/`server/`) y **no aplica
aquí** salvo lo que se repite expresamente en este archivo. Si trabajas dentro de `launcher/`, esta
es tu referencia; si trabajas en el resto del repo, usa el AGENTS.md raíz.

## 0. Qué es esto

Launcher de escritorio oficial de **WarCrafted**: punto de entrada del jugador al ecosistema
(detección/preparación del cliente WoW 3.3.5 build 12340, parches y addons obligatorios,
actualizaciones, noticias, enlaces, addons opcionales, lanzamiento del juego). Pensado para un
solo reino hoy (nuestro WotLK-SoD) pero con arquitectura abierta a varios reinos en el futuro.
El encargo completo del usuario, con todos los requisitos funcionales, de UX, de seguridad y de
licencias, está en `docs/encargo-original.md`: **léelo antes de tomar cualquier decisión
importante**, es la fuente de la que deriva todo lo demás.

Rol del orquestador en este subproyecto: investigar, decidir arquitectura, delegar
implementación, revisar críticamente. No se da por bueno un resultado solo porque compile.

## 1. Idioma

Igual que el resto del repo: documentación, commits, comentarios e informes en **castellano**.
Identificadores de código en **inglés**.

## 2. Fase actual: investigación y decisión de stack (obligatoria antes de implementar)

**No hay stack tecnológico fijado todavía.** Antes de escribir código de producto:

1. Investigar (delegado al ejecutor, para ahorrar contexto del orquestador) proyectos
   existentes: launchers de AzerothCore/WoW 3.3.5, sistemas de autoactualización y manifest,
   distribución incremental de archivos, gestores de addons, launchers profesionales de
   videojuegos, y las opciones de UI de escritorio relevantes (p. ej. Tauri, Electron,
   .NET/WPF/Avalonia u otras que surjan) con sus licencias, tamaño de binario, story de
   auto-actualización y seguridad por proceso.
2. El orquestador evalúa los hallazgos, decide el stack y lo registra como decisión en
   `docs/decisiones/0001-stack-tecnologico.md` (mismo formato que las decisiones del repo raíz:
   fecha, contexto, alternativas consideradas, elección, motivo).
3. Solo entonces se empieza a implementar.

Toda afirmación sobre un proyecto externo (licencia, actividad, versión soportada) va con URL y
fecha de consulta, igual que en el resto del repo. Sin fuente, no se escribe. Se puede estudiar
código con licencia incompatible para aprender de su arquitectura, pero no copiarlo ni derivar de
él: la licencia final del launcher la elige WarCrafted con libertad, así que ninguna dependencia
(framework, librerías, UI, fuentes, iconos, assets) puede imponer condiciones incompatibles con
eso. Revisa también las dependencias transitivas cuando sea relevante.

## 3. Principios de arquitectura (no negociables, vienen del encargo)

- **Separación estricta** entre: núcleo de actualización/integridad, lógica de reinos/configuración,
  UI, y contenido remoto (noticias/addons opcionales). La identidad visual debe poder cambiar sin
  tocar la lógica.
- **Multi-reino desde el diseño, mono-reino en la implementación inicial.** No se construye ahora
  selector de reinos ni gestión de credenciales por reino si solo hay uno, pero ningún dato de
  reino (URLs, build de cliente, archivos obligatorios, addons obligatorios, noticias) se escribe
  como constante: va en configuración/manifest para que añadir un reino no obligue a rehacer nada.
- **Confianza cero en lo descargado** hasta validarlo: hashes criptográficos, actualizaciones
  atómicas (nunca un cliente a medio actualizar), verificación antes de sustituir, protección
  contra path traversal y contra ejecución arbitraria de contenido descargado, validación de URLs
  de origen. Esto incluye la actualización del propio launcher.
- **Addons obligatorios vs. opcionales**: nunca deben poder confundirse ni en el modelo de datos ni
  en la UI. Los obligatorios los gestiona el mismo sistema de integridad que el cliente; el jugador
  no puede desactivarlos ni dejarlos desactualizados y seguir jugando.
- **Bloqueo de juego mientras el cliente no esté en estado válido** es una invariante del sistema,
  no una comprobación cosmética de la UI.
- **GitHub como infraestructura de distribución** (releases del launcher, manifest de versiones):
  diseñar sabiendo sus límites (tamaño de release, límites de API/rate limit, no es un CDN) en vez
  de descubrirlos tarde. Si esto resulta ser una limitación real, decirlo y proponer alternativa en
  vez de forzarlo.
- **No sobreingeniería**: no se construye soporte para varios reinos, varias versiones de cliente
  o varias versiones de WoW *de más* — solo se evita que añadirlas después obligue a rehacer la
  base.

## 4. Estructura de directorios dentro de `launcher/`

Stack decidido: **Tauri 2** (`docs/decisiones/0001-stack-tecnologico.md`). Estructura de un
proyecto Tauri estándar, más nuestras carpetas de documentación:

| Ruta                          | Qué contiene                                                  | ¿Se versiona? |
|-------------------------------|----------------------------------------------------------------|---------------|
| `AGENTS.md` / `CLAUDE.md`     | Este archivo y su alias para Claude Code                       | Sí            |
| `docs/encargo-original.md`    | Encargo completo del usuario, literal, fuente de todo lo demás | Sí            |
| `docs/decisiones/`            | Decisiones tipo ADR, una por archivo, con fecha y motivo        | Sí            |
| `docs/investigacion/`         | Informes de investigación con fuentes y fecha de consulta       | Sí            |
| `docs/ESTADO.md`              | Estado del subproyecto: qué toca ahora, cómo reanudar           | Sí            |
| `src/`                        | Frontend web (UI): ventana principal, noticias, addons, config | Sí            |
| `src-tauri/`                  | Backend Rust: comandos, motor de actualización/integridad, capabilities | Sí      |
| `src-tauri/target/`, `node_modules/`, `dist/` | Artefactos de build                            | No (ignorado) |

El motor de actualización/integridad (manifest, hashes, staging atómico) vive en `src-tauri/`
como módulo propio, no como dependencia de un framework de UI (decisión 0001).

## 5. Delegación con AgentRelay

Este subproyecto comparte repositorio git con el servidor, así que `agentrelay status`/`run`
operan sobre **todo** `WotLK-SoD`, no solo sobre `launcher/`. Al delegar tareas del launcher:

- Indica explícitamente en el `objective`/`context` de la tarea que el trabajo es sobre
  `launcher/` y que no debe tocar `server/`, `core/`, `docs/decisiones/0001`-`0005` (son del
  servidor) ni nada fuera de `launcher/`, salvo que la propia tarea lo pida.
- Usa `files`/`doNotModify` para acotar a rutas dentro de `launcher/`.
- El resto del flujo (dividir en tareas pequeñas, revisar con `agentrelay show`/`review`, no dar
  por bueno que compile, commits en castellano) es el mismo que describe el AGENTS.md raíz en su
  bloque de AgentRelay.

## 6. Rigor

No inventar números de versión, nombres de API, límites de GitHub ni cifras de rendimiento sin
comprobarlos. Si algo no se puede verificar, decirlo explícitamente en vez de darlo por hecho.
