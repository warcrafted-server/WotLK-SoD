#!/usr/bin/env python3
"""Persistent task queue for AgentRelay runs."""

import argparse
import datetime as dt
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
DEFAULT_QUEUE = ROOT / ".agents" / "cola"
STATE_NAME = "estado.json"
STATES = {"pendiente", "en_curso", "revisar", "hecha", "descartada"}
SCRATCHPAD_RE = re.compile(
    r"/tmp/claude-[^/\s\"']+/.+?/scratchpad/spell_dbc_before_[^/\s\"']+\.sql"
)


class QueueError(Exception):
    pass


def now_text():
    return dt.datetime.now().astimezone().isoformat(timespec="seconds")


def queue_path(value):
    return Path(value).expanduser().resolve() if value else DEFAULT_QUEUE


def state_path(queue_dir):
    return queue_dir / STATE_NAME


def load_state(queue_dir):
    path = state_path(queue_dir)
    if not path.exists():
        return {"version": 1, "tareas": []}
    try:
        state = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise QueueError("No se puede leer estado.json: %s" % exc)
    if not isinstance(state, dict) or state.get("version") != 1 or not isinstance(state.get("tareas"), list):
        raise QueueError("estado.json no tiene el formato de versión 1")
    return state


def save_state(queue_dir, state):
    queue_dir.mkdir(parents=True, exist_ok=True)
    fd, temp_name = tempfile.mkstemp(prefix=".estado-", suffix=".tmp", dir=str(queue_dir))
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            json.dump(state, stream, ensure_ascii=False, indent=2)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temp_name, state_path(queue_dir))
        try:
            dir_fd = os.open(str(queue_dir), os.O_DIRECTORY)
            try:
                os.fsync(dir_fd)
            finally:
                os.close(dir_fd)
        except (AttributeError, OSError):
            pass
    finally:
        if os.path.exists(temp_name):
            os.unlink(temp_name)


def find_task(state, name):
    for task in state["tareas"]:
        if task.get("nombre") == name:
            return task
    raise QueueError("No existe la tarea «%s»" % name)


def safe_name(name):
    if not name or name in {".", ".."} or Path(name).name != name or "/" in name or "\\" in name:
        raise QueueError("Nombre de tarea no válido")


def queue_relative_file(queue_dir, relative):
    path = (queue_dir / relative).resolve()
    try:
        path.relative_to(queue_dir.resolve())
    except ValueError:
        raise QueueError("El archivo de tarea debe estar dentro de la cola")
    return path


def cmd_add(args, queue_dir):
    safe_name(args.nombre)
    state = load_state(queue_dir)
    if any(task.get("nombre") == args.nombre for task in state["tareas"]):
        raise QueueError("Ya existe una tarea llamada «%s»" % args.nombre)

    source = Path(args.archivo).expanduser().resolve()
    if not source.is_file():
        raise QueueError("No existe el JSON de tarea: %s" % source)
    try:
        spec = json.loads(source.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise QueueError("El JSON de tarea no es válido: %s" % exc)
    if not isinstance(spec, dict):
        raise QueueError("El JSON de tarea debe contener un objeto")

    tasks_dir = queue_dir / "tareas"
    tasks_dir.mkdir(parents=True, exist_ok=True)
    try:
        source.relative_to(tasks_dir.resolve())
        destination = source
    except ValueError:
        destination = tasks_dir / source.name
        if destination.exists() and destination.read_bytes() != source.read_bytes():
            raise QueueError("Ya existe otro archivo con el nombre %s" % source.name)
        if not destination.exists():
            shutil.copy2(source, destination)

    existing_orders = [int(task.get("orden", 0)) for task in state["tareas"]]
    order = args.orden if args.orden is not None else (max(existing_orders, default=0) + 10)
    record = {
        "nombre": args.nombre,
        "archivo": destination.relative_to(queue_dir).as_posix(),
        "estado": "pendiente",
        "orden": order,
        "nota": args.nota or "",
        "previo_sql": bool(args.previo_sql),
        "run_id": None,
        "inicio": None,
        "fin": None,
        "resultado": None,
    }
    state["tareas"].append(record)
    save_state(queue_dir, state)
    print("Añadida %s (orden %s)" % (args.nombre, order))


def parse_date(value):
    if not value:
        return None
    try:
        return dt.datetime.fromisoformat(value.replace("Z", "+00:00"))
    except (ValueError, TypeError):
        return None


def duration(task):
    start = parse_date(task.get("inicio"))
    end = parse_date(task.get("fin"))
    if not start:
        return "-"
    end = end or dt.datetime.now().astimezone()
    try:
        seconds = max(0, int((end - start).total_seconds()))
    except TypeError:
        return "-"
    hours, remainder = divmod(seconds, 3600)
    minutes, seconds = divmod(remainder, 60)
    return "%02d:%02d:%02d" % (hours, minutes, seconds)


def cmd_status(queue_dir):
    state = load_state(queue_dir)
    headings = ("orden", "nombre", "estado", "run_id", "nota", "duración")
    rows = []
    for task in sorted(state["tareas"], key=lambda item: (int(item.get("orden", 0)), item.get("nombre", ""))):
        rows.append((
            str(task.get("orden", "")),
            str(task.get("nombre", "")),
            str(task.get("estado", "")),
            str(task.get("run_id") or "-"),
            str(task.get("nota") or "").replace("\n", " "),
            duration(task),
        ))
    widths = [max([len(headings[index])] + [len(row[index]) for row in rows])
              for index in range(len(headings))]
    print("  ".join(value.ljust(widths[index]) for index, value in enumerate(headings)))
    print("  ".join("-" * width for width in widths))
    for row in rows:
        print("  ".join(value.ljust(widths[index]) for index, value in enumerate(row)))


def cmd_siguiente(queue_dir):
    state = load_state(queue_dir)
    pending = sorted(
        (task for task in state["tareas"] if task.get("estado") == "pendiente"),
        key=lambda item: (int(item.get("orden", 0)), item.get("nombre", "")),
    )
    print(pending[0]["nombre"] if pending else "No hay tareas pendientes.")


def cmd_marcar(args, queue_dir):
    if args.estado not in STATES:
        raise QueueError("Estado no válido: %s" % args.estado)
    state = load_state(queue_dir)
    task = find_task(state, args.nombre)
    task["estado"] = args.estado
    if args.estado == "hecha":
        task["fin"] = now_text()
    save_state(queue_dir, state)
    print("%s: %s" % (args.nombre, args.estado))


def cmd_reset(args, queue_dir):
    state = load_state(queue_dir)
    task = find_task(state, args.nombre)
    task.update({"estado": "pendiente", "run_id": None, "inicio": None, "fin": None, "resultado": None})
    save_state(queue_dir, state)
    print("%s: pendiente" % args.nombre)


def pid_alive(pid):
    try:
        os.kill(pid, 0)
        return True
    except ProcessLookupError:
        return False
    except PermissionError:
        return True


def acquire_lock(queue_dir):
    lock_path = queue_dir / "runner.pid"
    queue_dir.mkdir(parents=True, exist_ok=True)
    for _ in range(3):
        try:
            fd = os.open(str(lock_path), os.O_CREAT | os.O_EXCL | os.O_WRONLY, 0o644)
            with os.fdopen(fd, "w", encoding="ascii") as stream:
                stream.write("%d\n" % os.getpid())
                stream.flush()
                os.fsync(stream.fileno())
            return lock_path
        except FileExistsError:
            try:
                old_pid = int(lock_path.read_text(encoding="ascii").strip())
            except (OSError, ValueError):
                old_pid = -1
            if old_pid > 0 and pid_alive(old_pid):
                raise QueueError("Ya hay una cola en ejecución (PID %d)" % old_pid)
            try:
                lock_path.unlink()
            except FileNotFoundError:
                pass
    raise QueueError("No se pudo adquirir el bloqueo de la cola")


def agentrelay_command():
    value = os.environ.get("AGENTRELAY_BIN", "agentrelay")
    command = shlex.split(value)
    if not command:
        raise QueueError("AGENTRELAY_BIN está vacío")
    if shutil.which(command[0]) is None and not Path(command[0]).is_file():
        raise QueueError("No se encuentra AgentRelay: %s" % command[0])
    return command


def call_agentrelay(command, args):
    try:
        return subprocess.run(command + args, text=True, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT, check=False)
    except OSError as exc:
        return subprocess.CompletedProcess(command + args, 127, str(exc))


def normalize_header(value):
    return re.sub(r"[^a-z]", "", value.lower())


def parse_list(output):
    records = []
    headers = None
    for raw_line in output.splitlines():
        line = raw_line.strip()
        if not line:
            continue
        if "|" in line:
            fields = [part.strip() for part in line.strip("| ").split("|")]
            normalized = [normalize_header(value) for value in fields]
            if any(value in {"id", "runid"} for value in normalized) and any(
                value in {"estado", "state"} for value in normalized
            ):
                headers = normalized
                continue
            if not fields or all(re.fullmatch(r"[-: ]+", value or "-") for value in fields):
                continue
            if headers and len(fields) >= len(headers):
                row = dict(zip(headers, fields))
                run_id = row.get("id") or row.get("runid")
                state = row.get("estado") or row.get("state")
                attempts = row.get("intentos") or row.get("attempts") or ""
                summary = row.get("resumen") or row.get("summary") or ""
                if run_id and state:
                    records.append({"id": run_id, "estado": state, "intentos": attempts, "resumen": summary})
                continue
        real = re.match(r"^(\d{8}-\d{6}-[0-9a-f]+)\s+(.+?)\s+intentos\s+(\d+)\s*(.*)$", line)
        if real:
            records.append({"id": real.group(1), "estado": real.group(2).strip(),
                            "intentos": real.group(3), "resumen": real.group(4)})
            continue
        match = re.match(r"^([A-Za-z0-9][A-Za-z0-9._-]+)\s+(\S+)\s+(\d+)\s+(.+)$", line)
        if match and not normalize_header(match.group(1)) in {"id", "runid"}:
            records.append({"id": match.group(1), "estado": match.group(2),
                            "intentos": match.group(3), "resumen": match.group(4)})
    return records


def append_log(queue_dir, name, message):
    log_dir = queue_dir / "log"
    log_dir.mkdir(parents=True, exist_ok=True)
    with (log_dir / (name + ".log")).open("a", encoding="utf-8") as stream:
        stream.write(message)
        if not message.endswith("\n"):
            stream.write("\n")
        stream.flush()


def log_command(queue_dir, name, label, completed):
    output = completed.stdout or ""
    append_log(queue_dir, name, "$ %s (código %s)\n%s" % (label, completed.returncode, output))


def recover_interrupted(queue_dir, state, command):
    interrupted = [task for task in state["tareas"] if task.get("estado") == "en_curso"]
    if not interrupted:
        return
    listing = call_agentrelay(command, ["list"])
    append_log(queue_dir, "reanudar", "$ agentrelay list (recuperación)\n" + (listing.stdout or ""))
    known = {entry["id"] for entry in parse_list(listing.stdout or "")}
    for task in interrupted:
        name = task["nombre"]
        if task.get("run_id"):
            run_id = str(task["run_id"])
            result = call_agentrelay(command, ["recover", run_id])
            append_log(queue_dir, name, "$ agentrelay recover %s%s\n%s" % (
                run_id, " (figura en agentrelay list)" if run_id in known else " (no figura en agentrelay list)",
                result.stdout or ""))
        append_log(queue_dir, name, "interrumpida por reinicio, se relanza; puede contener cambios parciales")
        task.update({"estado": "pendiente", "run_id": None, "inicio": None, "fin": None, "resultado": None})
        save_state(queue_dir, state)


def make_launch_spec(queue_dir, task):
    source = queue_relative_file(queue_dir, task["archivo"])
    try:
        spec = json.loads(source.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise QueueError("No se puede leer %s: %s" % (task["archivo"], exc))
    context = spec.get("context")
    if isinstance(context, str):
        previous_path = (queue_dir / "previo" / (task["nombre"] + ".sql")).resolve()
        spec["context"] = SCRATCHPAD_RE.sub(str(previous_path), context)
    handle = tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", suffix=".json",
                                         prefix="acore-sod-cola-", delete=False)
    try:
        json.dump(spec, handle, ensure_ascii=False, indent=2)
        handle.write("\n")
        return Path(handle.name)
    finally:
        handle.close()


def snapshot_sql(queue_dir, task):
    source = ROOT / "server/mod-sod-content/data/sql/db-world/base/sod_content_spell_dbc.sql"
    if not source.is_file():
        raise QueueError("No existe el SQL que se debe guardar antes de %s: %s" % (task["nombre"], source))
    destination = queue_dir / "previo" / (task["nombre"] + ".sql")
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)


def execute_task(queue_dir, state, task, command):
    name = task["nombre"]
    if task.get("previo_sql"):
        snapshot_sql(queue_dir, task)

    before = call_agentrelay(command, ["list"])
    previous_ids = {entry["id"] for entry in parse_list(before.stdout or "")}
    append_log(queue_dir, name, "$ agentrelay list (antes)\n" + (before.stdout or ""))

    task.update({"estado": "en_curso", "run_id": None, "inicio": now_text(), "fin": None, "resultado": None})
    save_state(queue_dir, state)
    append_log(queue_dir, name, "Inicio %s; lanzamiento con --allow-dirty" % task["inicio"])

    temp_spec = None
    run_returncode = 127
    try:
        temp_spec = make_launch_spec(queue_dir, task)
        with (queue_dir / "log" / (name + ".log")).open("a", encoding="utf-8") as log:
            log.write("$ agentrelay run --allow-dirty %s\n" % temp_spec)
            log.flush()
            try:
                completed = subprocess.run(command + ["run", "--allow-dirty", str(temp_spec)],
                                           stdout=log, stderr=subprocess.STDOUT, check=False)
                run_returncode = completed.returncode
            except OSError as exc:
                log.write("No se pudo iniciar AgentRelay: %s\n" % exc)
    except Exception as exc:
        append_log(queue_dir, name, "Error al preparar la tarea: %s" % exc)
    finally:
        if temp_spec is not None:
            try:
                temp_spec.unlink()
            except FileNotFoundError:
                pass

    listing = call_agentrelay(command, ["list"])
    records = parse_list(listing.stdout or "")
    new_records = [record for record in records if record["id"] not in previous_ids]
    latest = new_records[0] if new_records else None
    if listing.stdout:
        append_log(queue_dir, name, "$ agentrelay list (después)\n" + listing.stdout)

    task.update({
        "estado": "revisar",
        "run_id": latest["id"] if latest else None,
        "fin": now_text(),
        "resultado": latest["estado"] if latest else ("failed" if run_returncode else "unknown"),
    })
    save_state(queue_dir, state)
    append_log(queue_dir, name, "Fin %s; run_id=%s; resultado=%s" % (
        task["fin"], task["run_id"] or "desconocido", task["resultado"]))
    if listing.returncode != 0:
        append_log(queue_dir, name, "agentrelay list terminó con código %d" % listing.returncode)


def cmd_run(args, queue_dir):
    if args.max is not None and args.max < 1:
        raise QueueError("--max debe ser mayor que cero")
    lock_path = acquire_lock(queue_dir)
    try:
        state = load_state(queue_dir)
        save_state(queue_dir, state)
        command = agentrelay_command()
        recover_interrupted(queue_dir, state, command)
        selected = sorted(
            (task for task in state["tareas"]
             if task.get("estado") == "pendiente" and (not args.solo or task.get("nombre") == args.solo)),
            key=lambda item: (int(item.get("orden", 0)), item.get("nombre", "")),
        )
        if args.max is not None:
            selected = selected[:args.max]
        for task in selected:
            execute_task(queue_dir, state, task, command)
            print("Revisar %s (run_id: %s)" % (task["nombre"], task.get("run_id") or "desconocido"), flush=True)
    finally:
        try:
            if lock_path.read_text(encoding="ascii").strip() == str(os.getpid()):
                lock_path.unlink()
        except FileNotFoundError:
            pass


def build_parser():
    parser = argparse.ArgumentParser(description="Gestiona la cola persistente de tareas AgentRelay.")
    commands = parser.add_subparsers(dest="command", required=True)

    status = commands.add_parser("status", help="Muestra el estado de la cola")
    status.add_argument("--cola-dir")

    add = commands.add_parser("add", help="Añade un JSON de tarea a la cola")
    add.add_argument("nombre")
    add.add_argument("archivo")
    add.add_argument("--orden", type=int)
    add.add_argument("--nota", default="")
    add.add_argument("--previo-sql", action="store_true")
    add.add_argument("--cola-dir")

    run = commands.add_parser("run", help="Ejecuta las tareas pendientes en orden")
    run.add_argument("--max", type=int)
    run.add_argument("--solo")
    run.add_argument("--cola-dir")

    mark = commands.add_parser("marcar", help="Cambia el estado de una tarea")
    mark.add_argument("nombre")
    mark.add_argument("estado", choices=sorted(STATES))
    mark.add_argument("--cola-dir")

    reset = commands.add_parser("reset", help="Devuelve una tarea a pendiente")
    reset.add_argument("nombre")
    reset.add_argument("--cola-dir")

    next_task = commands.add_parser("siguiente", help="Muestra la próxima tarea pendiente")
    next_task.add_argument("--cola-dir")
    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)
    queue_dir = queue_path(getattr(args, "cola_dir", None))
    try:
        if args.command == "status":
            cmd_status(queue_dir)
        elif args.command == "add":
            cmd_add(args, queue_dir)
        elif args.command == "run":
            cmd_run(args, queue_dir)
        elif args.command == "marcar":
            cmd_marcar(args, queue_dir)
        elif args.command == "reset":
            cmd_reset(args, queue_dir)
        elif args.command == "siguiente":
            cmd_siguiente(queue_dir)
        return 0
    except QueueError as exc:
        print("Error: %s" % exc, file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
