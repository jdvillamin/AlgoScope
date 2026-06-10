#include "tracer.h"

#include <stdarg.h>
#include <stdio.h>

/* Every trace event must occupy its own stdout line, but user printf calls
   may leave the cursor mid-line (e.g. printf("%d ", ...) in a traversal).
   Emitting a leading newline before each event guarantees the event starts
   at column 0; the resulting blank lines are skipped by the frontend. */
static void _emit(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  putchar('\n');
  vprintf(fmt, args);
  va_end(args);
}

/* ── Variable ───────────────────────────────────────────────────── */

void _trace_var_init_ll(char* name, long long value) {
  _emit("{\"type\":\"var_init\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_var_init_char(char* name, char value) {
  _emit("{\"type\":\"var_init\",\"name\":\"%s\",\"v\":\"%c\"}\n", name, value);
}

void _trace_var_ll(char* name, long long value) {
  _emit("{\"type\":\"var\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_var_char(char* name, char value) {
  _emit("{\"type\":\"var\",\"name\":\"%s\",\"v\":\"%c\"}\n", name, value);
}

/* ── Array ──────────────────────────────────────────────────────── */

void trace_array_init(char* name, int size) {
  _emit("{\"type\":\"array_init\",\"name\":\"%s\",\"size\":%d}\n", name, size);
}

void trace_array_init_bars(char* name, int size) {
  _emit("{\"type\":\"array_init\",\"name\":\"%s\",\"size\":%d,\"display\":\"bars\"}\n", name, size);
}

void _trace_array_ll(char* name, int index, long long value) {
  _emit("{\"type\":\"array\",\"name\":\"%s\",\"i\":%d,\"v\":%lld}\n", name,
         index, value);
}

void _trace_array_char(char* name, int index, char value) {
  _emit("{\"type\":\"array\",\"name\":\"%s\",\"i\":%d,\"v\":\"%c\"}\n", name,
         index, value);
}

void trace_array_highlight(char* name, int index) {
  _emit("{\"type\":\"array_highlight\",\"name\":\"%s\",\"i\":%d}\n", name,
         index);
}

void trace_array_cell(char* array_name, char* var_name, int index) {
  _emit("{\"type\":\"array_cell\",\"name\":\"%s\",\"var\":\"%s\",\"i\":%d}\n",
         array_name, var_name, index);
}

/* ── 2D Array ───────────────────────────────────────────────────── */

void trace_array2d_init(char* name, int rows, int cols) {
  _emit(
      "{\"type\":\"array2d_init\",\"name\":\"%s\",\"rows\":%d,\"cols\":%d}\n",
      name, rows, cols);
}

void _trace_array2d_ll(char* name, int r, int c, long long value) {
  _emit("{\"type\":\"array2d\",\"name\":\"%s\",\"r\":%d,\"c\":%d,\"v\":%lld}\n",
         name, r, c, value);
}

void _trace_array2d_char(char* name, int r, int c, char value) {
  _emit("{\"type\":\"array2d\",\"name\":\"%s\",\"r\":%d,\"c\":%d,\"v\":\"%c\"}\n",
         name, r, c, value);
}

void trace_array2d_highlight(char* name, int r, int c) {
  _emit(
      "{\"type\":\"array2d_highlight\",\"name\":\"%s\",\"r\":%d,\"c\":%d}\n",
      name, r, c);
}

void trace_array2d_cell(char* array_name, char* var_name, int r, int c) {
  _emit("{\"type\":\"array2d_cell\",\"name\":\"%s\",\"var\":\"%s\",\"r\":%d,\"c\":%d}\n",
         array_name, var_name, r, c);
}

/* ── Singly Linked List ─────────────────────────────────────────── */

void trace_ll_init(char* name) {
  _emit("{\"type\":\"ll_init\",\"name\":\"%s\"}\n", name);
}

void _trace_ll_node_ll(char* list, char* id, long long value) {
  _emit("{\"type\":\"ll_node\",\"list\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         list, id, value);
}

void trace_ll_link(char* list, char* from, char* to) {
  _emit(
      "{\"type\":\"ll_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%s\"}\n",
      list, from, to);
}

void trace_ll_free(char* list, char* id) {
  _emit("{\"type\":\"ll_free\",\"list\":\"%s\",\"id\":\"%s\"}\n", list, id);
}

void trace_ll_pointer(char* list, char* name, char* target) {
  _emit(
      "{\"type\":\"ll_pointer\",\"list\":\"%s\",\"name\":\"%s\",\"target\":\"%"
      "s\"}\n",
      list, name, target);
}

void trace_ll_highlight(char* list, char* id) {
  _emit("{\"type\":\"ll_highlight\",\"list\":\"%s\",\"id\":\"%s\"}\n", list,
         id);
}

/* ── Doubly Linked List ─────────────────────────────────────────── */

void trace_dll_init(char* name) {
  _emit("{\"type\":\"dll_init\",\"name\":\"%s\"}\n", name);
}

void _trace_dll_node_ll(char* list, char* id, long long value) {
  _emit("{\"type\":\"dll_node\",\"list\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         list, id, value);
}

void trace_dll_next_link(char* list, char* from, char* to) {
  _emit(
      "{\"type\":\"dll_next_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_prev_link(char* list, char* from, char* to) {
  _emit(
      "{\"type\":\"dll_prev_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_next_unlink(char* list, char* from, char* to) {
  _emit(
      "{\"type\":\"dll_next_unlink\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_prev_unlink(char* list, char* from, char* to) {
  _emit(
      "{\"type\":\"dll_prev_unlink\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_highlight(char* list, char* id) {
  _emit("{\"type\":\"dll_highlight\",\"list\":\"%s\",\"id\":\"%s\"}\n", list,
         id);
}

void trace_dll_pointer(char* list, char* name, char* target) {
  _emit(
      "{\"type\":\"dll_pointer\",\"list\":\"%s\",\"name\":\"%s\",\"target\":\"%"
      "s\"}\n",
      list, name, target);
}

void trace_dll_free(char* list, char* id) {
  _emit("{\"type\":\"dll_free\",\"list\":\"%s\",\"id\":\"%s\"}\n", list, id);
}

/* ── Stack ──────────────────────────────────────────────────────── */

void trace_stack_init(char* name) {
  _emit("{\"type\":\"stack_init\",\"name\":\"%s\"}\n", name);
}

void _trace_stack_push_ll(char* name, long long value) {
  _emit("{\"type\":\"stack_push\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void trace_stack_pop(char* name) {
  _emit("{\"type\":\"stack_pop\",\"name\":\"%s\"}\n", name);
}

void _trace_stack_top_ll(char* name, long long value) {
  _emit("{\"type\":\"stack_top\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

/* ── Queue ──────────────────────────────────────────────────────── */

void trace_queue_init(char* name) {
  _emit("{\"type\":\"queue_init\",\"name\":\"%s\"}\n", name);
}

void _trace_queue_enqueue_ll(char* name, long long value) {
  _emit("{\"type\":\"queue_enqueue\",\"name\":\"%s\",\"v\":%lld}\n", name,
         value);
}

void trace_queue_dequeue(char* name) {
  _emit("{\"type\":\"queue_dequeue\",\"name\":\"%s\"}\n", name);
}

void _trace_queue_front_ll(char* name, long long value) {
  _emit("{\"type\":\"queue_front\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_queue_rear_ll(char* name, long long value) {
  _emit("{\"type\":\"queue_rear\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

/* ── Hash Map ───────────────────────────────────────────────────── */

void trace_hash_init(char* name, int size) {
  _emit("{\"type\":\"hash_init\",\"name\":\"%s\",\"size\":%d}\n", name, size);
}

void _trace_hash_put_ll(char* name, long long key, long long value, int index) {
  _emit(
      "{\"type\":\"hash_put\",\"name\":\"%s\",\"key\":%lld,\"value\":%lld,"
      "\"index\":%d}\n",
      name, key, value, index);
}

void _trace_hash_remove_ll(char* name, long long key, int index) {
  _emit("{\"type\":\"hash_remove\",\"name\":\"%s\",\"key\":%lld,\"index\":%d}\n",
         name, key, index);
}

/* ── N-ary Tree ─────────────────────────────────────────────────── */

void trace_tree_init(char* name) {
  _emit("{\"type\":\"tree_init\",\"name\":\"%s\"}\n", name);
}

void trace_tree_node(char* tree, char* id, char* value) {
  _emit(
      "{\"type\":\"tree_node\",\"tree\":\"%s\",\"id\":\"%s\",\"v\":\"%s\"}\n",
      tree, id, value);
}

void trace_tree_edge(char* tree, char* parent, char* child) {
  _emit(
      "{\"type\":\"tree_edge\",\"tree\":\"%s\",\"parent\":\"%s\",\"child\":\"%"
      "s\"}\n",
      tree, parent, child);
}

void trace_tree_highlight(char* tree, char* id) {
  _emit("{\"type\":\"tree_highlight\",\"tree\":\"%s\",\"id\":\"%s\"}\n", tree,
         id);
}

/* ── Binary Tree ────────────────────────────────────────────────── */
/* Identity is the node POINTER, formatted as a stable hex id and kept separate
   from the displayed integer data. This lets a node be relabeled (data changes,
   identity/position stay) and deleted without the user's struct needing an id
   field. A NULL child unlinks that side. */

void trace_btree_init(char* name) {
  _emit("{\"type\":\"btree_init\",\"name\":\"%s\"}\n", name);
}

void trace_btree_node(char* tree, void* node, long long data) {
  if (node == NULL) return;
  char id[32];
  snprintf(id, sizeof(id), "%p", node);
  _emit("{\"type\":\"btree_node\",\"tree\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         tree, id, data);
}

static void _btree_edge(char* tree, void* parent, void* child, char side) {
  if (parent == NULL) return;
  char pid[32], cid[32];
  snprintf(pid, sizeof(pid), "%p", parent);
  if (child == NULL)
    cid[0] = '\0';
  else
    snprintf(cid, sizeof(cid), "%p", child);
  _emit("{\"type\":\"btree_edge\",\"tree\":\"%s\",\"parent\":\"%s\",\"child\":"
         "\"%s\",\"side\":\"%c\"}\n",
         tree, pid, cid, side);
}

void trace_btree_left(char* tree, void* parent, void* child) {
  _btree_edge(tree, parent, child, 'L');
}

void trace_btree_right(char* tree, void* parent, void* child) {
  _btree_edge(tree, parent, child, 'R');
}

void trace_btree_update(char* tree, void* node, long long data) {
  if (node == NULL) return;
  char id[32];
  snprintf(id, sizeof(id), "%p", node);
  _emit("{\"type\":\"btree_update\",\"tree\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         tree, id, data);
}

void trace_btree_delete(char* tree, void* node) {
  if (node == NULL) return;
  char id[32];
  snprintf(id, sizeof(id), "%p", node);
  _emit("{\"type\":\"btree_delete\",\"tree\":\"%s\",\"id\":\"%s\"}\n", tree, id);
}

void trace_btree_highlight(char* tree, void* node) {
  if (node == NULL) return;
  char id[32];
  snprintf(id, sizeof(id), "%p", node);
  _emit("{\"type\":\"btree_highlight\",\"tree\":\"%s\",\"id\":\"%s\"}\n", tree,
         id);
}

void trace_btree_color(char* tree, void* node, char* color) {
  if (node == NULL || color == NULL) return;
  char id[32];
  snprintf(id, sizeof(id), "%p", node);
  _emit("{\"type\":\"btree_color\",\"tree\":\"%s\",\"id\":\"%s\",\"color\":\"%s\"}\n",
         tree, id, color);
}

void trace_btree_pointer(char* tree, char* name, void* target) {
  char tid[32];
  if (target == NULL)
    tid[0] = '\0';
  else
    snprintf(tid, sizeof(tid), "%p", target);
  _emit(
      "{\"type\":\"btree_pointer\",\"tree\":\"%s\",\"name\":\"%s\",\"target\":\"%"
      "s\"}\n",
      tree, name, tid);
}

/* ── Graph ──────────────────────────────────────────────────────── */

void trace_graph_init(char* name) {
  _emit("{\"type\":\"graph_init\",\"name\":\"%s\"}\n", name);
}

void trace_graph_node(char* graph, char* id) {
  _emit("{\"type\":\"graph_node\",\"graph\":\"%s\",\"id\":\"%s\"}\n", graph,
         id);
}

void trace_graph_edge(char* graph, char* from, char* to) {
  _emit(
      "{\"type\":\"graph_edge\",\"graph\":\"%s\",\"from\":\"%s\",\"to\":\"%s\"}"
      "\n",
      graph, from, to);
}

void trace_graph_highlight(char* graph, char* id) {
  _emit("{\"type\":\"graph_highlight\",\"graph\":\"%s\",\"id\":\"%s\"}\n",
         graph, id);
}

/* ── Recursion / Call Tree ──────────────────────────────────────── */
/* An internal call stack lets the tracer assign every invocation a unique id and
   derive its parent (the caller on the stack below it) and the currently-active
   frame, so user code only marks enter/param/return. enter pushes a fresh id;
   param/return act on the top frame; return/exit pops. Because identity is the
   pushed id (not the function), the same function reached twice produces two
   separate nodes — exactly what a recursion tree shows. */

#define _TRACE_REC_MAX 8192
static long long _trace_rec_stack[_TRACE_REC_MAX];
static int _trace_rec_sp = 0;
static long long _trace_rec_counter = 0;

static long long _trace_rec_top(void) {
  return _trace_rec_sp > 0 ? _trace_rec_stack[_trace_rec_sp - 1] : -1;
}

void trace_rec_init(char* name) {
  _trace_rec_sp = 0;
  _trace_rec_counter = 0;
  _emit("{\"type\":\"rec_init\",\"name\":\"%s\"}\n", name);
}

void trace_rec_enter(char* name, char* func) {
  long long id = ++_trace_rec_counter;
  long long parent = _trace_rec_top();
  if (_trace_rec_sp < _TRACE_REC_MAX) _trace_rec_stack[_trace_rec_sp++] = id;
  _emit("{\"type\":\"rec_enter\",\"name\":\"%s\",\"id\":%lld,\"parent\":%lld,"
         "\"func\":\"%s\"}\n",
         name, id, parent, func);
}

void _trace_rec_param_ll(char* name, char* p, long long value) {
  _emit("{\"type\":\"rec_param\",\"name\":\"%s\",\"id\":%lld,\"p\":\"%s\","
         "\"v\":%lld}\n",
         name, _trace_rec_top(), p, value);
}

void _trace_rec_param_char(char* name, char* p, char value) {
  _emit("{\"type\":\"rec_param\",\"name\":\"%s\",\"id\":%lld,\"p\":\"%s\","
         "\"v\":\"%c\"}\n",
         name, _trace_rec_top(), p, value);
}

void _trace_rec_return_ll(char* name, long long value) {
  long long id = _trace_rec_top();
  if (_trace_rec_sp > 0) _trace_rec_sp--;
  _emit("{\"type\":\"rec_return\",\"name\":\"%s\",\"id\":%lld,\"v\":%lld}\n",
         name, id, value);
}

void _trace_rec_return_char(char* name, char value) {
  long long id = _trace_rec_top();
  if (_trace_rec_sp > 0) _trace_rec_sp--;
  _emit("{\"type\":\"rec_return\",\"name\":\"%s\",\"id\":%lld,\"v\":\"%c\"}\n",
         name, id, value);
}

void trace_rec_exit(char* name) {
  long long id = _trace_rec_top();
  if (_trace_rec_sp > 0) _trace_rec_sp--;
  _emit("{\"type\":\"rec_return\",\"name\":\"%s\",\"id\":%lld}\n", name, id);
}

/* ── Others ─────────────────────────────────────────────────────── */

void trace_line(int line) { _emit("{\"type\":\"line\",\"n\":%d}\n", line); }
