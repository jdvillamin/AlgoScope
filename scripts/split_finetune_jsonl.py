#!/usr/bin/env python3
import argparse
import csv
import json
import random
from pathlib import Path


def read_jsonl(path: Path) -> list[dict]:
    rows = []
    with path.open("r", encoding="utf-8") as f:
        for line_no, line in enumerate(f, start=1):
            line = line.strip()
            if not line:
                continue
            try:
                row = json.loads(line)
            except json.JSONDecodeError as exc:
                raise SystemExit(f"{path}:{line_no}: invalid JSONL: {exc}") from exc
            messages = row.get("messages")
            if not isinstance(messages, list) or len(messages) < 3:
                raise SystemExit(f"{path}:{line_no}: missing chat messages")
            if messages[-1].get("role") != "assistant":
                raise SystemExit(f"{path}:{line_no}: final message must be assistant")
            rows.append(row)
    return rows


def write_jsonl(path: Path, rows: list[dict]) -> None:
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("--out-dir", type=Path, default=Path("datasets/fine_tuning_jsonl"))
    parser.add_argument("--prefix", default="algoscope_sft")
    parser.add_argument("--validation-size", type=int, default=20)
    parser.add_argument("--seed", type=int, default=20260428)
    parser.add_argument("--source-manifest", type=Path)
    args = parser.parse_args()

    rows = read_jsonl(args.input)
    if args.validation_size <= 0 or args.validation_size >= len(rows):
        raise SystemExit("--validation-size must be between 1 and input row count - 1")

    rng = random.Random(args.seed)
    indices = list(range(len(rows)))
    rng.shuffle(indices)
    validation_indices = set(indices[: args.validation_size])

    train = [row for i, row in enumerate(rows) if i not in validation_indices]
    validation = [row for i, row in enumerate(rows) if i in validation_indices]

    args.out_dir.mkdir(parents=True, exist_ok=True)
    train_path = args.out_dir / f"{args.prefix}_train.jsonl"
    validation_path = args.out_dir / f"{args.prefix}_validation.jsonl"
    manifest_path = args.out_dir / f"{args.prefix}_split_manifest.csv"

    write_jsonl(train_path, train)
    write_jsonl(validation_path, validation)

    source_rows = None
    fieldnames = ["split", "index"]
    if args.source_manifest:
        with args.source_manifest.open("r", encoding="utf-8", newline="") as f:
            source_rows = list(csv.DictReader(f))
        if len(source_rows) != len(rows):
            raise SystemExit("--source-manifest row count must match input JSONL row count")
        fieldnames.extend(["source", "category", "raw", "instrumented", "id"])

    with manifest_path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for i in range(len(rows)):
            row = {"split": "validation" if i in validation_indices else "train", "index": i}
            if source_rows is not None:
                row.update({key: source_rows[i][key] for key in ["source", "category", "raw", "instrumented", "id"]})
            writer.writerow(row)

    print(json.dumps({
        "input": str(args.input),
        "train": str(train_path),
        "validation": str(validation_path),
        "manifest": str(manifest_path),
        "total": len(rows),
        "train_count": len(train),
        "validation_count": len(validation),
        "seed": args.seed,
    }, indent=2))


if __name__ == "__main__":
    main()
