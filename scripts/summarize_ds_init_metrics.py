#!/usr/bin/env python3
import argparse
import json
from collections import Counter
from pathlib import Path


def norm_kind(kind: str) -> str:
    if kind == "array_bars":
        return "array"
    return kind


def f1(precision: float, recall: float) -> float:
    if precision + recall == 0:
        return 0.0
    return 2 * precision * recall / (precision + recall)


def overlap_count(expected: Counter, observed: Counter) -> int:
    return sum((expected & observed).values())


def metric(numerator: int, denominator: int) -> float:
    if denominator == 0:
        return 1.0
    return numerator / denominator


def summarize_paths(label: str, result_paths: list[Path]) -> dict:
    if not result_paths:
        raise SystemExit(f"no result JSON files found for {label}")

    totals = Counter()
    category_hits = 0
    exact_object_hits = 0
    normalized_name_hits = 0
    kind_count_hits = 0
    kind_set_hits = 0
    examples_with_expected = 0

    for path in result_paths:
        row = json.loads(path.read_text(encoding="utf-8"))
        expected = row.get("visual_objects_expected", [])
        observed = row.get("visual_objects_observed", [])

        exact_expected = Counter((item["kind"], item["name"]) for item in expected)
        exact_observed = Counter((item["kind"], item["name"]) for item in observed)
        normalized_expected = Counter((norm_kind(item["kind"]), item["name"]) for item in expected)
        normalized_observed = Counter((norm_kind(item["kind"]), item["name"]) for item in observed)
        kind_expected = Counter(norm_kind(item["kind"]) for item in expected)
        kind_observed = Counter(norm_kind(item["kind"]) for item in observed)
        kind_set_expected = set(kind_expected)
        kind_set_observed = set(kind_observed)

        totals["examples"] += 1
        totals["compile_ok"] += int(bool(row.get("compile_ok")))
        totals["raw_lines_preserved"] += int(bool(row.get("raw_lines_preserved")))
        totals["exact_match_examples"] += int(bool(row.get("visual_objects_match")))
        totals["expected_objects"] += sum(exact_expected.values())
        totals["observed_objects"] += sum(exact_observed.values())
        totals["expected_kinds"] += len(kind_set_expected)
        totals["observed_kinds"] += len(kind_set_observed)

        exact_object_hits += overlap_count(exact_expected, exact_observed)
        normalized_name_hits += overlap_count(normalized_expected, normalized_observed)
        kind_count_hits += overlap_count(kind_expected, kind_observed)
        kind_set_hits += len(kind_set_expected & kind_set_observed)

        if kind_set_expected:
            examples_with_expected += 1
            category_hits += int(bool(kind_set_expected & kind_set_observed))

    exact_precision = metric(exact_object_hits, totals["observed_objects"])
    exact_recall = metric(exact_object_hits, totals["expected_objects"])
    normalized_precision = metric(normalized_name_hits, totals["observed_objects"])
    normalized_recall = metric(normalized_name_hits, totals["expected_objects"])
    kind_count_precision = metric(kind_count_hits, totals["observed_objects"])
    kind_count_recall = metric(kind_count_hits, totals["expected_objects"])
    kind_set_precision = metric(kind_set_hits, totals["observed_kinds"])
    kind_set_recall = metric(kind_set_hits, totals["expected_kinds"])

    return {
        "result_dir": label,
        "examples": totals["examples"],
        "compile_ok": totals["compile_ok"],
        "raw_lines_preserved": totals["raw_lines_preserved"],
        "exact_initializer_match_examples": totals["exact_match_examples"],
        "expected_ds_objects": totals["expected_objects"],
        "observed_ds_objects": totals["observed_objects"],
        "exact_object": {
            "precision": exact_precision,
            "recall": exact_recall,
            "f1": f1(exact_precision, exact_recall),
        },
        "normalized_name": {
            "precision": normalized_precision,
            "recall": normalized_recall,
            "f1": f1(normalized_precision, normalized_recall),
            "note": "Compares normalized kind plus name; array_bars counts as array.",
        },
        "kind_count": {
            "precision": kind_count_precision,
            "recall": kind_count_recall,
            "f1": f1(kind_count_precision, kind_count_recall),
            "note": "Compares normalized DS kinds with multiplicity; ignores variable names.",
        },
        "kind_set": {
            "precision": kind_set_precision,
            "recall": kind_set_recall,
            "f1": f1(kind_set_precision, kind_set_recall),
            "note": "Compares normalized DS kind sets per file; ignores names and duplicate counts.",
        },
        "category_hit": {
            "hits": category_hits,
            "examples_with_expected_ds": examples_with_expected,
            "rate": metric(category_hits, examples_with_expected),
            "note": "Passes a file if at least one expected DS kind appears in the candidate.",
        },
    }


def summarize(result_dir: Path) -> dict:
    result_paths = sorted((result_dir / "results").glob("*.json"))
    return summarize_paths(str(result_dir), result_paths)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("result_dirs", type=Path, nargs="+")
    parser.add_argument("--out", type=Path)
    parser.add_argument("--combined-label")
    args = parser.parse_args()

    if args.combined_label:
        result_paths = []
        for result_dir in args.result_dirs:
            result_paths.extend(sorted((result_dir / "results").glob("*.json")))
        summaries = [summarize_paths(args.combined_label, result_paths)]
    else:
        summaries = [summarize(path) for path in args.result_dirs]
    text = json.dumps(summaries, indent=2)
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text + "\n", encoding="utf-8")
    print(text)


if __name__ == "__main__":
    main()
