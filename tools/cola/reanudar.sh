#!/usr/bin/env bash
set -euo pipefail

ROOT=/home/stark/Repos/acore-sod
QUEUE="$ROOT/.agents/cola"
LOG_DIR="$QUEUE/log"
LOCK_DIR="$QUEUE/launch.lock"

cd "$ROOT"
mkdir -p "$LOG_DIR"

if ! command -v agentrelay >/dev/null 2>&1; then
    echo "No se encuentra agentrelay en PATH." >&2
    exit 1
fi

pid_is_alive() {
    local pid="$1"
    [[ "$pid" =~ ^[0-9]+$ ]] && kill -0 "$pid" 2>/dev/null
}

if [[ -f "$QUEUE/runner.pid" ]]; then
    runner_pid=$(cat "$QUEUE/runner.pid" 2>/dev/null || true)
    if pid_is_alive "$runner_pid"; then
        echo "La cola ya se está ejecutando (PID $runner_pid)."
        exit 0
    fi
fi

if ! mkdir "$LOCK_DIR" 2>/dev/null; then
    lock_pid=$(cat "$LOCK_DIR/pid" 2>/dev/null || true)
    if pid_is_alive "$lock_pid"; then
        echo "La reanudación ya está en curso (PID $lock_pid)."
        exit 0
    fi
    lock_age=$(( $(date +%s) - $(stat -c %Y "$LOCK_DIR" 2>/dev/null || date +%s) ))
    if [[ -z "$lock_pid" && "$lock_age" -lt 60 ]]; then
        echo "La reanudación está iniciándose; no se duplica."
        exit 0
    fi
    rm -rf "$LOCK_DIR"
    mkdir "$LOCK_DIR"
fi

log_file="$LOG_DIR/reanudar-$(date +%Y%m%d-%H%M%S).log"
nohup bash -c '
    set +e
    root="$1"
    queue="$2"
    lock_dir="$3"
    log_file="$4"
    printf "%s\n" "$BASHPID" > "$lock_dir/pid"
    cleanup() { rm -rf "$lock_dir"; }
    trap cleanup EXIT
    cd "$root" || exit 1

    python3 tools/cola/cola.py run
    queue_rc=$?

    if python3 - "$root" <<"PY"
import ast
import json
import pathlib
import sys

try:
root = pathlib.Path(sys.argv[1])
source_path = root / "docs/runas/fuentes-sod.json"
if not source_path.exists():
    raise SystemExit(0)
try:
    catalogue = json.loads((root / "docs/runas/catalogo-sod.json").read_text(encoding="utf-8"))
    found = json.loads(source_path.read_text(encoding="utf-8"))
    tree = ast.parse((root / "tools/sod-data/fetch_rune_sources.py").read_text(encoding="utf-8"))
except (OSError, ValueError, SyntaxError, KeyError, TypeError):
    raise SystemExit(0)
slot_ids = None
for node in ast.walk(tree):
    if isinstance(node, ast.Assign) and any(isinstance(target, ast.Name) and target.id == "SLOT_IDS" for target in node.targets):
        try:
            slot_ids = ast.literal_eval(node.value)
        except (ValueError, SyntaxError):
            raise SystemExit(0)
        break
if slot_ids is None or not isinstance(found, dict):
    raise SystemExit(0)
needed = {str(rune["taught_spell_id"]) for rune in catalogue["runas"] if rune.get("slot_id") in slot_ids}
valid = {"ok", "sin_objeto"}
raise SystemExit(0 if any(key not in found or not isinstance(found[key], dict) or found[key].get("estado") not in valid for key in needed) else 1)
PY
    then
        echo "Quedan fuentes de runas por recoger; se reanuda el extractor."
        PAUSE=10 python3 -u tools/sod-data/fetch_rune_sources.py
    else
        echo "Las fuentes de runas ya están completas; se omite el extractor."
    fi
    exit "$queue_rc"
' _ "$ROOT" "$QUEUE" "$LOCK_DIR" "$log_file" >>"$log_file" 2>&1 </dev/null &
background_pid=$!
printf '%s\n' "$background_pid" > "$LOCK_DIR/pid"

echo "Reanudación iniciada (PID $background_pid)."
echo "Registro: $log_file"
echo "Seguir: tail -f '$log_file'"
