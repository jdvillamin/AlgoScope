PROMPT_HEADER = """
You are instrumenting a C program so its execution can be visualized.

Your task is to INSERT tracing calls into the code.

STRICT RULES
1. Preserve the original C program EXACTLY — every line, every character.
2. Do NOT delete ANY original line under any circumstance.
3. Do NOT modify, rewrite, or simplify ANY original line.
4. Do NOT remove or collapse ANY struct, union, or typedef definition.
5. Do NOT remove ANY function definition or declaration.
6. Do NOT remove ANY #include directive.
7. Do NOT remove ANY variable declaration, even if you think it is unused.
8. Do NOT reorder any original code — includes, structs, typedefs, functions, and statements must stay in their original order.
9. Only INSERT new trace statements. You may only add lines BETWEEN existing lines.
10. If any trace call is inserted, ensure `#include "tracer.h"` is present at the top.
11. Output ONLY valid C code.
12. Do NOT output explanations, comments, or markdown.
13. If you are uncertain whether to keep a line — KEEP IT.

==================================================
TRACE SYSTEM MODEL
==================================================

Each trace call emits a JSON event.

The frontend replays these events sequentially to build the program state
for visualization.

Trace calls must represent **visible state changes**.

Two categories exist:

1. Execution trace
2. Data structure traces

==================================================
EXECUTION TRACE
==================================================

trace_line(int line)

Purpose:
Highlight the currently executing source line.

Rule:
Insert `trace_line(L)` immediately BEFORE executing the statement on line L.

Example:

trace_line(12);
x = x + 1;

Never attach trace_line to:

- blank lines
- includes
- typedef
- struct definitions
- declarations without execution

==================================================
LOOP INSTRUMENTATION (CRITICAL)
==================================================

Loop headers cannot contain inserted statements.

Use the following pattern.

Original:

for (i = 0; i < n; i++) {
    body;
}

Instrumented:

trace_line(<for_line>);
for (i = 0; i < n; i++) {
    trace_line(<for_line>);
    body;
}

Explanation:
The first trace marks the initial evaluation.
The second simulates repeated condition checks.

Apply the same rule to:

- for
- while
- do-while

Nested loops follow the same rule independently.

==================================================
VARIABLE TRACES
==================================================

trace_var_init(char* name, int value)
trace_var(char* name, int value)

Rules:

Use trace_var_init when a variable is first initialized.

Example:

int x = 5;
trace_var_init("x", x);

Use trace_var when the variable value changes.

Example:

x = x + 1;
trace_var("x", x);

Loop variables must be traced when updated.

==================================================
ARRAY TRACES
==================================================

trace_array_init(char* name, int size)
trace_array(char* name, int index, int value)

Rules:

Initialize once after declaration.

int arr[5];
trace_array_init("arr", 5);

Trace every write.

arr[i] = value;
trace_array("arr", i, arr[i]);

==================================================
2D ARRAY TRACES
==================================================

trace_array2d_init(char* name, int rows, int cols)
trace_array2d(char* name, int r, int c, int value)

Rules:

Initialize after declaration.

int mat[3][5];
trace_array2d_init("mat", 3, 5);

Trace cell writes.

mat[r][c] = value;
trace_array2d("mat", r, c, mat[r][c]);

==================================================
SINGLY LINKED LIST TRACES
==================================================

trace_ll_init(char* name)
trace_ll_node(char* list, char* id, int value)
trace_ll_link(char* list, char* from, char* to)
trace_ll_free(char* list, char* id)
trace_ll_pointer(char* list, char* name, char* target)
trace_ll_highlight(char* list, char* id)

Rules:

Initialize list BEFORE any node events.

trace_ll_init("list");

A node becomes "ready" only after BOTH id and value are initialized.

Correct order:

strcpy(node->id, "n1");
node->value = 5;
trace_ll_node("list", node->id, node->value);

Next pointer connections:

node1->next = node2;
trace_ll_link("list", node1->id, node2->id);

Traversal pointers:

trace_ll_pointer("list", "curr", node->id);

Traversal highlight:

trace_ll_highlight("list", node->id);

Free nodes BEFORE calling free():

trace_ll_free("list", node->id);
free(node);

Do NOT use trace_var_init or trace_var for pointer variables used in linked lists,
such as head, temp, curr, prev, or nextNode.

These pointers must be traced using trace_ll_pointer instead.

Example:

Node* temp = head;

Correct:
trace_ll_pointer("list", "temp", temp->id);

Incorrect:
trace_var_init("temp", (int)(uintptr_t)temp);

==================================================
DOUBLY LINKED LIST TRACES
==================================================

trace_dll_init
trace_dll_node
trace_dll_next_link
trace_dll_prev_link
trace_dll_next_unlink
trace_dll_prev_unlink
trace_dll_pointer
trace_dll_highlight
trace_dll_free

Rules:

Forward link:

a->next = b;
trace_dll_next_link("dll", a->id, b->id);

Backward link:

b->prev = a;
trace_dll_prev_link("dll", b->id, a->id);

Pointer movement:

trace_dll_pointer("dll", "curr", curr->id);

==================================================
STACK TRACES
==================================================

trace_stack_init
trace_stack_push
trace_stack_pop
trace_stack_top

==================================================
QUEUE TRACES
==================================================

trace_queue_init
trace_queue_enqueue
trace_queue_dequeue
trace_queue_front
trace_queue_rear

==================================================
HASH TABLE TRACES
==================================================

trace_hash_init
trace_hash_put
trace_hash_remove

==================================================
TREE TRACES
==================================================

trace_tree_init
trace_tree_node
trace_tree_edge
trace_tree_highlight

==================================================
GRAPH TRACES
==================================================

trace_graph_init
trace_graph_node
trace_graph_edge
trace_graph_highlight

==================================================
INSTRUMENTATION STRATEGY
==================================================

Follow this process:

1. Identify which data structures exist.
2. Insert initialization traces once.
3. Insert mutation traces when structure state changes.
4. Insert pointer/highlight traces for traversal.
5. Insert trace_line before executable statements.
6. Preserve every original line.

==================================================
OUTPUT
==================================================

Return ONLY the final instrumented C program.

Do NOT explain anything.
Do NOT remove ANY original line, struct, function, include, or declaration.
Do NOT rewrite or simplify ANY original statement.
Do NOT omit anything from the original source — not even blank lines.

Only insert trace statements between existing lines.

==================================================
SOURCE CODE
==================================================

{numbered_code}
""".strip()
