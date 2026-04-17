#!/usr/bin/env python3
"""Filter CodeNet C files for fine-tuning candidates.

Reads all .c files from an input directory, rejects files that are too
short/long, non-UTF-8, or won't compile, and classifies survivors by
detected data structure usage. Outputs passing files into subdirectories
and writes a rejection log.
"""

import os
import re
import shutil
import subprocess
import sys

SRC_DIR = os.path.join(os.path.dirname(__file__), "..", "datasets", "codenet_raw")
OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "datasets", "codenet_filtered")
REJECT_LOG = os.path.join(os.path.dirname(__file__), "..", "datasets", "codenet_rejected.log")

MIN_LINES = 5
MAX_LINES = 120


def read_file(path):
    try:
        with open(path, "r", encoding="utf-8") as f:
            return f.read()
    except UnicodeDecodeError:
        return None


def compiles(path):
    result = subprocess.run(
        ["gcc", "-fsyntax-only", "-std=c11", path],
        capture_output=True,
        timeout=10,
    )
    return result.returncode == 0


def classify(source):
    """Return a list of detected data structure tags."""
    tags = []

    # 2D array: double-index declarations or access
    if re.search(r"\w+\s*\[[^\]]+\]\s*\[[^\]]+\]", source):
        tags.append("array2d")

    # 1D array: single-index declarations or access (but not 2D)
    if re.search(r"\w+\s*\[\s*\w+\s*\]", source) and "array2d" not in tags:
        tags.append("array")

    # Struct-based (potential linked list, tree, graph)
    if re.search(r"\bstruct\b", source) and re.search(r"\bmalloc\b", source):
        if re.search(r"->", source):
            tags.append("struct")

    # If nothing specific detected, it's variable/loop-heavy
    if not tags:
        tags.append("variable")

    return tags


def main():
    src = os.path.abspath(SRC_DIR)
    out = os.path.abspath(OUT_DIR)

    if not os.path.isdir(src):
        print(f"Source directory not found: {src}")
        sys.exit(1)

    # Clean output
    if os.path.exists(out):
        shutil.rmtree(out)
    os.makedirs(out)

    files = sorted(f for f in os.listdir(src) if f.endswith(".c"))
    print(f"Scanning {len(files)} files...")

    rejected = []
    counts = {}
    passed = 0

    for i, fname in enumerate(files):
        path = os.path.join(src, fname)
        source = read_file(path)

        if source is None:
            rejected.append((fname, "non-utf8"))
            continue

        lines = source.splitlines()
        n = len(lines)

        if n < MIN_LINES:
            rejected.append((fname, f"too-short ({n} lines)"))
            continue

        if n > MAX_LINES:
            rejected.append((fname, f"too-long ({n} lines)"))
            continue

        if not compiles(path):
            rejected.append((fname, "compile-fail"))
            continue

        tags = classify(source)
        primary = tags[0]

        tag_dir = os.path.join(out, primary)
        os.makedirs(tag_dir, exist_ok=True)
        shutil.copy2(path, os.path.join(tag_dir, fname))

        counts[primary] = counts.get(primary, 0) + 1
        passed += 1

        if (i + 1) % 50 == 0:
            print(f"  processed {i + 1}/{len(files)}...")

    # Write rejection log
    with open(os.path.abspath(REJECT_LOG), "w") as f:
        for fname, reason in rejected:
            f.write(f"{fname}\t{reason}\n")

    print(f"\nResults:")
    print(f"  passed:   {passed}")
    print(f"  rejected: {len(rejected)}")
    print(f"\nBy category:")
    for tag in sorted(counts):
        print(f"  {tag:12s} {counts[tag]}")
    print(f"\nRejection log: {REJECT_LOG}")


if __name__ == "__main__":
    main()
