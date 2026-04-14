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
9. Do NOT restructure ANY code. Never extract declarations out of for-loop headers.
   If the original code says `for (int i = 0; ...)`, keep it exactly as `for (int i = 0; ...)`.
   Do NOT split it into `int i = 0;` followed by `for (i = 0; ...)` or any other form.
   Every original statement must remain in its original syntactic form.
10. Only INSERT new trace statements. You may only add lines BETWEEN existing lines.
11. If any trace call is inserted, ensure `#include "tracer.h"` is present at the top.
12. Output ONLY valid C code.
13. Do NOT output explanations, comments, or markdown.
14. If you are uncertain whether to keep a line — KEEP IT.

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

CRITICAL — Variables populated via scanf or other input:

When a variable receives its value from scanf (or similar input functions),
insert trace_var_init (or trace_var if already initialized) AFTER the scanf call.
The variable has no meaningful value until scanf writes to it, so trace it after.

Example:

int n;
scanf("%d", &n);
trace_var_init("n", n);

int a, b;
scanf("%d %d", &a, &b);
trace_var_init("a", a);
trace_var_init("b", b);

The same applies to arrays filled via scanf in a loop:

int arr[100];
trace_array_init("arr", n);
for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
    trace_array("arr", i, arr[i]);
}

Every variable or array element that receives data from input MUST be traced
immediately after the input call so the visualizer shows its value.

CRITICAL — Loop iterator variables:

For-loop iterators (i, j, k, etc.) change on EVERY iteration due to the
increment expression (e.g. i++). Because you cannot insert code inside
the for-header, you must trace the iterator at the TOP of the loop body,
AFTER the trace_line for the for-header. This captures the new value of
the iterator at the start of each iteration AND the initial value on the
first iteration.

When the variable is declared OUTSIDE the for-header:

int i = 0;
trace_var_init("i", i);
trace_line(<for_line>);
for (i = 0; i < 5; i++) {
    trace_line(<for_line>);
    trace_var("i", i);
    // ... loop body ...
}

When the variable is declared INSIDE the for-header (e.g. `for (int i = ...)`):
Do NOT extract the declaration. Keep the for-header exactly as written.
Use trace_var_init inside the loop body on the first iteration to register it.

trace_line(<for_line>);
for (int i = 0; i < 5; i++) {
    trace_line(<for_line>);
    trace_var_init("i", i);
    // ... loop body ...
}

Note: trace_var_init is safe to call multiple times — the visualizer will
treat subsequent calls as updates. This avoids restructuring the code.

For nested loops, trace EACH iterator at the top of its own loop body:

trace_line(<outer>);
for (int i = 0; i < n; i++) {
    trace_line(<outer>);
    trace_var_init("i", i);
    trace_line(<inner>);
    for (int j = 0; j < m; j++) {
        trace_line(<inner>);
        trace_var_init("j", j);
        // ... inner body ...
    }
}

The same rule applies to while loops — trace any variable that changes
each iteration at the top of the loop body.

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

Note that arrays can also be allocated in the heap. If the array is 
declared using an integer pointer, you must also visualize it.

int* arr = (int*)malloc(5 * sizeof(int));
trace_array_init("arr", 5);

If the array is declared with initial values, emit trace_array for EVERY
element immediately after trace_array_init so the visualizer shows the
pre-filled contents.

int arr[5] = {3, 7, 1, 9, 4};
trace_array_init("arr", 5);
trace_array("arr", 0, arr[0]);
trace_array("arr", 1, arr[1]);
trace_array("arr", 2, arr[2]);
trace_array("arr", 3, arr[3]);
trace_array("arr", 4, arr[4]);

Use a loop when the size comes from a variable or from stdin:

trace_array_init("arr", n);
for (int _i = 0; _i < n; _i++) { trace_array("arr", _i, arr[_i]); }

This rule applies to ALL initialized arrays — whether the values come from
an initializer list, a preceding input loop, or any other source. The
visualizer cannot see array contents until trace_array is called for each
index.

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

Note that 2D arrays can also be allocated in the heap. If a 2D array
is declared using int**, please visualize it as well.

int** mat[3][5] = (int**)malloc(3 * sizeof(int));
for (int i = 0; i < 3; i++) {
    mat[i] = (int*)malloc(5 * sizeof(int));
}
trace_array2d_init("mat", 3, 5);

If the 2D array is declared with initial values, emit trace_array2d for
EVERY cell immediately after trace_array2d_init.

int mat[2][3] = {{1,2,3},{4,5,6}};
trace_array2d_init("mat", 2, 3);
for (int _r = 0; _r < 2; _r++)
    for (int _c = 0; _c < 3; _c++)
        trace_array2d("mat", _r, _c, mat[_r][_c]);

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

Notes:

1. A graph can be represented using structs, but it can also be represented as
an adjacency matrix (a 2D array where adj[u][v] = 1 denotes an edge from u to v
and 0 denotes no edge) OR as an adjacency list (an array of linked lists where
adj[u] is a linked list of the neighbors of u).

2. If the adjacency matrix is symmetric (adj[u][v] == adj[v][u] for all u, v),
or if the adjacency list stores edges in both directions, visualize an
undirected graph instead of a directed graph.

3. MANDATORY: Whenever the source code uses an adjacency matrix or an
adjacency list to represent a graph, you MUST visualize BOTH the underlying
data structure (2D array or array of linked lists) AND the graph itself. The
two views must be kept in sync — every time the matrix/list is updated, emit
the corresponding graph event as well.

   a. Adjacency matrix — pair trace_array2d with trace_graph:

      trace_array2d_init("adj", n, n)   ← paired with →   trace_graph_init("adj")

      for (int i = 0; i < n; i++) {
          trace_graph_node("adj", _trace_id(i));
      }

      adj[u][v] = 1;   ← paired with →   trace_graph_edge("adj", _trace_id(u), _trace_id(v));

   b. Adjacency list — each vertex u owns its own linked list named "adj_u"
      (use the _trace_id helper or snprintf to build the name). You must
      ALSO emit a graph view named "adj" that mirrors the whole structure:

      trace_graph_init("adj");
      for (int i = 0; i < n; i++) {
          char list_name[32];
          snprintf(list_name, 32, "adj_%d", i);
          trace_ll_init(list_name);
          trace_graph_node("adj", _trace_id(i));
      }

      When you append neighbor v to adj[u] (i.e. create a new list node in
      "adj_u"), also emit the graph edge:

      trace_ll_node("adj_u", node_id, v);
      trace_ll_link("adj_u", prev_id, node_id);   // if not head
      trace_graph_edge("adj", _trace_id(u), _trace_id(v));

      Traversal highlighting must hit BOTH views: when visiting vertex u,
      call trace_graph_highlight("adj", _trace_id(u)); when scanning a
      neighbor node in the list, call trace_ll_highlight("adj_u", node_id).

Example (adjacency matrix):
#include <stdlib.h>
#include <stdio.h>
#include "tracer.h"

static char _trace_id_buffers[4096][32];
static int _trace_id_next = 0;

char* _trace_id(int x) {
    char* buf = _trace_id_buffers[_trace_id_next];
    _trace_id_next = (_trace_id_next + 1) % 4096;
    snprintf(buf, 32, "%d", x);
    return buf;
}

void dfs(int u, int n, int** adj, int* vis) {
    trace_var_init("u", u);
    trace_var_init("n", n);
    trace_graph_highlight("adj", _trace_id(u));
    trace_line(4);
    trace_array_highlight("vis", u);
    vis[u] = 1;
    trace_array("vis", u, vis[u]);
    trace_line(5);
    for (int v = 0; v < n; v++) {
        trace_line(5);
        trace_var_init("v", v);
        trace_line(6);
        trace_array2d_highlight("adj", u, v);
        trace_array_highlight("vis", v);
        if (adj[u][v] == 1 && vis[v] == 0) {
            trace_line(7);
            dfs(v, n, adj, vis);
        }
    }
}

int main() {
    int n, m;
    trace_line(14);
    scanf("%d %d", &n, &m);
    trace_var_init("n", n);
    trace_var_init("m", m);
    trace_line(15);
    int* vis = (int*)malloc(n * sizeof(int));
    trace_array_init("vis", n);
    trace_graph_init("adj");
    trace_line(16);
    for (int i = 0; i < n; i++) {
        trace_line(16);
        trace_var_init("i", i);
        trace_graph_node("adj", _trace_id(i));
        trace_line(17);
        vis[i] = 0;
        trace_array("vis", i, vis[i]);
    }
    trace_line(19);
    int** adj = (int**)malloc(n * sizeof(int*));
    trace_array2d_init("adj", n, n);
    trace_line(20);
    for (int i = 0; i < n; i++) {
        trace_line(20);
        trace_var_init("i", i);
        trace_line(21);
        adj[i] = (int*)malloc(n * sizeof(int));
        trace_line(22);
        for (int j = 0; j < n; j++) {
            trace_line(22);
            trace_var_init("j", j);
            trace_line(23);
            trace_array2d_highlight("adj", i, j);
            adj[i][j] = 0;
            trace_array2d("adj", i, j, adj[i][j]);
        }
    }
    trace_line(26);
    for (int i = 0; i < m; i++) {
        trace_line(26);
        trace_var_init("i", i);
        int u, v;
        trace_line(28);
        scanf("%d %d", &u, &v);
        trace_var_init("u", u);
        trace_var_init("v", v);
        trace_line(29);
        trace_array2d_highlight("adj", u, v);
        adj[u][v] = 1;
        trace_array2d("adj", u, v, adj[u][v]);
        trace_graph_edge("adj", _trace_id(u), _trace_id(v));
    }
    trace_line(31);
    dfs(0, n, adj, vis);
}

Example (adjacency list):
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tracer.h"

static char _trace_id_buffers[4096][32];
static int _trace_id_next = 0;

char* _trace_id(int x) {
    char* buf = _trace_id_buffers[_trace_id_next];
    _trace_id_next = (_trace_id_next + 1) % 4096;
    snprintf(buf, 32, "%d", x);
    return buf;
}

typedef struct Node {
    int v;
    int nid;
    struct Node* next;
} Node;

static int _next_nid = 0;

void dfs(int u, Node** adj, int* vis) {
    trace_var_init("u", u);
    trace_graph_highlight("adj", _trace_id(u));
    char list_u[32];
    snprintf(list_u, 32, "adj_%d", u);
    trace_line(4);
    trace_array_highlight("vis", u);
    vis[u] = 1;
    trace_array("vis", u, vis[u]);
    trace_line(5);
    for (Node* p = adj[u]; p != NULL; p = p->next) {
        trace_line(5);
        trace_ll_highlight(list_u, _trace_id(p->nid));
        trace_line(6);
        trace_array_highlight("vis", p->v);
        if (vis[p->v] == 0) {
            trace_line(7);
            dfs(p->v, adj, vis);
        }
    }
}

int main() {
    int n, m;
    trace_line(14);
    scanf("%d %d", &n, &m);
    trace_var_init("n", n);
    trace_var_init("m", m);

    trace_line(15);
    int* vis = (int*)malloc(n * sizeof(int));
    trace_array_init("vis", n);

    // Initialize one linked list per vertex AND a single graph view.
    trace_graph_init("adj");
    Node** adj = (Node**)malloc(n * sizeof(Node*));
    trace_line(16);
    for (int i = 0; i < n; i++) {
        trace_line(16);
        trace_var_init("i", i);
        adj[i] = NULL;
        char list_name[32];
        snprintf(list_name, 32, "adj_%d", i);
        trace_ll_init(list_name);
        trace_graph_node("adj", _trace_id(i));
        vis[i] = 0;
        trace_array("vis", i, vis[i]);
    }

    trace_line(20);
    for (int i = 0; i < m; i++) {
        trace_line(20);
        trace_var_init("i", i);
        int u, v;
        trace_line(22);
        scanf("%d %d", &u, &v);
        trace_var_init("u", u);
        trace_var_init("v", v);

        // Prepend v to adj[u]: create list node, link it, and mirror the
        // edge onto the graph view.
        Node* node = (Node*)malloc(sizeof(Node));
        node->v = v;
        node->nid = _next_nid++;
        node->next = adj[u];
        adj[u] = node;

        char list_u[32];
        snprintf(list_u, 32, "adj_%d", u);
        trace_ll_node(list_u, _trace_id(node->nid), v);
        if (node->next != NULL) {
            trace_ll_link(list_u, _trace_id(node->nid), _trace_id(node->next->nid));
        }
        trace_graph_edge("adj", _trace_id(u), _trace_id(v));
    }

    trace_line(30);
    dfs(0, adj, vis);
}

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
Do NOT rewrite, simplify, or restructure ANY original statement.
Do NOT extract declarations from for-loop headers or change any code's form.
Do NOT omit anything from the original source — not even blank lines.

Only insert trace statements between existing lines.

==================================================
SOURCE CODE
==================================================

{numbered_code}
""".strip()
