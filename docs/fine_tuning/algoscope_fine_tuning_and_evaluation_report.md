# AlgoScope Fine-Tuning and Evaluation Report

## Purpose

This document centralizes the work completed for the AlgoScope C instrumentation fine-tuning effort: dataset expansion, validation, fine-tuning job creation, model deployment wiring, baseline testing, fine-tuned model testing, and metric reporting.

## Final Model

The successful fine-tuned model is:

```text
ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd
```

It was fine-tuned from the baseline model:

```text
gpt-4.1-mini-2025-04-14
```

The runtime app instrumentation path now defaults to this fine-tuned model in:

```text
backend/ml/instrumenter.py
```

The runtime model can still be overridden with:

```text
ALGOSCOPE_INSTRUMENTATION_MODEL
```

The runtime prompt mode can be overridden with:

```text
ALGOSCOPE_INSTRUMENTATION_PROMPT_MODE
```

For fine-tuned models, the default prompt mode is `sft`, matching the compact training format.

## Dataset Construction

The final dataset is:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500.jsonl
```

It contains 500 total supervised fine-tuning examples.

The final split is:

| Split | File | Count |
| --- | --- | ---: |
| Train | `datasets/fine_tuning_jsonl/algoscope_sft_500_train.jsonl` | 400 |
| Validation/test | `datasets/fine_tuning_jsonl/algoscope_sft_500_validation.jsonl` | 100 |

The split manifest is:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500_split_manifest.csv
```

The evaluation validation manifest is:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500_eval_validation_manifest.csv
```

## Dataset Additions Completed

The dataset was expanded in several batches.

### Manual 30-File Batch

Added 30 manually instrumented files under:

```text
datasets/fine_tuning/github_batch_06/
```

These included GFG/top50/GitHub-style C examples across arrays, graphs, trees, stacks, linked lists, and sorting-related categories.

Validation completed:

| Check | Result |
| --- | ---: |
| Source preservation | 30/30 |
| Instrumented compile | 30/30 |

This produced:

```text
datasets/fine_tuning_jsonl/algoscope_sft_451.jsonl
```

### AnishLohiya/DSA GitHub Batch

Imported and instrumented C files from:

```text
https://github.com/AnishLohiya/DSA
```

Added 27 raw/instrumented pairs under:

```text
datasets/fine_tuning/github_batch_07/
```

One upstream issue was handled in the instrumented copy: `Searching/JumpSearch.c` defined `JumpSearch` but called `jump_search`, so the instrumented file added a macro alias while preserving the raw source.

Validation completed:

| Check | Result |
| --- | ---: |
| Source preservation | 27/27 |
| Instrumented compile | 27/27 |

This produced:

```text
datasets/fine_tuning_jsonl/algoscope_sft_478.jsonl
```

### Claude Code 20-File Batch

Added the next 20 already instrumented examples from the Claude Code GFG set.

Source:

```text
samples/fine_tuning/gfg/
```

Destination:

```text
datasets/fine_tuning/claude_gfg_batch_03/
```

These covered examples 41 through 60 from the GFG batch.

Validation completed:

| Check | Result |
| --- | ---: |
| Source preservation | 20/20 |
| Instrumented compile | 20/20 |

This produced:

```text
datasets/fine_tuning_jsonl/algoscope_sft_498.jsonl
```

### Two Generated Graph Files

Created two new graph examples:

```text
datasets/fine_tuning/graph/11_adjacency_list_raw.c
datasets/fine_tuning/graph/11_adjacency_list_instrumented.c
datasets/fine_tuning/graph/12_adjacency_matrix_raw.c
datasets/fine_tuning/graph/12_adjacency_matrix_instrumented.c
```

The adjacency-list example traces graph nodes, graph edges, highlights, and related scalar variables.

The adjacency-matrix example traces graph nodes/edges and also uses 2D array tracing through:

```c
trace_array2d_init(...)
trace_array2d(...)
trace_array2d_highlight(...)
```

Validation completed:

| Check | Result |
| --- | ---: |
| Source preservation | 2/2 |
| Raw compile | 2/2 |
| Instrumented compile | 2/2 |

This produced the final 500-example dataset:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500.jsonl
```

## Dataset Validation and Split

The final split was corrected to 80/20:

| Use | Count |
| --- | ---: |
| Fine-tuning | 400 |
| Testing/validation | 100 |

Final files:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500_train.jsonl
datasets/fine_tuning_jsonl/algoscope_sft_500_validation.jsonl
datasets/fine_tuning_jsonl/algoscope_sft_500_manifest.csv
datasets/fine_tuning_jsonl/algoscope_sft_500_split_manifest.csv
datasets/fine_tuning_jsonl/algoscope_sft_500_validation_report.json
```

The dry-run fine-tune creation check passed before submitting the job.

## Fine-Tuning Jobs

### First Job

The first fine-tuning job was created with:

```text
ftjob-HvGO1vjKGBCgFLI7s8YXkyec
```

Metadata:

```text
datasets/fine_tuning_jsonl/algoscope_sft_job_2026-04-29.json
```

Training file:

```text
file-WoRW5ResCwLugVNbJ9miYm
```

Validation file:

```text
file-1fPNrnsenE1jsUm5ejYZs7
```

This job failed due to quota:

```text
exceeded_quota
```

The job cost estimate was USD 5.13, but the available project quota at the time was USD 0.57.

### Retry Job

After credits were added, a new fine-tuning job was created:

```text
ftjob-AlmJdkEyXyVOw2WhNxTqbGZo
```

Metadata:

```text
datasets/fine_tuning_jsonl/algoscope_sft_job_retry_2026-04-29.json
```

Training file:

```text
file-8gMQB33RZ6du7pHLNGPsLJ
```

Validation file:

```text
file-86hBcrgC1q6nD9p3ST5XZS
```

The retry job succeeded.

Result file:

```text
file-DUipMSqyBU5NLQyBo77snN
```

Fine-tuned model:

```text
ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd
```

## Runtime Integration

The backend instrumentation wrapper was updated in:

```text
backend/ml/instrumenter.py
```

Changes made:

- Added `INSTRUMENTATION_MODEL`.
- Added `INSTRUMENTATION_PROMPT_MODE`.
- Defaulted runtime instrumentation to the successful fine-tuned model.
- Used compact SFT prompt messages when the model starts with `ft:`.
- Kept the previous long prompt-header path available for baseline-style runs.
- Kept line-number cleanup only for non-SFT prompt mode.

This lets the app use the fine-tuned model by default while still allowing controlled baseline comparison.

## Evaluation Scripts and Helpers

Existing evaluation scripts used:

```text
scripts/run_instrumentation_model_eval.py
scripts/evaluate_instrumentation_output.py
scripts/filter_eval_manifest.py
```

New summarizer added:

```text
scripts/summarize_ds_init_metrics.py
```

The summarizer computes:

- Exact initializer object precision, recall, and F1.
- Normalized kind+name precision, recall, and F1.
- Kind-only precision, recall, and F1.
- Kind-set precision, recall, and F1.
- Category-hit rate.

It also supports combined summaries across multiple result directories, which was needed because the baseline run was completed in two parts.

## Evaluation Setup

The fine-tuned model was evaluated on all 100 validation files using:

```text
model: ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd
mode: sft
temperature: 0
```

The baseline model was evaluated on all 100 validation files using:

```text
model: gpt-4.1
mode: prompt
temperature: 0
```

The baseline was completed in two runs:

| Run | Directory | Count |
| --- | --- | ---: |
| Initial baseline run | `datasets/evals/prompt_gpt-4.1` | 89 |
| Tail baseline run | `datasets/evals_tail_90_100/prompt_gpt-4.1` | 11 |

The tail manifest was:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500_eval_validation_tail_90_100_manifest.csv
```

## Strict Evaluation Results

Strict results compare exact data-structure initializer objects against the reference instrumented file. Exact matching requires both initializer kind and object name to match.

| Model | Files | Compile OK | Raw lines preserved | Exact important DS initialized |
| --- | ---: | ---: | ---: | ---: |
| Fine-tuned model | 100 | 94/100 | 90/100 | 80/100 |
| `gpt-4.1` baseline | 100 | 82/100 | 38/100 | 37/100 |

## Looser DS Initialization Results

The strict metric is useful, but it is brittle. The looser metrics better answer whether the important data-structure type was initialized.

| Model | Exact object F1 | Kind+name recall | Kind-only recall | Kind-set recall | Category hit |
| --- | ---: | ---: | ---: | ---: | ---: |
| Fine-tuned model | 78.2% | 76.1% | 87.6% | 90.3% | 82/86 |
| `gpt-4.1` baseline | 34.8% | 36.3% | 61.1% | 62.1% | 60/86 |

Metric meanings:

- `Exact object F1`: requires initializer kind and object name to match.
- `Kind+name recall`: normalizes `array_bars` to `array` but still requires object names to match.
- `Kind-only recall`: ignores names and checks whether expected DS kinds were initialized.
- `Kind-set recall`: compares the set of expected DS kinds per file, ignoring names and duplicate counts.
- `Category hit`: passes if at least one expected DS kind appears for files with expected DS initializers.

The most useful metric for this project is likely `kind-only recall`, because AlgoScope primarily needs the important data-structure type initialized so the visualizer has a renderable object.

## Interpretation

The fine-tuned model is substantially better than the baseline for AlgoScope instrumentation.

Key improvements:

- Compile success improved from 82% to 94%.
- Source preservation improved from 38% to 90%.
- Exact important-DS initialization improved from 37% to 80%.
- Kind-only DS recall improved from 61.1% to 87.6%.
- Category hit improved from 60/86 to 82/86.

The preservation improvement is especially important because instrumentation should add tracer calls without rewriting or deleting the user's original C code.

The looser DS metrics show that even when exact object names differ, the fine-tuned model more often initializes the important data-structure categories needed by the visualizer.

## Remaining Limitations

The evaluation does not yet fully measure visualization quality.

Current metrics check:

- Whether generated C compiles.
- Whether original source lines are preserved.
- Whether expected DS initializer calls appear.

They do not yet fully measure:

- Whether every update operation is traced.
- Whether highlights are placed at the best program points.
- Whether graph/tree/list edges are updated with perfect timing.
- Whether stack and queue operations are semantically complete.
- Whether the visual timeline is pedagogically ideal.

Those would require a deeper execution-trace quality evaluator or human review.

## Important Artifacts

Final dataset:

```text
datasets/fine_tuning_jsonl/algoscope_sft_500.jsonl
datasets/fine_tuning_jsonl/algoscope_sft_500_train.jsonl
datasets/fine_tuning_jsonl/algoscope_sft_500_validation.jsonl
datasets/fine_tuning_jsonl/algoscope_sft_500_split_manifest.csv
```

Fine-tuning metadata:

```text
datasets/fine_tuning_jsonl/algoscope_sft_job_2026-04-29.json
datasets/fine_tuning_jsonl/algoscope_sft_job_retry_2026-04-29.json
```

Fine-tuned results:

```text
datasets/evals/sft_ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd
```

Baseline results:

```text
datasets/evals/prompt_gpt-4.1
datasets/evals_tail_90_100/prompt_gpt-4.1
datasets/evals/prompt_gpt-4.1_combined_100_summary.json
```

Metric summaries and reports:

```text
datasets/evals/algoscope_sft_500_ds_init_metrics.json
datasets/evals/prompt_gpt-4.1_combined_100_ds_init_metrics.json
datasets/evals/algoscope_sft_500_quick_comparison.md
datasets/evals/algoscope_sft_500_results_discussion.md
```

Runtime integration:

```text
backend/ml/instrumenter.py
```

Technology stack note:

```text
tech_stack.md
```

## Verification Performed

Local Python syntax checks:

```text
venv/bin/python -m py_compile backend/ml/instrumenter.py
venv/bin/python -m py_compile scripts/summarize_ds_init_metrics.py
```

Backend validator test:

```text
cd backend
../venv/bin/python -m unittest test_validator.py
```

Result:

```text
23 tests passed
```

## Current Status

The fine-tuning workflow is complete.

The new fine-tuned model is trained, tested on the full 100-file validation set, compared against a full 100-file `gpt-4.1` baseline, and wired into the backend instrumentation path.

Recommended default model:

```text
ft:gpt-4.1-mini-2025-04-14:personal:algoscope-instrumenter:DZxrdcOd
```

Recommended headline metric:

```text
Kind-only DS recall: 87.6%
```

Recommended strict metric:

```text
Exact important DS initialized: 80/100
```
