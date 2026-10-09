# Brujo: verificación de datos y contrato de revisión (pasos 2–5)

Fecha: 2026-10-09. Autor: orquestador. **Nada de esto está compilado ni ejecutado en vivo**: son
comprobaciones sobre los datos del cliente SoD (`datos/wago/1.15.9.70003/`), sobre las tablas de
`acore_world` y sobre el código de `core/` (rama `Playerbot-SoD`). Lo que sí está verificado va
citado con archivo y línea; lo que no, aparece en «incertidumbres».

Este documento es el **contrato con el que el orquestador revisa** las ejecuciones de AgentRelay
de las runas de brujo (`.agents/plans/brujo/tareas/war2.json` … `war5.json`). Si un ejecutor se
desvía de §4 sin justificarlo, hay que pedir corrección (`agentrelay review <id> --decision fix`).

## 1. Fuentes consultadas

| Qué | De dónde | Cómo |
|---|---|---|
| Valores de las runas | CSV del cliente 1.15.9.70003 (`datos/wago/1.15.9.70003/`) | `SpellEffect.enUS.csv`, `SpellMisc.enUS.csv`, `SpellDuration.enUS.csv` |
| Equivalentes de WotLK 3.3.5 | DBC del cliente + `acore_world` viva + `core/data/sql/base/db_world/` | volcado crudo de `Spell.dbc`/`spell_dbc`, y `spell_proc`, `spell_script_names`, `spell_pet_auras` |
| Comportamiento del core | `core/src/server/game/**`, `core/src/server/scripts/Spells/spell_warlock.cpp` | lectura directa (se citan líneas) |

## 2. Reglas de traducción SoD → 3.3.5 (verificadas)

1. **`base`/`die`.** El importe de un efecto es `base + die` si `die != 0`, y `base` si `die == 0`.
   Los CSV de SoD guardan el importe final (`die=0`) o `valor-1` con `die=1`; las dos formas son
   válidas en 3.3.5. Ojo donde el core lee el **máximo**: `spell_warl_demonic_knowledge` calcula
   `pct = GetBaseAmount() + GetDieSides()` (`spell_warlock.cpp:281`), así que para el 3 % de la
   runa hay que dejar `base=2, die=1` **o** `base=3, die=0`.
2. **Máscaras de familia.** SoD 1.15.9 usa **el mismo reparto de bits que 3.3.5** para la familia
   de brujo. Pruebas: Backdraft marca Conflagrar con `maskB 0x800000` (= Conflagrar en 3.3.5);
   los `spell_proc` de Exterminación de SoD coinciden con los de WotLK (`mask0=1`, `mask1=192`,
   `SpellTypeMask=1`, `SpellPhaseMask=2`); los conjuntos de Aflicción eterna describen su lista de
   hechizos (`0x4109` / `0x40040`). ⇒ **se copian tal cual**. Los bits que en 3.3.5 no correspondan
   a ningún hechizo (p. ej. el hechizo exclusivo de SoD) simplemente no dispararán nunca; no hace
   falta limpiarlos.
3. **`aura 109` (`ADD_TARGET_TRIGGER`)** la resuelve el core de forma genérica, **sin C++**. Al
   **lanzar** un hechizo, el core recorre los auras 109 del lanzador
   (`unitCaster->GetAuraEffectsByType(SPELL_AURA_ADD_TARGET_TRIGGER)`, `Spell.cpp:9161-9180`),
   se queda con las que cubren ese hechizo (`AuraEffect::IsAffectedOnSpell`, es decir **las
   máscaras A/B/C del propio efecto**) y guarda el disparo con probabilidad
   `CalculateSpellDamage(..., baseAmount)` = **`base + die`** × acumulaciones. Al **golpear**
   (`Spell::DoTriggersOnSpellHit`, `Spell.cpp:3350-3400`) lanza el `EffectTriggerSpell` **sobre la
   unidad golpeada**. El destino final lo decide el blanco implícito del hechizo disparado: `1`
   (lanzador) → el buff cae en el brujo; `6` (enemigo) → cae en el objetivo. El propio comentario
   del core («info confirmed with retail sniffs of **permafrost** and **shadow weaving**») cubre
   los dos casos: Permafrost = buff al lanzador, Shadow Weaving = debuff a la víctima.
   ⇒ Sirve igual para Backdraft (buff al brujo) y para Aflicción eterna (refresco en el enemigo),
   y **no requiere fila en `spell_proc`**: el filtro son las máscaras del aura 109.
4. **Auras de familiar**: la tabla `spell_pet_auras` liga un aura **dummy del dueño** con el aura
   que el familiar recibe al invocarse (`class PetAura`, `SpellMgr.h:466`; carga en
   `SpellMgr::LoadSpellPetAuras`; aplicación en `Pet::CastPetAuras`, `Pet.cpp:2360`, recorriendo
   `owner->m_petAuras`; `spell_pet_auras.pet = 0` significa cualquier demonio). El emisor
   `tools/sod_spells*.py` **no** genera esta tabla ⇒ sus filas van **a mano** en el SQL del módulo.
5. **`GetDummyAuraEffect(familia, icono, efecto)`** = `GetAuraEffect(SPELL_AURA_DUMMY, familia,
   icono, efecto)` (`Unit.h:1442`), que casa por **`SpellFamilyName` + `SpellIconID` + índice**
   (`Unit.cpp:5535`). ⇒ Las runas cuyo efecto depende de un script del core que busca su dummy por
   icono (Pacto demoníaco) **no deben tocar `SpellIconID` ni `SpellClassSet`**: se heredan de la
   plantilla de WotLK.
6. **Duraciones**: las de los buffs de SoD coinciden **exactamente** con las de WotLK, así que se
   puede reutilizar/clonar la plantilla sin tocar duraciones:
   - Backdraft: índice 8 = 15 s (SoD 427714 y WotLK 54277).
   - Exterminación: índice 1 = 10 s (SoD 440873 y WotLK 63167).
   - Pacto demoníaco: índice 22 = 45 s (SoD 425467 y WotLK 48090).
7. **El emisor** sólo escribe `spell_script_names`, `spell_proc` y `spell_bonus_data`; todo lo
   demás (`spell_pet_auras`, filas de `spell_script_names` de ids nuevos, etc.) va a mano.
8. **Ids nuevos**: las runas usan 7008009–7008013 (fase 2). Para los auxiliares que no existen en
   el cliente se inventa un id libre del rango 9000xx (el último usado está en el SQL del módulo);
   no se reutiliza un id de Blizzard.

## 3. Rasgos del core que fijan el diseño

| Mecanismo | Dónde | Consecuencia |
|---|---|---|
| Script de Exterminación | `spell_warlock.cpp:1397` | Sólo comprueba `AURA_STATE_HEALTHLESS_35_PERCENT` (35 % fijo); no lleva el trigger escrito. ⇒ clonar 63158 y apuntar su trigger al buff es correcto. |
| Script de Aflicción eterna | `spell_warlock.cpp:672` | Refresca **Corrupción** (`0x2`) en **la unidad golpeada**. Exige `EFFECT_0` = `SPELL_EFFECT_SCRIPT_EFFECT` (77). El 47422 de WotLK ya es efecto 77, familia 5 y blanco 6 ⇒ clonarlo tal cual vale. |
| Script de Conocimiento demoníaco | `spell_warlock.cpp:273` | Aura sobre **el familiar**: `EFFECT_0` = `SPELL_AURA_MOD_DAMAGE_DONE` (13), importe recalculado cada 5 s, `pct = base + die` sobre la **stamina + intelecto del lanzador** (el propio familiar, porque quien lanza el aura es `Pet::CastPetAuras`). |
| Script de Pacto demoníaco | `spell_warlock.cpp:1417` | Colgado del **aura del familiar 54909**: exige que el actor sea un familiar, busca en **el dueño** un dummy de familia 5 + **icono 3220** (`WARLOCK_ICON_ID_DEMONIC_PACT`, línea 99), calcula `bp = importe × SP/100` y lanza **48090** (`SPELL_WARLOCK_DEMONIC_PACT_PROC`, línea 75) sobre el propio brujo. |
| Cooldown por aura | `SpellDefines.h:94-95`, `Player.cpp:11142` | `aura 108` + `SPELLMOD_COOLDOWN (11)` **sí** reduce el enfriamiento del hechizo filtrado por máscara ⇒ el «Soul Fire sin enfriamiento» de SoD no necesita C++. |
| Velocidad de lanzamiento | `SpellAuraEffects.cpp:130` | `aura 65` tiene manejador (`HandleModCastingSpeed`) ⇒ el Backdraft de SoD (que usa 65 y no 108) funciona sin C++. |
| `spell_pet_auras` de Conocimiento demoníaco | `core/data/sql/base/db_world/spell_pet_auras.sql:75-77` | Existen `35691/35692/35693 → 35696`, y el aura 35696 lleva `base=11, die=1` ⇒ **12 %** (el valor del rango 3, aplicado a todos los rangos). Para el 3 % de SoD hay que clonar 35696 con otro importe. |
| `spell_pet_auras` de Pacto demoníaco | `spell_pet_auras.sql` y `acore_world` (no hay) | En AzerothCore de WotLK **no existe ninguna fila** que entregue 53646/54909 al familiar: el talento de WotLK funciona por sus propios efectos (47236 = dummy 2 % + modificador plano + 2 % de daño). Nuestro 425464 sí necesita la fila `(425464, 0, 0, 54909)`. |
| `spell_script_names` del core | `acore_world` | Ya existen `-63156 → spell_warl_decimation`, `-35696 → spell_warl_demonic_knowledge`, `47422 → spell_warl_everlasting_affliction`, `54909 → spell_warl_demonic_pact`. Cualquier id **nuevo** que sustituya a esos necesita su propia fila. |

## 4. Diseño runa a runa (contrato de revisión)

Convenciones: los importes van como `base`/`die` de 3.3.5 (§2.1) y las máscaras tal cual las trae
SoD (§2.2). «Clon de X» = entrada del emisor con `template: X`, `inherit_server: true` y los
`overrides` que se listan (sólo esos: **no** se tocan `SpellClassSet` ni `SpellIconID`).

### 4.1 Backdraft — runa 7008009, ranura Cabeza (1)

SoD: `427713` (pasiva) + `427714` (buff).

- `427713`: aura 109, `base=99 die=1` (→100 %), `MiscValue=12`, `TriggerSpell=427714`,
  máscaras `A=0, B=8388608 (Conflagrar), C=0`, `ImplicitTargetA=1`, sin duración.
- `427714`: aura 65, `base=30 die=0`, `ImplicitTargetA=1`, `DurationIndex=8` (15 s).

Diseño:

- **Clon de 47260 → 427713**: `Effect_1=6`, `EffectAura_1=109`, `EffectBasePoints_1=99`,
  `EffectDieSides_1=1`, `EffectTriggerSpell_1=427714`, `EffectMiscValue_1=12`,
  `EffectSpellClassMaskA_1=0`, `EffectSpellClassMaskB_1=8388608`, `EffectSpellClassMaskC_1=0`.
  Cualquier otro efecto de 47260 queda vacío.
- **Clon de 54277 → 427714**: `EffectAura_1=65`, `EffectBasePoints_1=30`, `EffectDieSides_1=0`,
  `EffectMiscValue_1=0`, máscaras A/B/C a 0, `ImplicitTargetA_1=1`; la duración **no se toca**
  (índice 8 heredado = 15 s = la de SoD).
- **Sin fila en `spell_proc`** (el filtro es la máscara del aura 109).
- Cliente: las dos (el buff se ve).

### 4.2 Exterminación — runa 7008010, ranura Pies (512)

SoD: `440870` (pasiva) + `440873` (buff).

- `440870`: `EFFECT_0` aura 42 `base=40 die=0` trig `440873`; `EFFECT_1` dummy (aura 4)
  `base=35 die=0` `maskA=1`; `EFFECT_2` aura 108 `base=-100 die=0` `MiscValue=11` `maskB=128`.
- `440873`: `EFFECT_0` aura 108 `base=-40 die=0` `MiscValue=10` `maskB=128`; `EFFECT_1` aura 256
  `base=-40 die=0` `maskB=128`. Duración índice 1 = 10 s.

Diseño:

- **Clon de 63158 → 440870**: `EffectBasePoints_1=40`, `EffectDieSides_1=0` (o `39/1`: da 40 igual),
  `EffectTriggerSpell_1=440873`; el dummy del efecto 2 **ya vale** (base 34 die 1 = 35 = el de SoD);
  **añadir el efecto 3**: `Effect_3=6`, `EffectAura_3=108`, `EffectBasePoints_3=-100`,
  `EffectDieSides_3=0`, `EffectMiscValue_3=11`, `EffectSpellClassMaskB_3=128`,
  `EffectImplicitTargetA_3=1`.
- **A mano**: `spell_script_names (440870, 'spell_warl_decimation')` **y**
  `spell_proc (440870, SpellTypeMask=1, SpellPhaseMask=2, SpellFamilyName=5, SpellFamilyMask0=1,
  SpellFamilyMask1=192)` — copiando la fila `-63156` de `acore_world`.
- **Clon de 63167 → 440873**: `EffectBasePoints_1=-40`, `EffectDieSides_1=0`,
  `EffectSpellClassMaskB_1=128`; el resto igual (el importe del aura 256 da igual, sólo cuenta su
  presencia). *Alternativa equivalente y aceptable*: dejar el `EffectTriggerSpell_1` de 440870
  apuntando a **63167** y no clonar el buff (mismos efectos y misma duración).
- Cliente: 440870 sí; 440873 recomendable (es el buff visible).

### 4.3 Pacto demoníaco — runa 7008011, ranura Piernas (256)

SoD: `425464`: `EFFECT_0` dummy (aura 4) `base=10 die=0`; `EFFECT_1` aura 79 `base=10 die=0`
`MiscValue=36` (Fuego | Sombras), máscaras 0.

- **El buff no se clona**: el core lanza **48090** escrito a fuego (`spell_warlock.cpp:75`) desde el
  aura de familiar 54909, y 48090 ya tiene los dos efectos de `425467` (`aura 13` misc 126 +
  `aura 135` misc 126, blanco 56) y la misma duración (índice 22 = 45 s) ⇒ reutilizarlo es lo fiel.

Diseño:

- **Clon de 47236 → 425464**: `EFFECT_0` dummy con `EffectBasePoints_1=10`, `EffectDieSides_1=0`
  (dejar `EffectMiscValue_1=12`, `SpellIconID=3220` y `SpellClassSet=5` **intactos**: el script del
  core los usa para encontrar este dummy); `EFFECT_1` = aura 79 `base=10 die=0`
  `EffectMiscValue_2=36` y máscaras a 0; **`EFFECT_2` y `EFFECT_3` vacíos** (el aura 107 del
  talento de WotLK no existe en la runa de SoD).
- **A mano**: `spell_pet_auras (425464, 0, 0, 54909)` (mismo formato que las tres filas
  35691–35693 → 35696). **No** tocar 54909, 53646 ni 48090.
- Cliente: 425464 sí.
- Desviación conocida: el proc del familiar usa la fila `spell_proc` de 54909
  (`SpellTypeMask=1` = cualquier daño), así que proca **con cualquier golpe del familiar**, no sólo
  con críticos; es la misma simplificación que el talento de WotLK en este core. Va a
  `docs/runas/warlock.md`.
- Ojo: el `aura 79` es un efecto del aura pasiva, por lo que el +10 % a Fuego/Sombras está activo
  siempre (así vienen los datos de SoD, no ligado al proc).

### 4.4 Aflicción eterna — runa 7008012, ranura Piernas (256)

SoD: `412689` (pasiva) + `412698` (disparo).

- `412689`: aura 109 `base=100 die=0` (100 %), `TriggerSpell=412698`,
  máscaras `A=16649, B=262208, C=131072`, `ImplicitTargetA=1`.
- `412698`: efecto 77 (`SPELL_EFFECT_SCRIPT_EFFECT`), `ImplicitTargetA=6` (enemigo), familia 5.

Diseño:

- **Clon de 47422 → 412698 sin ningún override de efectos**: 47422 ya es efecto 77, familia 5 y
  blanco 6, que es justo lo que exige el script del core (`spell_warlock.cpp:672-690`). Sólo
  cambian id, nombre y descripción. (En el cliente no hace falta: el efecto no se ve.)
- **Clon de 47201 → 412689**: `EffectAura_1=109`, `EffectBasePoints_1=100`, `EffectDieSides_1=0`,
  `EffectTriggerSpell_1=412698`, `EffectSpellClassMaskA_1=16649`, `EffectSpellClassMaskB_1=262208`,
  `EffectSpellClassMaskC_1=131072`, `EffectImplicitTargetA_1=1`; **`EFFECT_2` vacío** (el talento
  de WotLK lleva ahí un aura 107 de +1 % de daño que la runa de SoD no tiene).
- **A mano**: `spell_script_names (412698, 'spell_warl_everlasting_affliction')`. **Sin**
  `spell_proc` (el filtro es la máscara del aura 109).
- Cliente: 412689 sí.

### 4.5 Conocimiento demoníaco — runa 7008013, ranura Pies (512)

SoD: `412732`: dummy (aura 4) `base=3 die=0`. La mecánica real vive en el **aura del familiar**,
que en SoD no tiene id propio (Blizzard la tenía del lado servidor).

Diseño:

- **Clon de 35693 → 412732**: `EFFECT_0` dummy con `EffectBasePoints_1=3`, `EffectDieSides_1=0`
  (el importe sólo alimenta el tooltip; el script recalcula el aura del familiar).
- **Clon de 35696 → 9000xx** (id libre del rango de auxiliares): `EffectBasePoints_1=3` con
  `EffectDieSides_1=0` (o `2/1`) ⇒ 3 %; el resto igual (efecto 143 `APPLY_AREA_AURA_PET` +
  `aura 13` `MOD_DAMAGE_DONE`, `MiscValue=126`). **No** se toca 35696 ni las filas
  35691/35692/35693 → 35696.
- **A mano**: `spell_script_names (9000xx, 'spell_warl_demonic_knowledge')` y
  `spell_pet_auras (412732, 0, 0, 9000xx)`.
- Cliente: 412732 sí; 9000xx recomendable (para que el buff del familiar tenga nombre e icono).

### 4.6 Resumen de ids y piezas

| Runa | id | Ranura | Spells de SoD | Plantillas de WotLK | SQL a mano |
|---|---|---|---|---|---|
| Backdraft | 7008009 | Cabeza (1) | 427713, 427714 | 47260, 54277 | — |
| Exterminación | 7008010 | Pies (512) | 440870, 440873 | 63158, 63167 | `spell_script_names` + `spell_proc` de 440870 |
| Pacto demoníaco | 7008011 | Piernas (256) | 425464 (buff: 48090 de WotLK) | 47236 | `spell_pet_auras (425464,0,0,54909)` |
| Aflicción eterna | 7008012 | Piernas (256) | 412689, 412698 | 47201, 47422 | `spell_script_names (412698, …)` |
| Conocimiento demoníaco | 7008013 | Pies (512) | 412732 (+ aura de familiar nueva) | 35693, 35696 | `spell_pet_auras (412732,0,0,9000xx)` + `spell_script_names (9000xx, …)` |

Ninguna de las cinco necesita C++ nuevo: todo son datos más los cuatro scripts que ya tiene el core.

## 5. Desviaciones y decisiones conscientes

1. **Pacto demoníaco proca con cualquier daño del familiar**, no sólo con críticos: la fila
   `spell_proc` de 54909 usa `SpellTypeMask=1` (daño). Es la misma simplificación que el talento
   de WotLK en este core. Debe quedar escrito en `docs/runas/warlock.md`.
2. **Pacto demoníaco reutiliza el buff 48090** en vez de crear 425467, porque el core lo lleva
   escrito a fuego (`spell_warlock.cpp:75`). Efectos y duración (45 s) son idénticos.
3. **Exterminación** implementa «Soul Fire sin enfriamiento» con `aura 108` + `SPELLMOD_COOLDOWN
   (11)` y máscara de Soul Fire, tal cual viene en los datos de SoD; no hace falta tocar el
   enfriamiento del hechizo en el DBC del cliente.
4. **Backdraft usa `aura 65`** (velocidad de lanzamiento) y no `aura 108`, y sin máscara: afecta a
   todos los hechizos, que es lo que dicen los datos de SoD (el talento de WotLK era 108 y estaba
   enmascarado).
5. **Conocimiento demoníaco**: el aura del familiar es una fila **de servidor** con id inventado
   (9000xx); WotLK da 12 % en todos los rangos y SoD pide 3 %, así que el clon lleva el importe de
   SoD.
6. **Coexistencia con los talentos de WotLK**: si un jugador pudiera tener a la vez un talento de
   WotLK y la runa equivalente, `GetDummyAuraEffect` devolvería el dummy que encuentre primero
   (importe del talento, no de la runa). Está relacionado con `docs/runas/redundantes.md`; estas
   tareas no lo resuelven y no hay que inventar una solución aquí.
7. **Bits de máscara sin hechizo equivalente en 3.3.5** (p. ej. el que corresponde al hechizo
   exclusivo de SoD): no disparan nunca. Se copian igualmente para no perder fidelidad y poder
   comparar con los CSV.

## 6. Lista de comprobación para revisar cada ejecución (war2…war5)

- [ ] El id de la runa y su ranura coinciden con §4 (Cabeza = 1, Piernas = 256, Pies = 512).
- [ ] Las plantillas son las de §4 y los `overrides` son exactamente los listados, ni uno de menos
      (importes, `die`, `TriggerSpell`, máscaras, `MiscValue`).
- [ ] No se ha sobrescrito `SpellClassSet` ni `SpellIconID` donde el core los necesita (7008011).
- [ ] Están las filas a mano: `spell_pet_auras (425464,0,0,54909)`,
      `spell_pet_auras (412732,0,0,9000xx)`, `spell_script_names` de `440870`, `412698` y `9000xx`.
- [ ] No se ha modificado ni borrado ninguna fila de Blizzard (`54909`, `48090`, `35696`,
      `63156/63158/63167`, `47422`, `47201`, `47236`, ni las filas 35691-35693 → 35696). Ojo
      también con `DELETE` sin `WHERE`.
- [ ] Los `INSERT` son idempotentes (`INSERT IGNORE` o `DELETE` previo), como el resto del módulo.
- [ ] `docs/runas/warlock.md` recoge las desviaciones de §5 y `TODO.md`/`docs/ESTADO.md` quedan al
      día.
- [ ] **No hay C++ nuevo**: si aparece, el ejecutor se ha salido del diseño (todo esto son datos).
- [ ] El diff no toca archivos fuera de los que la tarea declaraba.

## 7. Incertidumbres / no verificado

- **Nada está compilado ni ejecutado**: los mecanismos están leídos en el código del core, no
  observados en un servidor en marcha.
- No se ha comprobado que los ids de SoD tengan icono y nombre válidos **en el cliente 3.3.5** tras
  parchear; eso lo verifica `tools/sod-client/build_patch.py` y una prueba en el cliente.
- No se ha validado hechizo por hechizo el reparto de bits de la familia de brujo en 3.3.5 frente a
  la lista de SoD; se asume que los bits sin hechizo equivalente simplemente no disparan.
- Los textos de descripción de las runas se redactan a mano: no se han contrastado con el cliente
  de SoD.
- Las líneas citadas de `Spell.cpp`/`Unit.cpp`/`spell_warlock.cpp` son de la revisión actual de
  `core/`; si el core se actualiza, hay que volver a comprobarlas.
