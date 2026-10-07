# Reanudar tareas tras un reinicio

1. Tras el reinicio, ejecuta `tools/cola/reanudar.sh` desde cualquier directorio.
2. El script inicia la cola en segundo plano y evita duplicarla si ya está activa.
3. Consulta `python3 tools/cola/cola.py status` y `python3 tools/cola/cola.py siguiente`.
4. Sigue el registro general con `tail -f .agents/cola/log/reanudar-AAAAmmdd-HHMMSS.log`.
5. Cada tarea guarda además su salida en `.agents/cola/log/<nombre>.log`.
6. Las tareas `en_curso` se recuperan y relanzan; el registro indica si quedaron cambios parciales.
7. `revisar` significa que AgentRelay terminó; consulta `agentrelay show <run_id>`.
8. Revisa y acepta o corrige con `agentrelay review <run_id> --decision ...`.
9. Cuando quede aceptada, usa `python3 tools/cola/cola.py marcar <nombre> hecha`.
10. Añade tareas con `python3 tools/cola/cola.py add <nombre> tarea.json --nota 'descripción'`.
11. El JSON se copia a `.agents/cola/tareas/`; `--orden N` elige la posición y `--previo-sql` guarda el SQL actual.
12. Para lanzar manualmente, ejecuta `python3 tools/cola/cola.py run`, con `--max N` o `--solo <nombre>` si hace falta.
13. Crontab opcional: `@reboot sleep 60 && /home/stark/Repos/acore-sod/tools/cola/reanudar.sh >> /home/stark/Repos/acore-sod/.agents/cola/log/cron.log 2>&1`.
