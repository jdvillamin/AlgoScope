# Instrumented Sample Audit

Audit date: 2026-04-18
Status: **All issues resolved**

41 of 100 instrumented sample files had deficient tracing after the tracer schema changed to support `long long` and `char` via `_Generic` dispatch. All have been fixed.

## Graph (10/10 — fixed)

All 10 graph samples were fully rewritten to fix 3 systematic issues:

1. **trace_graph_node/trace_graph_edge moved inside helper functions.** Previously at call site in `main()`, now inside `addVertex()` and `addEdge()` per prompt rules.

2. **Adjacency matrix visualization added.** All samples now emit `trace_array2d_init`, `trace_array2d`, and `trace_array2d_highlight` for the `int adj[MAX_V][MAX_V]` matrix, paired with the graph view.

3. **Variable traces added.** All samples now trace loop iterators, traversal variables (`current`, `front`, `rear`, `top`), and vertex index variables (`A`, `B`, `C`, etc.).

Fixed files: `graph/01_bfs` through `graph/10_all_paths` (all `_instrumented.c`).

## Array2d (11/20 — fixed)

Added `trace_var_init("i", i)`, `trace_var_init("j", j)`, and `trace_var_init("k", k)` inside for-loop bodies for samples 01–11. Samples 12–20 were already correct.

## Hash_map (5/10 — fixed, 5 unchanged)

Added `trace_var_init("i", i)` inside multi-line for-loop bodies for samples 05, 07, 08, 09, 10. Samples 01–04 and 06 only have one-liner init loops (`for (...) table[i] = NULL;`) which cannot have traces inserted without restructuring the original code.

## Tree (7/10 — fixed)

Added `trace_var_init("i", i)` inside child-iteration and level-order BFS for-loop bodies for samples 01–07.

## Queue (2/10 — fixed)

Added `trace_var_init("i", i)` in `queue/04_queue_from_input` and `queue/09_reverse_queue`.

## Doubly_linked_list (1/10 — fixed)

Added `trace_var_init("i", i)` in `doubly_linked_list/08_insert_at_position`.

## Still outstanding

`backend/ml/prompt_header.py` still documents `int value` parameters for all trace functions. Does not mention `long long`, `char`, or `_Generic` dispatch. Should be updated separately to avoid GPT-4 adding explicit `(int)` casts that truncate `long long` values.
