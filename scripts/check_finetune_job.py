#!/usr/bin/env python3
import argparse
import json
import os


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("job_id")
    args = parser.parse_args()

    if not os.getenv("OPENAI_API_KEY"):
        raise SystemExit("OPENAI_API_KEY is not set")

    from openai import OpenAI

    client = OpenAI()
    job = client.fine_tuning.jobs.retrieve(args.job_id)
    print(json.dumps({
        "id": job.id,
        "status": job.status,
        "model": job.model,
        "fine_tuned_model": job.fine_tuned_model,
        "training_file": job.training_file,
        "validation_file": job.validation_file,
        "result_files": job.result_files,
        "created_at": job.created_at,
        "finished_at": job.finished_at,
    }, indent=2))


if __name__ == "__main__":
    main()
