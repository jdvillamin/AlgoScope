#!/usr/bin/env python3
import argparse
import csv
import json
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FINE_TUNING_DIR = ROOT / "datasets" / "fine_tuning"
DEFAULT_CODENET_FILTERED_DIR = ROOT / "datasets" / "codenet_filtered"
DEFAULT_CODENET_INSTRUMENTED_DIR = ROOT / "datasets" / "codenet_instrumented"
PROMPT_HEADER = ROOT / "backend" / "ml" / "prompt_header.py"
TRACER = ROOT / "tracer" / "tracer.c"
TRACER_INCLUDE = ROOT / "tracer"

SYSTEM_MESSAGE = (
    "You are a strict C instrumentation engine. Insert tracer calls into the C "
    "program while preserving every original source line exactly. Output only "
    "valid C code."
)

DATA_TRACE_MARKERS = (
    "trace_var_init",
    "trace_var(",
    "trace_array_init",
    "trace_array(",
    "trace_array_highlight",
    "trace_array2d_init",
    "trace_array2d(",
    "trace_array2d_highlight",
    "trace_ll_",
    "trace_dll_",
    "trace_stack_",
    "trace_queue_",
    "trace_hash_",
    "trace_tree_",
    "trace_graph_",
)

CATEGORY_MARKERS = {
    "array": ("trace_array_init", "trace_array("),
    "array2d": ("trace_array2d_init", "trace_array2d("),
    "variable": ("trace_var_init",),
}


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def display_path(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def original_lines_preserved(raw: str, instrumented: str) -> bool:
    inst_lines = instrumented.splitlines()
    pos = 0
    for raw_line in raw.splitlines():
        while pos < len(inst_lines) and inst_lines[pos] != raw_line:
            pos += 1
        if pos >= len(inst_lines):
            return False
        pos += 1
    return True


def has_meaningful_traces(instrumented: str, category: str) -> tuple[bool, str]:
    if '#include "tracer.h"' not in instrumented:
        return False, "missing tracer include"
    if not any(marker in instrumented for marker in DATA_TRACE_MARKERS):
        return False, "missing non-line tracer calls"
    category_key = category.rsplit("/", 1)[-1]
    if category_key in CATEGORY_MARKERS:
        missing = [m for m in CATEGORY_MARKERS[category_key] if m not in instrumented]
        if missing:
            return False, f"missing category markers: {', '.join(missing)}"
    return True, ""


def compile_instrumented(path: Path) -> tuple[bool, str]:
    out = Path("/tmp") / "algoscope_finetune_check.out"
    cmd = [
        "gcc",
        str(path),
        str(TRACER),
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


def sample_pairs(fine_tuning_dir: Path = DEFAULT_FINE_TUNING_DIR) -> list[dict]:
    pairs = []
    for raw in sorted(fine_tuning_dir.rglob("*_raw.c")):
        inst = raw.with_name(raw.name.replace("_raw.c", "_instrumented.c"))
        if not inst.exists():
            continue
        category = raw.parent.relative_to(fine_tuning_dir).as_posix()
        pairs.append(
            {
                "source": "sample",
                "category": category,
                "raw": raw,
                "instrumented": inst,
                "id": f"sample/{category}/{raw.name}",
            }
        )
    return pairs


def codenet_pairs(
    filtered_dir: Path = DEFAULT_CODENET_FILTERED_DIR,
    instrumented_dir: Path = DEFAULT_CODENET_INSTRUMENTED_DIR,
) -> list[dict]:
    pairs = []
    for raw in sorted(filtered_dir.rglob("*.c")):
        category = raw.parent.relative_to(filtered_dir).as_posix()
        inst = instrumented_dir / raw.relative_to(filtered_dir)
        if not inst.exists():
            continue
        pairs.append(
            {
                "source": "codenet",
                "category": category,
                "raw": raw,
                "instrumented": inst,
                "id": f"codenet/{category}/{raw.name}",
            }
        )
    return pairs


def validate_pair(pair: dict) -> tuple[bool, list[str]]:
    errors = []
    raw = read_text(pair["raw"])
    instrumented = read_text(pair["instrumented"])
    if not original_lines_preserved(raw, instrumented):
        errors.append("raw lines not preserved in order")
    ok, reason = has_meaningful_traces(instrumented, pair["category"])
    if not ok:
        errors.append(reason)
    ok, reason = compile_instrumented(pair["instrumented"])
    if not ok:
        errors.append(reason)
    return not errors, errors


def jsonl_example(pair: dict) -> dict:
    raw = read_text(pair["raw"])
    instrumented = read_text(pair["instrumented"])
    return {
        "messages": [
            {"role": "system", "content": SYSTEM_MESSAGE},
            {"role": "user", "content": f"Instrument this C program:\n\n{raw}"},
            {"role": "assistant", "content": instrumented},
        ]
    }


def build(
    limit: int,
    sample_target: int,
    out_dir: Path,
    prefix: str = "first_100",
    fine_tuning_dir: Path = DEFAULT_FINE_TUNING_DIR,
    codenet_filtered_dir: Path = DEFAULT_CODENET_FILTERED_DIR,
    codenet_instrumented_dir: Path = DEFAULT_CODENET_INSTRUMENTED_DIR,
) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)
    selected = []
    rejected = []

    samples = sample_pairs(fine_tuning_dir)
    codenet = codenet_pairs(codenet_filtered_dir, codenet_instrumented_dir)

    for pool, target in ((samples, sample_target), (codenet, limit - sample_target)):
        for pair in pool:
            if len([p for p in selected if p["source"] == pair["source"]]) >= target:
                break
            ok, errors = validate_pair(pair)
            if ok:
                selected.append(pair)
            else:
                rejected.append({**pair, "errors": errors})

    if len(selected) < limit:
        for pair in codenet:
            if len(selected) >= limit:
                break
            if any(pair["id"] == p["id"] for p in selected):
                continue
            ok, errors = validate_pair(pair)
            if ok:
                selected.append(pair)
            else:
                rejected.append({**pair, "errors": errors})

    jsonl_path = out_dir / f"{prefix}.jsonl"
    manifest_path = out_dir / f"{prefix}_manifest.csv"
    report_path = out_dir / f"{prefix}_validation_report.json"

    with jsonl_path.open("w", encoding="utf-8") as f:
        for pair in selected[:limit]:
            f.write(json.dumps(jsonl_example(pair), ensure_ascii=False) + "\n")

    with manifest_path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["source", "category", "raw", "instrumented", "id"])
        writer.writeheader()
        for pair in selected[:limit]:
            writer.writerow(
                {
                    "source": pair["source"],
                    "category": pair["category"],
                    "raw": str(pair["raw"].relative_to(ROOT)),
                    "instrumented": str(pair["instrumented"].relative_to(ROOT)),
                    "id": pair["id"],
                }
            )

    report = {
        "requested": limit,
        "written": len(selected[:limit]),
        "sample_count": len([p for p in selected[:limit] if p["source"] == "sample"]),
        "codenet_count": len([p for p in selected[:limit] if p["source"] == "codenet"]),
        "jsonl": display_path(jsonl_path),
        "manifest": display_path(manifest_path),
        "validation_report": display_path(report_path),
        "rejected_checked": [
            {
                "id": r["id"],
                "raw": display_path(r["raw"]),
                "instrumented": display_path(r["instrumented"]),
                "errors": r["errors"],
            }
            for r in rejected[:200]
        ],
    }
    report_path.write_text(json.dumps(report, indent=2), encoding="utf-8")

    print(json.dumps(report, indent=2))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", type=int, default=100)
    parser.add_argument("--sample-target", type=int, default=50)
    parser.add_argument("--out-dir", type=Path, default=ROOT / "datasets" / "fine_tuning_jsonl")
    parser.add_argument("--prefix", default="first_100")
    parser.add_argument("--fine-tuning-dir", type=Path, default=DEFAULT_FINE_TUNING_DIR)
    parser.add_argument("--codenet-filtered-dir", type=Path, default=DEFAULT_CODENET_FILTERED_DIR)
    parser.add_argument("--codenet-instrumented-dir", type=Path, default=DEFAULT_CODENET_INSTRUMENTED_DIR)
    args = parser.parse_args()
    build(
        args.limit,
        args.sample_target,
        args.out_dir,
        args.prefix,
        args.fine_tuning_dir,
        args.codenet_filtered_dir,
        args.codenet_instrumented_dir,
    )


if __name__ == "__main__":
    main()
