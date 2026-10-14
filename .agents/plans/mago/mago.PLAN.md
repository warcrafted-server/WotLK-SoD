# Plan: mago (runas base de SoD pendientes)

Las 14 runas del mago ya hechas (7000001–7000012 y Mass Regeneration `7000002`) viven en `sod_spells.py`/`sod_mage_*.sql`; las que
siguen van en `server/mod-sod-content/tools/sod_spells_mage.py` (registrado en `CLASS_SPEC_MODULES`). Arcane Blast, Living Bomb y
Mass Regeneration ya existen con otros ids y no se duplican. Convenciones y rutina como en `.agents/plans/picaro/picaro.PLAN.md`,
con la familia de WotLK 3. Encargos generados con `gen_tareas_clase.py mage` y podados a mano.

## Pasos

| Paso | Runas | Esfuerzo | Estado |
|---|---|---|---|
| 1 | Frostfire Bolt (7000016), Missile Barrage (7000017) | high | hecho |
| 2 | Spellfrost Bolt (7000018), Brain Freeze (7000019), Chronostatic Preservation (7000020), Spell Power (7000021), Advanced Warding (7000022) | high | hecho |
| 3 | Deep Freeze (7000023), Hot Streak (7000024), Temporal Anomaly (7000025), Balefire Bolt (7000026), Displacement (7000027) | high | pendiente |
| 4 | Molten Armor (7000028), Arcane Barrage (7000029), Frozen Orb (7000030), Overheat (7000031) | high | pendiente |
| 5 | Adquisición de los objetos-runa | medium | pendiente |
