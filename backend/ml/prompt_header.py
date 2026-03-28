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
trace_array_highlight(char* name, int index)

Rules:

Initialize once after declaration.

int arr[5];
trace_array_init("arr", 5);

Trace every write.

arr[i] = value;
trace_array("arr", i, arr[i]);

Highlight the element currently being accessed, compared, or swapped.
Call trace_array_highlight each time the algorithm inspects or modifies an element.

trace_array_highlight("arr", i);

Example (linear search):

for (int i = 0; i < n; i++) {
    trace_array_highlight("arr", i);
    if (arr[i] == target) {
        found = i;
        break;
    }
}

Example (bubble sort inner loop):

if (arr[j] > arr[j + 1]) {
    trace_array_highlight("arr", j);
    int temp = arr[j];
    arr[j] = arr[j + 1];
    arr[j + 1] = temp;
    trace_array("arr", j, arr[j]);
    trace_array("arr", j + 1, arr[j + 1]);
}

==================================================
2D ARRAY TRACES
==================================================

trace_array2d_init(char* name, int rows, int cols)
trace_array2d(char* name, int r, int c, int value)
trace_array2d_highlight(char* name, int r, int c)

Rules:

Initialize after declaration.

int mat[3][5];
trace_array2d_init("mat", 3, 5);

Trace cell writes.

mat[r][c] = value;
trace_array2d("mat", r, c, mat[r][c]);

Highlight the cell currently being accessed or compared.

trace_array2d_highlight("mat", r, c);

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

trace_dll_init(char* name)
trace_dll_node(char* list, char* id, int value)
trace_dll_next_link(char* list, char* from, char* to)
trace_dll_prev_link(char* list, char* from, char* to)
trace_dll_next_unlink(char* list, char* from, char* to)
trace_dll_prev_unlink(char* list, char* from, char* to)
trace_dll_pointer(char* list, char* name, char* target)
trace_dll_highlight(char* list, char* id)
trace_dll_free(char* list, char* id)

Rules:

Initialize list BEFORE any node events.

trace_dll_init("dll");

A node becomes "ready" only after BOTH id and value are initialized.

Correct order:

strcpy(node->id, "n1");
node->value = 5;
trace_dll_node("dll", node->id, node->value);

Forward (next) pointer connections:

node1->next = node2;
trace_dll_next_link("dll", node1->id, node2->id);

Backward (prev) pointer connections:

node2->prev = node1;
trace_dll_prev_link("dll", node2->id, node1->id);

IMPORTANT: trace_dll_prev_link takes (list, from, to) where "from" is the node
whose prev pointer is being SET, and "to" is the node it points back to.
So if b->prev = a, call trace_dll_prev_link("dll", b->id, a->id).

Forward unlink (when removing a next connection):

trace_dll_next_unlink("dll", node1->id, node2->id);
node1->next = node2->next;

Backward unlink (when removing a prev connection):

trace_dll_prev_unlink("dll", node2->id, node1->id);
node2->prev = node1->prev;

Traversal pointers:

trace_dll_pointer("dll", "curr", node->id);

Traversal highlight:

trace_dll_highlight("dll", node->id);

Free nodes BEFORE calling free():

trace_dll_free("dll", node->id);
free(node);

Do NOT use trace_var_init or trace_var for pointer variables used in doubly linked lists,
such as head, tail, temp, curr, prev, or nextNode.

These pointers must be traced using trace_dll_pointer instead.

Example:

Node* temp = head;

Correct:
trace_dll_pointer("dll", "temp", temp->id);

Incorrect:
trace_var_init("temp", (int)(uintptr_t)temp);

Example (full insertion at tail):

trace_dll_init("dll");

Node* n1 = malloc(sizeof(Node));
strcpy(n1->id, "n1");
n1->value = 10;
n1->next = NULL;
n1->prev = NULL;
trace_dll_node("dll", n1->id, n1->value);
trace_dll_pointer("dll", "head", n1->id);
trace_dll_pointer("dll", "tail", n1->id);

Node* n2 = malloc(sizeof(Node));
strcpy(n2->id, "n2");
n2->value = 20;
n2->next = NULL;
trace_dll_node("dll", n2->id, n2->value);

n1->next = n2;
trace_dll_next_link("dll", n1->id, n2->id);

n2->prev = n1;
trace_dll_prev_link("dll", n2->id, n1->id);

trace_dll_pointer("dll", "tail", n2->id);

/* Deletion of n1: */
trace_dll_next_unlink("dll", n1->id, n2->id);
n2->prev = NULL;
trace_dll_prev_unlink("dll", n2->id, n1->id);
trace_dll_pointer("dll", "head", n2->id);
trace_dll_free("dll", n1->id);
free(n1);

==================================================
STACK TRACES
==================================================

Signatures:

trace_stack_init(char* name)
trace_stack_push(char* name, int value)
trace_stack_pop(char* name)
trace_stack_top(char* name, int value)

Rules:

1. Call trace_stack_init ONCE before any push or pop traces.

2. Call trace_stack_push AFTER the value has been written to the stack array.
   Pass the value that was pushed.

3. Call trace_stack_pop BEFORE decrementing top.
   Do NOT pass the value — the visualizer removes the top element automatically.

4. Call trace_stack_top only when explicitly peeking at the top element without popping.
   Pass the current top value.

Example:

trace_stack_init("S");

/* push */
top++;
stack[top] = 5;
trace_stack_push("S", 5);

/* pop */
trace_stack_pop("S");
top--;

==================================================
QUEUE TRACES
==================================================

Signatures:

trace_queue_init(char* name)
trace_queue_enqueue(char* name, int value)
trace_queue_dequeue(char* name)
trace_queue_front(char* name, int value)
trace_queue_rear(char* name, int value)

Rules:

1. Call trace_queue_init ONCE before any enqueue or dequeue traces.

2. Call trace_queue_enqueue AFTER the value has been written to the queue array.
   Pass the value that was enqueued.

3. Call trace_queue_dequeue BEFORE incrementing front.
   Do NOT pass the value — the visualizer removes the front element automatically.

4. Call trace_queue_front and trace_queue_rear only when explicitly reading the
   front or rear pointer values without modifying the queue.

Example:

trace_queue_init("Q");

/* enqueue */
rear++;
queue[rear] = 10;
trace_queue_enqueue("Q", 10);

/* dequeue */
trace_queue_dequeue("Q");
front++;

==================================================
HASH TABLE TRACES
==================================================

Signatures:

trace_hash_init(char* name, int size)
trace_hash_put(char* name, int key, int value, int index)
trace_hash_remove(char* name, int key, int index)

Rules:

1. Call trace_hash_init ONCE before any put or remove traces.
   Pass the total number of buckets as size.

2. Call trace_hash_put AFTER the new node has been fully inserted into the bucket chain.
   Pass the key, value, and the bucket index returned by the hash function.

3. Call trace_hash_remove AFTER the node has been unlinked but BEFORE calling free().
   Pass the key and bucket index.

4. The bucket index must always be the result of the hash function — never a raw pointer or array offset.

Example:

trace_hash_init("H", SIZE);

/* put */
int index = hash(key);
/* ... build and link newNode ... */
trace_hash_put("H", key, value, index);

/* remove */
int index = hash(key);
/* ... unlink node from chain ... */
trace_hash_remove("H", key, index);
free(node);

==================================================
TREE TRACES
==================================================

Signatures:

trace_tree_init(char* name)
trace_tree_node(char* tree, char* id, char* value)
trace_tree_edge(char* tree, char* parent_id, char* child_id)
trace_tree_highlight(char* tree, char* id)

Rules:

1. Call trace_tree_init ONCE before any node or edge traces.

2. Call trace_tree_node after the node's id and value strings are set.
   id must be a unique string identifier for the node (e.g., "n1", "root").
   value is the display string shown inside the node in the visualization.
   Both id and value must be char* (string), not integers.

3. Call trace_tree_edge after the parent-child relationship is established.
   The parent node must already be registered with trace_tree_node.
   Pass the parent's id string, then the child's id string.

4. MANDATORY: Call trace_tree_highlight every time a traversal visits a node.
   This applies to ALL traversal patterns — preorder, inorder, postorder, or level-order.
   Place it immediately at the start of the traversal function, after the NULL check.
   Do NOT skip this call. Every visited node MUST be highlighted.

5. Ordering requirement:
   trace_tree_init → trace_tree_node (register node) → trace_tree_edge (connect to parent)
   A child node must be registered before the edge connecting it to its parent.

Traversal highlight patterns:

Preorder (recursive) — highlight at the start, before processing children:

void preorder(Node* node) {
    if (node == NULL) return;
    trace_tree_highlight("T", node->id);
    printf("%s ", node->value);
    for (int i = 0; i < node->childCount; i++) {
        preorder(node->children[i]);
    }
}

Inorder (binary tree) — highlight before processing the node's value:

void inorder(Node* node) {
    if (node == NULL) return;
    inorder(node->left);
    trace_tree_highlight("T", node->id);
    printf("%s ", node->value);
    inorder(node->right);
}

Postorder (recursive) — highlight after processing children:

void postorder(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->childCount; i++) {
        postorder(node->children[i]);
    }
    trace_tree_highlight("T", node->id);
    printf("%s ", node->value);
}

Level-order (BFS) — highlight immediately after dequeue:

queue[rear++] = root;
while (front < rear) {
    Node* current = queue[front++];
    trace_tree_highlight("T", current->id);
    for (int i = 0; i < current->childCount; i++) {
        queue[rear++] = current->children[i];
    }
}

Example (tree construction):

trace_tree_init("T");

Node* root = malloc(sizeof(Node));
strcpy(root->id, "root");
strcpy(root->value, "A");
trace_tree_node("T", root->id, root->value);

Node* child = malloc(sizeof(Node));
strcpy(child->id, "n1");
strcpy(child->value, "B");
trace_tree_node("T", child->id, child->value);
trace_tree_edge("T", root->id, child->id);

==================================================
GRAPH TRACES
==================================================

Signatures:

trace_graph_init(char* name)
trace_graph_node(char* graph, char* id)
trace_graph_edge(char* graph, char* from_id, char* to_id)
trace_graph_highlight(char* graph, char* id)

Rules:

1. Call trace_graph_init ONCE before any node or edge traces.

2. Call trace_graph_node after the vertex's string id field is set.
   The id argument must be the string identifier of the vertex, NOT an integer index.
   Call it once per vertex, as soon as the vertex is ready.

3. Call trace_graph_edge after the adjacency link is established in the data structure.
   Both from_id and to_id must be string IDs previously registered with trace_graph_node.
   Do NOT pass integer indices — pass the string vertex IDs.

4. MANDATORY: Call trace_graph_highlight every time a traversal visits a node.
   This applies to ALL traversal patterns — BFS, DFS, or any loop that processes vertices.
   Place it immediately after the node is dequeued, popped, or selected as current.
   Do NOT skip this call. Every visited node MUST be highlighted.
   Pass the string ID of the node being visited, not its index.

5. Ordering requirement:
   trace_graph_init → trace_graph_node (all vertices) → trace_graph_edge (all edges)
   A node must be registered before any edge that references it.

Traversal highlight patterns:

BFS — highlight immediately after dequeue:

int current = queue[front++];
trace_graph_highlight("G", g.vertices[current].id);

DFS (iterative) — highlight immediately after pop:

int current = stack[top--];
trace_graph_highlight("G", g.vertices[current].id);

DFS (recursive) — highlight at the start of the recursive call:

void dfs(Graph* g, int v) {
    trace_graph_highlight("G", g->vertices[v].id);
    ...
}

Example (full BFS):

trace_graph_init("G");

int A = addVertex(&g, "A");
trace_graph_node("G", g.vertices[A].id);

int B = addVertex(&g, "B");
trace_graph_node("G", g.vertices[B].id);

addEdge(&g, A, B);
trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);

/* Inside BFS loop: */
int current = queue[front++];
trace_graph_highlight("G", g.vertices[current].id);

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
