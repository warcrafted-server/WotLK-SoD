#!/usr/bin/env python3
"""Comprueba la sintaxis de los módulos propios usando compile_commands.json."""

from __future__ import annotations

import concurrent.futures
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
from typing import Any


REPOSITORY_ROOT = Path(__file__).resolve().parents[2]
COMPILE_COMMANDS = Path("/home/stark/Repos/acore-test/build/compile_commands.json")
MODULES = (
    "server/mod-sod-content",
    "server/mod-rune-engraving",
)
DEPENDENCY_FLAGS_WITH_VALUE = {"-MF", "-MT", "-MQ", "-MJ"}
DEPENDENCY_FLAGS = {"-MD", "-MMD", "-MP"}
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".C"}
PCH_ERROR_MARKERS = (
    "precompiled header",
    "pch file",
    "unable to read pch",
    "invalid or corrupt pch",
)


def canonical(path: str | Path, directory: str | Path = ".") -> str:
    candidate = Path(path)
    if not candidate.is_absolute():
        candidate = Path(directory) / candidate
    return os.path.realpath(candidate)


def command_arguments(entry: dict[str, Any]) -> list[str]:
    if isinstance(entry.get("arguments"), list):
        return list(entry["arguments"])
    command = entry.get("command")
    if not isinstance(command, str):
        raise ValueError("la entrada no contiene 'arguments' ni 'command'")
    return shlex.split(command)


def is_source_argument(argument: str, entry: dict[str, Any]) -> bool:
    if Path(argument).suffix not in SOURCE_SUFFIXES:
        return False
    return canonical(argument, entry["directory"]) == canonical(
        entry["file"], entry["directory"]
    )


def pch_groups(arguments: list[str]) -> list[tuple[int, int]]:
    groups: list[tuple[int, int]] = []
    index = 0
    while index < len(arguments):
        argument = arguments[index]
        if argument == "-Xclang" and index + 3 < len(arguments):
            if arguments[index + 1] == "-include-pch" and arguments[index + 2] == "-Xclang":
                groups.append((index, index + 4))
                index += 4
                continue
        if argument == "-include-pch" and index + 1 < len(arguments):
            groups.append((index, index + 2))
            index += 2
            continue
        if argument.startswith("-include-pch="):
            groups.append((index, index + 1))
        index += 1
    return groups


def pch_file(group: tuple[int, int], arguments: list[str]) -> str | None:
    start, end = group
    for token in arguments[start:end]:
        if token.endswith((".pch", ".gch")):
            return token
    return None


def build_arguments(
    entry: dict[str, Any], source: Path, strip_all_pch: bool = False
) -> tuple[list[str], list[str]]:
    arguments = command_arguments(entry)
    if not arguments:
        raise ValueError("la orden de compilación está vacía")

    removed_pch: list[str] = []
    remove_indexes: set[int] = set()
    for start, end in pch_groups(arguments):
        pch = pch_file((start, end), arguments)
        missing = pch is not None and not Path(canonical(pch, entry["directory"])).is_file()
        if strip_all_pch or missing:
            remove_indexes.update(range(start, end))
            removed_pch.append(pch or "bandera PCH")

    cleaned: list[str] = []
    index = 0
    while index < len(arguments):
        if index in remove_indexes:
            index += 1
            continue

        argument = arguments[index]
        if argument in {"-o", "-MF", "-MT", "-MQ", "-MJ"}:
            index += 2
            continue
        if argument in {"-c", *DEPENDENCY_FLAGS} or (strip_all_pch and argument == "-Winvalid-pch"):
            index += 1
            continue
        if argument.startswith(("-MF", "-MT", "-MQ", "-MJ")) and argument not in DEPENDENCY_FLAGS_WITH_VALUE:
            index += 1
            continue
        if is_source_argument(argument, entry):
            cleaned.append(str(source.resolve()))
            index += 1
            continue
        cleaned.append(argument)
        index += 1

    if not any(argument == str(source.resolve()) for argument in cleaned):
        cleaned.append(str(source.resolve()))
    cleaned.extend(("-fsyntax-only", "-fno-color-diagnostics"))
    return cleaned, removed_pch


def error_context(output: str) -> str:
    lines = output.splitlines()
    error_indexes = [index for index, line in enumerate(lines) if "error:" in line]
    if not error_indexes:
        return output.strip() or "clang terminó con error sin emitir diagnóstico."

    shown: set[int] = set()
    for index in error_indexes:
        shown.update(range(max(0, index - 2), min(len(lines), index + 3)))
    return "\n".join(lines[index] for index in sorted(shown))


def run_source(
    source: Path,
    entry: dict[str, Any] | None,
    template_description: str | None,
) -> dict[str, Any]:
    if entry is None:
        return {
            "source": source,
            "ok": False,
            "message": "Sin entrada ni plantilla de compile_commands.json.",
            "fallback": template_description,
        }

    try:
        arguments, removed_pch = build_arguments(entry, source)
    except (KeyError, ValueError, OSError) as error:
        return {"source": source, "ok": False, "message": str(error), "fallback": template_description}

    command = ["nice", "-n", "19", *arguments]
    try:
        completed = subprocess.run(
            command,
            cwd=entry["directory"],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            check=False,
        )
    except OSError as error:
        return {
            "source": source,
            "ok": False,
            "message": f"No se pudo ejecutar clang: {error}",
            "fallback": template_description,
        }

    output = completed.stdout
    retried_without_pch = False
    if completed.returncode != 0 and any(marker in output.lower() for marker in PCH_ERROR_MARKERS):
        try:
            retry_arguments, retry_removed_pch = build_arguments(entry, source, strip_all_pch=True)
            if retry_removed_pch:
                retry = subprocess.run(
                    ["nice", "-n", "19", *retry_arguments],
                    cwd=entry["directory"],
                    text=True,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    check=False,
                )
                completed = retry
                output = retry.stdout
                removed_pch.extend(retry_removed_pch)
                retried_without_pch = True
        except OSError as error:
            output += f"\nNo se pudo repetir sin PCH: {error}"

    success = completed.returncode == 0
    message = "OK" if success else error_context(output)
    return {
        "source": source,
        "ok": success,
        "message": message,
        "fallback": template_description,
        "removed_pch": sorted(set(removed_pch)),
        "retried_without_pch": retried_without_pch,
    }


def load_tasks() -> tuple[list[tuple[Path, dict[str, Any] | None, str | None]], int]:
    if not COMPILE_COMMANDS.is_file():
        raise FileNotFoundError(f"No existe {COMPILE_COMMANDS}")
    entries = json.loads(COMPILE_COMMANDS.read_text(encoding="utf-8"))
    by_source: dict[str, dict[str, Any]] = {}
    for entry in entries:
        try:
            by_source[canonical(entry["file"], entry["directory"])] = entry
        except (KeyError, TypeError):
            continue

    tasks: list[tuple[Path, dict[str, Any] | None, str | None]] = []
    for relative_module in MODULES:
        source_root = REPOSITORY_ROOT / relative_module / "src"
        if not source_root.is_dir():
            raise FileNotFoundError(f"No existe el directorio {source_root}")
        module_sources = sorted(
            source for source in source_root.rglob("*") if source.is_file() and source.suffix in SOURCE_SUFFIXES
        )
        module_entry_paths = [
            entry
            for entry in by_source.values()
            if canonical(entry["file"], entry["directory"]).startswith(
                os.path.realpath(source_root) + os.sep
            )
            or f"/{Path(relative_module).name}/src/"
            in ("/" + str(entry["file"]).replace("\\", "/").lstrip("/"))
        ]
        if not module_entry_paths:
            raise RuntimeError(f"No hay órdenes de compilación para el módulo {relative_module}")
        template = sorted(module_entry_paths, key=lambda entry: canonical(entry["file"], entry["directory"]))[0]
        for source in module_sources:
            source_key = os.path.realpath(source)
            entry = by_source.get(source_key)
            description = None
            if entry is None:
                description = f"plantilla {Path(template['file']).name} del mismo módulo"
                entry = template
            tasks.append((source, entry, description))
    return tasks, len(by_source)


def main() -> int:
    try:
        tasks, entry_count = load_tasks()
    except (OSError, ValueError, RuntimeError, json.JSONDecodeError) as error:
        print(f"No se pudo preparar la comprobación: {error}", file=sys.stderr)
        return 2

    print(f"Entradas cargadas: {entry_count}; archivos fuente: {len(tasks)}; procesos simultáneos: 2.", flush=True)
    results: list[dict[str, Any]] = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as executor:
        futures = {
            executor.submit(run_source, source, entry, fallback): source
            for source, entry, fallback in tasks
        }
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            relative = result["source"].relative_to(REPOSITORY_ROOT)
            label = "OK" if result["ok"] else "ERROR"
            detail = f" ({result['fallback']})" if result.get("fallback") else ""
            if result.get("removed_pch"):
                detail += f" (se retiró PCH: {', '.join(result['removed_pch'])})"
            if result.get("retried_without_pch"):
                detail += " (reintentado sin PCH)"
            print(f"[{label}] {relative}{detail}", flush=True)
            if not result["ok"]:
                print(result["message"], flush=True)

    passed = sum(result["ok"] for result in results)
    failed = len(results) - passed
    fallbacks = sum(result.get("fallback") is not None for result in results)
    print(
        f"Resumen: {passed} OK, {failed} con errores, {fallbacks} con orden plantilla, "
        f"{len(results)} archivos en total."
    )
    return 0 if failed == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
