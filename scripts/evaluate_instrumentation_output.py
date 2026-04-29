#!/usr/bin/env python3
import argparse
import json
import re
import subprocess
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TRACER_C = ROOT / "tracer" / "tracer.c"
TRACER_INCLUDE = ROOT / "tracer"

INIT_PATTERNS = (
    ("array_bars", re.compile(r'\btrace_array_init_bars\s*\(\s*"([^"]+)"')),
    ("array", re.compile(r'\btrace_array_init\s*\(\s*"([^"]+)"')),
    ("array2d", re.compile(r'\btrace_array2d_init\s*\(\s*"([^"]+)"')),
    ("linked_list", re.compile(r'\btrace_ll_init\s*\(\s*"([^"]+)"')),
    ("doubly_linked_list", re.compile(r'\btrace_dll_init\s*\(\s*"([^"]+)"')),
    ("stack", re.compile(r'\btrace_stack_init\s*\(\s*"([^"]+)"')),
    ("queue", re.compile(r'\btrace_queue_init\s*\(\s*"([^"]+)"')),
    ("hash", re.compile(r'\btrace_hash_init\s*\(\s*"([^"]+)"')),
    ("tree", re.compile(r'\btrace_tree_init\s*\(\s*"([^"]+)"')),
    ("graph", re.compile(r'\btrace_graph_init\s*\(\s*"([^"]+)"')),
)


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def original_lines_preserved(raw: str, candidate: str) -> bool:
    candidate_lines = candidate.splitlines()
    pos = 0
    for raw_line in raw.splitlines():
        while pos < len(candidate_lines) and candidate_lines[pos] != raw_line:
            pos += 1
        if pos >= len(candidate_lines):
            return False
        pos += 1
    return True


def visual_objects(code: str) -> Counter:
    objects = Counter()
    for kind, pattern in INIT_PATTERNS:
        for match in pattern.finditer(code):
            objects[(kind, match.group(1))] += 1
    return objects


def compile_candidate(path: Path) -> tuple[bool, str]:
    out = Path("/tmp") / "algoscope_eval_compile.out"
    cmd = [
        "gcc",
        str(path),
        str(TRACER_C),
        "-I",
        str(TRACER_INCLUDE),
        "-std=c11",
        "-w",
        "-lm",
        "-Dscanf_s=scanf",
        "-o",
        str(out),
    ]
    result = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode == 0:
        return True, ""
    return False, result.stderr.strip().splitlines()[0] if result.stderr else "compile failed"


def score(raw_path: Path, candidate_path: Path, reference_path: Path | None) -> dict:
    raw = read_text(raw_path)
    candidate = read_text(candidate_path)
    expected = visual_objects(read_text(reference_path)) if reference_path else Counter()
    observed = visual_objects(candidate)

    missing = list((expected - observed).elements())
    extra = list((observed - expected).elements())
    compile_ok, compile_error = compile_candidate(candidate_path)
    preserve_ok = original_lines_preserved(raw, candidate)

    return {
        "raw": str(raw_path),
        "candidate": str(candidate_path),
        "reference": str(reference_path) if reference_path else None,
        "compile_ok": compile_ok,
        "compile_error": compile_error,
        "raw_lines_preserved": preserve_ok,
        "visual_objects_expected": [{"kind": k, "name": n} for (k, n), count in expected.items() for _ in range(count)],
        "visual_objects_observed": [{"kind": k, "name": n} for (k, n), count in observed.items() for _ in range(count)],
        "visual_objects_match": not missing and not extra,
        "visual_objects_missing": [{"kind": k, "name": n} for k, n in missing],
        "visual_objects_extra": [{"kind": k, "name": n} for k, n in extra],
        "manual_unit_test": "pending",
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--raw", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--reference", type=Path)
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()

    result = score(args.raw, args.candidate, args.reference)
    text = json.dumps(result, indent=2)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text + "\n", encoding="utf-8")
    print(text)


if __name__ == "__main__":
    main()
