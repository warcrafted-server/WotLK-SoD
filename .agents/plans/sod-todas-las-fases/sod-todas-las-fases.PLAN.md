# Plan: runas de SoD, las 8 fases

Decisión del usuario (2026-10-06): implementar todas las runas de la build 1.15.9, hasta la fase 8,
más las partes de SoD aún no implementadas. Estado y datos en `docs/ESTADO.md`; pruebas en
`docs/PRUEBAS.md`.

## Datos de partida
- `docs/runas/catalogo-sod.json`: 661 runas, todas las clases y fases (campo `slot`; `slot_id` indica la
  ranura-fase de origen). Equivalentes WotLK: `docs/runas/equivalencias-wotlk.json` (solo fase 1 hoy).
- Método ya probado: clon del rango más alto de WotLK, `inherit_server`, descripción heredada, script
  del core si lo hay, `scale_to_level` para valores planos (ver `AGENTS.md`, `docs/ESTADO.md`).
- Specs por clase en `server/mod-sod-content/tools/sod_spells_<clase>.py`; SQL en `sod_<clase>_runes.sql`;
  bandas de `rune_id` en `server/mod-rune-engraving/docs/integrating-content.md` (1000 por clase).

## Orden
1. Cola inmediata: Explosive Shot (coste 4 %, el más cercano a 3,5 %), `scale_to_level` en las demás
   runas de daño y curación, traducción de textos de NPC.
2. Ampliar `tools/sod-data/classify_runes.py` y `match_wotlk.py` a todas las fases y ranuras; regenerar
   `docs/runas/plan-implementacion.*` con niveles P (pasiva), T (proc) y C (C++), más una columna de fase.
3. Ranuras y niveles por fase: abrir en la config del motor las ranuras de fases posteriores
   (`RuneEngraving.SlotMinLevel.*`, cortes de SoD 1/26/41/51 ya comentados) y comprobar que el motor, el
   NPC y el addon admiten las 11 ranuras.
4. Implementar por clase y fase, de menos a más difícil: P y T con datos; C con C++ en
   `server/mod-sod-content/src/<clase>/`. Un encargo por clase y fase, con los datos ya masticados.
5. Partes de SoD sin hacer: Chaos Bolt atraviesa absorciones; forma de oso de Survival of the Fittest;
   Penance (script del core con cadena de rangos); Beacon of Light y Mangle (`spell_linked_spell` no
   soportado por el generador).
6. Cada paso: recompilar solo si hay C++; actualizar `docs/PRUEBAS.md` con lo que debe probar el usuario.

## Riesgos
- Clases sin equivalente en WotLK (Raging Blow, Starsurge…): C++ nuevo, probar en juego.
- Runas de ranuras no fase 1 pueden necesitar ranuras que el addon no pinta aún.
- El generador solo soporta 3 efectos y enteros en `ManaCostPct`.
