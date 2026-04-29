# Fine-Tuning Repository Layout

## Git-Tracked Files

The GitHub repository should contain source code, reusable scripts, curated small examples, and human-readable reports.

Tracked fine-tuning-related files live in:

```text
samples/fine_tuning/
samples/raw_samples/
samples/traced_samples/
scripts/
docs/fine_tuning/
```

These are small enough to review and useful for reproducing or understanding the instrumentation workflow.

## Ignored Local Workspace

Generated datasets, large imports, evaluation outputs, and API-produced artifacts live under:

```text
datasets/
```

This directory is intentionally ignored by Git. It is the local working area for:

- generated JSONL files,
- train/validation splits,
- evaluation candidates,
- result JSON files,
- fine-tuning job metadata,
- filtered CodeNet subsets,
- expanded local batches.

## Project_CodeNet

`Project_CodeNet/` is a large local source dataset and should not be included in the GitHub repository.

The folder is ignored in `.gitignore`:

```text
Project_CodeNet/
```

It has also been removed from Git tracking with:

```text
git rm -r --cached Project_CodeNet
```

This keeps the local files on disk while removing them from future commits.

## Canonical Local Fine-Tuning Workspace

Use this local layout for active fine-tuning work:

```text
datasets/
  fine_tuning/
    array/
    array2d/
    graph/
    linked_list/
    queue/
    stack/
    tree/
    hash_map/
    doubly_linked_list/
    prompt_header_examples/
    claude_gfg_batch_01/
    claude_gfg_batch_02/
    claude_gfg_batch_03/
    github_batch_01/
    github_batch_02/
    github_batch_03/
    github_batch_04/
    github_batch_05/
    github_batch_06/
    github_batch_07/
  codenet_filtered/
  codenet_instrumented/
  fine_tuning_jsonl/
  evals/
```

The batch folder names are intentionally explicit because the generated manifests and reports refer to them.

## Script Support

`scripts/build_finetune_tranche.py` now accepts configurable source roots:

```text
--fine-tuning-dir
--codenet-filtered-dir
--codenet-instrumented-dir
```

It also scans fine-tuning examples recursively, so future local reorganization can use deeper source-specific folders without requiring another script rewrite.

For example, a future local layout like this is now supported:

```text
datasets/fine_tuning/
  curated/array/
  curated/graph/
  imported/claude_gfg/batch_01/
  imported/github/anish_lohiya_dsa/
```

If the dataset is reorganized in this deeper format, rebuild the JSONL and manifest files afterward so artifact paths stay accurate.

## Current Recommendation

Do not move the completed `algoscope_sft_500` source folders until a new dataset version is intentionally rebuilt.

Reason: the existing manifests and evaluation reports point to the current local paths. Moving the local data first would make old manifests harder to rerun. The safer path is:

1. Keep the completed `algoscope_sft_500` layout stable.
2. Use the new recursive source-root support for the next dataset version.
3. Rebuild the JSONL, split manifests, and evaluation manifests after any local folder move.
