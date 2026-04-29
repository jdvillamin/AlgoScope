#!/usr/bin/env python3
import argparse
import csv
import json
import os
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))


def clean_markdown(text: str) -> str:
    text = re.sub(r"```c", "", text)
    text = re.sub(r"```", "", text)
    return text.strip()


def add_line_numbers(code: str) -> str:
    return "\n".join(f"{i}: {line}" for i, line in enumerate(code.split("\n"), start=1))


def remove_line_numbers(code: str) -> str:
    return "\n".join(re.sub(r"^\s*\d+:\s*", "", line) for line in code.split("\n"))


def prompt_messages(raw: str, mode: str) -> list[dict]:
    if mode == "sft":
        return [
            {
                "role": "system",
                "content": (
                    "You are a strict C instrumentation engine. Insert tracer calls into the C "
                    "program while preserving every original source line exactly. Output only "
                    "valid C code."
                ),
            },
            {"role": "user", "content": f"Instrument this C program:\n\n{raw}"},
        ]

    from backend.ml.instrumenter import build_instrumentation_prompt

    numbered = add_line_numbers(raw)
    return [
        {
            "role": "system",
            "content": (
                "You are a strict C instrumentation engine. "
                "Preserve the full original source code exactly. "
                "Only insert trace lines before or after existing source lines."
            ),
        },
        {"role": "user", "content": build_instrumentation_prompt(numbered)},
    ]


def run_eval(raw_path: Path, reference_path: Path, candidate_path: Path, result_path: Path) -> dict:
    cmd = [
        "python3",
        "scripts/evaluate_instrumentation_output.py",
        "--raw",
        str(raw_path),
        "--candidate",
        str(candidate_path),
        "--reference",
        str(reference_path),
        "--out",
        str(result_path),
    ]
    completed = subprocess.run(cmd, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if completed.returncode != 0:
        raise SystemExit(completed.stderr or completed.stdout)
    return json.loads(result_path.read_text(encoding="utf-8"))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, default=Path("datasets/fine_tuning_jsonl/algoscope_sft_211_manifest.csv"))
    parser.add_argument("--model", required=True)
    parser.add_argument("--mode", choices=("prompt", "sft"), default="prompt")
    parser.add_argument("--limit", type=int, default=20)
    parser.add_argument("--out-dir", type=Path, default=Path("datasets/evals"))
    parser.add_argument("--temperature", type=float, default=0)
    args = parser.parse_args()

    if not os.getenv("OPENAI_API_KEY"):
        raise SystemExit("OPENAI_API_KEY is not set")

    from openai import OpenAI

    client = OpenAI()
    rows = []
    with args.manifest.open("r", encoding="utf-8", newline="") as f:
        for row in csv.DictReader(f):
            rows.append(row)
            if len(rows) >= args.limit:
                break

    run_dir = args.out_dir / f"{args.mode}_{args.model.replace('/', '_')}"
    outputs_dir = run_dir / "outputs"
    results_dir = run_dir / "results"
    outputs_dir.mkdir(parents=True, exist_ok=True)
    results_dir.mkdir(parents=True, exist_ok=True)

    results = []
    for idx, row in enumerate(rows, start=1):
        raw_path = ROOT / row["raw"]
        reference_path = ROOT / row["instrumented"]
        raw = raw_path.read_text(encoding="utf-8", errors="replace")
        response = client.chat.completions.create(
            model=args.model,
            temperature=args.temperature,
            messages=prompt_messages(raw, args.mode),
        )
        candidate = remove_line_numbers(clean_markdown(response.choices[0].message.content or ""))
        stem = f"{idx:03d}_{Path(row['raw']).stem}"
        candidate_path = outputs_dir / f"{stem}.c"
        result_path = results_dir / f"{stem}.json"
        candidate_path.write_text(candidate + "\n", encoding="utf-8")
        result = run_eval(raw_path, reference_path, candidate_path, result_path)
        result.update({"id": row["id"], "category": row["category"], "source": row["source"]})
        results.append(result)
        print(json.dumps({
            "id": row["id"],
            "compile_ok": result["compile_ok"],
            "visual_objects_match": result["visual_objects_match"],
            "manual_unit_test": result["manual_unit_test"],
        }))

    summary = {
        "model": args.model,
        "mode": args.mode,
        "count": len(results),
        "compile_ok": sum(1 for r in results if r["compile_ok"]),
        "visual_objects_match": sum(1 for r in results if r["visual_objects_match"]),
        "raw_lines_preserved": sum(1 for r in results if r["raw_lines_preserved"]),
        "manual_unit_test": "pending",
    }
    (run_dir / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
