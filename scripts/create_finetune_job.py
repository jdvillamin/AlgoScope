#!/usr/bin/env python3
import argparse
import json
import os
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--train", type=Path, default=Path("datasets/fine_tuning_jsonl/algoscope_sft_train.jsonl"))
    parser.add_argument("--validation", type=Path, default=Path("datasets/fine_tuning_jsonl/algoscope_sft_validation.jsonl"))
    parser.add_argument("--model", default="gpt-4.1-mini-2025-04-14")
    parser.add_argument("--suffix", default="algoscope-instrumenter")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    if not args.train.exists():
        raise SystemExit(f"missing train file: {args.train}")
    if not args.validation.exists():
        raise SystemExit(f"missing validation file: {args.validation}")

    if args.dry_run:
        print(json.dumps({
            "model": args.model,
            "train": str(args.train),
            "validation": str(args.validation),
            "suffix": args.suffix,
            "next": "set OPENAI_API_KEY and rerun without --dry-run to upload files and create the job",
        }, indent=2))
        return

    if not os.getenv("OPENAI_API_KEY"):
        raise SystemExit("OPENAI_API_KEY is not set")

    from openai import OpenAI

    client = OpenAI()
    training_file = client.files.create(file=args.train.open("rb"), purpose="fine-tune")
    validation_file = client.files.create(file=args.validation.open("rb"), purpose="fine-tune")
    job = client.fine_tuning.jobs.create(
        model=args.model,
        training_file=training_file.id,
        validation_file=validation_file.id,
        suffix=args.suffix,
    )
    print(json.dumps({
        "training_file": training_file.id,
        "validation_file": validation_file.id,
        "job": job.id,
        "status": job.status,
        "model": args.model,
    }, indent=2))


if __name__ == "__main__":
    main()
