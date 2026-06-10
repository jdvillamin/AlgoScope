# Datasets

## Overview

The `samples/` directory contains C source files used for demonstration and LLM fine-tuning. All samples are designed for visualization, so data sizes must remain small enough to render clearly on a canvas.

## Directory Structure

```
samples/
  raw_samples/          # Standalone demo programs (editor preloads)
  traced_samples/       # Pre-instrumented versions of raw_samples
  fine_tuning/          # Paired raw + instrumented files for LLM fine-tuning
    array/              # 10 pairs (20 files)
    array2d/            # 20 pairs (40 files)
    doubly_linked_list/ # 10 pairs (20 files)
    graph/              # 10 pairs (20 files)
    hash_map/           # 10 pairs (20 files)
    linked_list/        # 10 pairs (20 files)
    queue/              # 10 pairs (20 files)
    stack/              # 10 pairs (20 files)
    tree/               # 10 pairs (20 files)
```

## Fine-Tuning Samples

Each fine-tuning subdirectory contains numbered pairs:

- `NN_description_raw.c` — the original C program (no tracing)
- `NN_description_instrumented.c` — the same program with `trace_*()` calls inserted

These pairs train the LLM to produce correct instrumented code given raw C input. The instrumented file must follow every rule in `backend/ml/prompt_header.py`.

**The live training corpus is `datasets/fine_tuning/`** (the default source for
`scripts/build_finetune_tranche.py`, which validates pairs — raw lines preserved
in order, tracer markers present, compiles against `tracer/` — and assembles the
JSONL tranches in `datasets/fine_tuning_jsonl/`). It is a superset of
`samples/fine_tuning/` and additionally holds the `claude_gfg_batch_*` /
`github_batch_*` batches and `red_black_tree/` (6 pairs covering colored-node
builds, rotations, CLRS insert/delete fixups, and search across the common color
conventions: `char 'R'/'B'`, `enum { RED, BLACK }`, and `int isRed`, with both
NULL children and NIL-sentinel styles). The deployed fine-tuned instrumenter
model only knows the trace calls present in this corpus — when a new trace
function is added (e.g. `trace_btree_color`), add pairs here and retrain, since
`backend/ml/prompt_header.py` is only used by the non-fine-tuned prompt mode.

## Constant Size Constraints

**When creating or editing sample files, or when encountering user-submitted programs with excessively large constants, reduce them to at most 20.**

This applies to:

- Array sizes: `int arr[10000]` -> `int arr[20]`
- Loop bounds: `for (i = 0; i < 1000; i++)` -> `for (i = 0; i < 10; i++)`
- `#define` constants: `#define MAX 500` -> `#define MAX 10`
- Matrix dimensions: `int mat[100][100]` -> `int mat[4][4]`
- Graph vertex counts: `#define MAX_V 200` -> `#define MAX_V 10`
- Hash table sizes: `#define SIZE 1000` -> `#define SIZE 7`
- Any other numeric constant controlling data structure size

**Why:** The tracer emits one JSON event per state change. Large constants produce thousands of trace events, which overwhelms the 5-second execution timeout, floods the frontend with unrenderable steps, and makes the visualization useless. The existing samples use sizes between 3 and 20 (arrays of 5-10 elements, 3x3 to 4x5 matrices, graphs with 4-6 vertices, hash tables of size 7, stacks/queues with MAX 10-20).

**How to apply:** When a raw C program uses constants larger than 20 for data structure sizes, scale them down proportionally while preserving the algorithm's logic. Choose values that demonstrate the algorithm clearly: 5-10 for arrays, 3x3 or 4x4 for matrices, 4-6 for graph vertices, 7 for hash tables. Adjust the corresponding data (initializer lists, loop bounds, input values) to match the reduced sizes. The actual values stored in elements can remain large (e.g., `arr[i] = 999` is fine) — only the sizes/counts that control how many elements exist need to be capped.
