#!/usr/bin/env python3
import argparse
import csv
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--split", choices=("train", "validation"), required=True)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()

    with args.manifest.open("r", encoding="utf-8", newline="") as f:
        rows = [row for row in csv.DictReader(f) if row.get("split") == args.split]

    if not rows:
        raise SystemExit(f"no rows for split: {args.split}")

    fieldnames = ["source", "category", "raw", "instrumented", "id"]
    args.out.parent.mkdir(parents=True, exist_ok=True)
    with args.out.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for row in rows:
            writer.writerow({key: row[key] for key in fieldnames})

    print(f"wrote {len(rows)} rows to {args.out}")


if __name__ == "__main__":
    main()
