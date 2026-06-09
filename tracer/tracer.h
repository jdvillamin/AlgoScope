#ifndef TRACER_H
#define TRACER_H

/* ── Implementation functions — do not call directly ────────────── */

void _trace_var_init_ll(char* name, long long value);
void _trace_var_init_char(char* name, char value);
void _trace_var_ll(char* name, long long value);
void _trace_var_char(char* name, char value);

void _trace_array_ll(char* name, int index, long long value);
void _trace_array_char(char* name, int index, char value);

void _trace_array2d_ll(char* name, int r, int c, long long value);
void _trace_array2d_char(char* name, int r, int c, char value);

void _trace_ll_node_ll(char* list, char* id, long long value);
void _trace_dll_node_ll(char* list, char* id, long long value);

void _trace_stack_push_ll(char* name, long long value);
void _trace_stack_top_ll(char* name, long long value);

void _trace_queue_enqueue_ll(char* name, long long value);
void _trace_queue_front_ll(char* name, long long value);
void _trace_queue_rear_ll(char* name, long long value);

void _trace_hash_put_ll(char* name, long long key, long long value, int index);
void _trace_hash_remove_ll(char* name, long long key, int index);

/* ── _Generic dispatch macros ───────────────────────────────────── */

#define _TRACE_IS_CHAR(x) _Generic((x), \
    char: 1, signed char: 1, unsigned char: 1, default: 0)

#define trace_var_init(name, value) _Generic((value), \
    char: _trace_var_init_char, \
    signed char: _trace_var_init_char, \
    unsigned char: _trace_var_init_char, \
    default: _trace_var_init_ll \
)(name, value)

#define trace_var(name, value) _Generic((value), \
    char: _trace_var_char, \
    signed char: _trace_var_char, \
    unsigned char: _trace_var_char, \
    default: _trace_var_ll \
)(name, value)

#define trace_array(name, index, value) _Generic((value), \
    char: _trace_array_char, \
    signed char: _trace_array_char, \
    unsigned char: _trace_array_char, \
    default: _trace_array_ll \
)(name, index, value)

#define trace_array2d(name, r, c, value) _Generic((value), \
    char: _trace_array2d_char, \
    signed char: _trace_array2d_char, \
    unsigned char: _trace_array2d_char, \
    default: _trace_array2d_ll \
)(name, r, c, value)

#define trace_ll_node(list, id, value) \
    _trace_ll_node_ll(list, id, (long long)(value))

#define trace_dll_node(list, id, value) \
    _trace_dll_node_ll(list, id, (long long)(value))

#define trace_stack_push(name, value) \
    _trace_stack_push_ll(name, (long long)(value))

#define trace_stack_top(name, value) \
    _trace_stack_top_ll(name, (long long)(value))

#define trace_queue_enqueue(name, value) \
    _trace_queue_enqueue_ll(name, (long long)(value))

#define trace_queue_front(name, value) \
    _trace_queue_front_ll(name, (long long)(value))

#define trace_queue_rear(name, value) \
    _trace_queue_rear_ll(name, (long long)(value))

#define trace_hash_put(name, key, value, index) \
    _trace_hash_put_ll(name, (long long)(key), (long long)(value), index)

#define trace_hash_remove(name, key, index) \
    _trace_hash_remove_ll(name, (long long)(key), index)

#define trace_rec_param(name, p, value) _Generic((value), \
    char: _trace_rec_param_char, \
    signed char: _trace_rec_param_char, \
    unsigned char: _trace_rec_param_char, \
    default: _trace_rec_param_ll \
)(name, p, value)

#define trace_rec_return(name, value) _Generic((value), \
    char: _trace_rec_return_char, \
    signed char: _trace_rec_return_char, \
    unsigned char: _trace_rec_return_char, \
    default: _trace_rec_return_ll \
)(name, value)

/* ── Functions without value parameters (no dispatch needed) ──── */

void trace_array_init(char* name, int size);
void trace_array_init_bars(char* name, int size);
void trace_array_highlight(char* name, int index);
void trace_array_cell(char* array_name, char* var_name, int index);

void trace_array2d_init(char* name, int rows, int cols);
void trace_array2d_highlight(char* name, int r, int c);
void trace_array2d_cell(char* array_name, char* var_name, int r, int c);

void trace_ll_init(char* name);
void trace_ll_link(char* list, char* from, char* to);
void trace_ll_free(char* list, char* id);
void trace_ll_pointer(char* list, char* name, char* target);
void trace_ll_highlight(char* list, char* id);

void trace_dll_init(char* name);
void trace_dll_next_link(char* list, char* from, char* to);
void trace_dll_prev_link(char* list, char* from, char* to);
void trace_dll_next_unlink(char* list, char* from, char* to);
void trace_dll_prev_unlink(char* list, char* from, char* to);
void trace_dll_highlight(char* list, char* id);
void trace_dll_pointer(char* list, char* name, char* target);
void trace_dll_free(char* list, char* id);

void trace_stack_init(char* name);
void trace_stack_pop(char* name);

void trace_queue_init(char* name);
void trace_queue_dequeue(char* name);

void trace_hash_init(char* name, int size);

void trace_tree_init(char* name);
void trace_tree_node(char* tree, char* id, char* value);
void trace_tree_edge(char* tree, char* parent, char* child);
void trace_tree_highlight(char* tree, char* id);

/* Binary tree: node identity is the node POINTER (formatted internally as a
   stable id), kept separate from the displayed integer data. A NULL child in
   trace_btree_left/right means "no child" (unlinks that side). */
void trace_btree_init(char* name);
void trace_btree_node(char* tree, void* node, long long data);
void trace_btree_left(char* tree, void* parent, void* child);
void trace_btree_right(char* tree, void* parent, void* child);
void trace_btree_update(char* tree, void* node, long long data);
void trace_btree_delete(char* tree, void* node);
void trace_btree_highlight(char* tree, void* node);
/* Attach a named label (e.g. "x", "y", "T2") to a node so students can see
   which pointer variable references it — useful for rotation pivots and search
   cursors. Passing NULL as target detaches the label. */
void trace_btree_pointer(char* tree, char* name, void* target);

void trace_graph_init(char* name);
void trace_graph_node(char* graph, char* id);
void trace_graph_edge(char* graph, char* from, char* to);
void trace_graph_highlight(char* graph, char* id);

/* ── Recursion / Call Tree ──────────────────────────────────────── */
/* Visualizes a recursion (call) tree: each function INVOCATION becomes a
   rectangular node whose parameter values are shown in separate partitions, and
   a directed edge links each caller to the callee it spawned. The tracer keeps
   an internal call stack, so each invocation's unique identity, its parent (the
   caller), and the currently-active frame are derived automatically — user code
   only marks enter / param / return. Identity is the invocation, not the
   function: fib(2) reached twice yields two distinct nodes. */
void trace_rec_init(char* name);
void trace_rec_enter(char* name, char* func);
void trace_rec_exit(char* name); /* leave current frame with no return value */

void _trace_rec_param_ll(char* name, char* p, long long value);
void _trace_rec_param_char(char* name, char* p, char value);
void _trace_rec_return_ll(char* name, long long value);
void _trace_rec_return_char(char* name, char value);

void trace_line(int line);

#endif
