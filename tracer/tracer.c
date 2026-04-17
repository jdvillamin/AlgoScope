#include "tracer.h"

#include <stdio.h>

/* ── Variable ───────────────────────────────────────────────────── */

void _trace_var_init_ll(char* name, long long value) {
  printf("{\"type\":\"var_init\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_var_init_char(char* name, char value) {
  printf("{\"type\":\"var_init\",\"name\":\"%s\",\"v\":\"%c\"}\n", name, value);
}

void _trace_var_ll(char* name, long long value) {
  printf("{\"type\":\"var\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_var_char(char* name, char value) {
  printf("{\"type\":\"var\",\"name\":\"%s\",\"v\":\"%c\"}\n", name, value);
}

/* ── Array ──────────────────────────────────────────────────────── */

void trace_array_init(char* name, int size) {
  printf("{\"type\":\"array_init\",\"name\":\"%s\",\"size\":%d}\n", name, size);
}

void _trace_array_ll(char* name, int index, long long value) {
  printf("{\"type\":\"array\",\"name\":\"%s\",\"i\":%d,\"v\":%lld}\n", name,
         index, value);
}

void _trace_array_char(char* name, int index, char value) {
  printf("{\"type\":\"array\",\"name\":\"%s\",\"i\":%d,\"v\":\"%c\"}\n", name,
         index, value);
}

void trace_array_highlight(char* name, int index) {
  printf("{\"type\":\"array_highlight\",\"name\":\"%s\",\"i\":%d}\n", name,
         index);
}

/* ── 2D Array ───────────────────────────────────────────────────── */

void trace_array2d_init(char* name, int rows, int cols) {
  printf(
      "{\"type\":\"array2d_init\",\"name\":\"%s\",\"rows\":%d,\"cols\":%d}\n",
      name, rows, cols);
}

void _trace_array2d_ll(char* name, int r, int c, long long value) {
  printf("{\"type\":\"array2d\",\"name\":\"%s\",\"r\":%d,\"c\":%d,\"v\":%lld}\n",
         name, r, c, value);
}

void _trace_array2d_char(char* name, int r, int c, char value) {
  printf("{\"type\":\"array2d\",\"name\":\"%s\",\"r\":%d,\"c\":%d,\"v\":\"%c\"}\n",
         name, r, c, value);
}

void trace_array2d_highlight(char* name, int r, int c) {
  printf(
      "{\"type\":\"array2d_highlight\",\"name\":\"%s\",\"r\":%d,\"c\":%d}\n",
      name, r, c);
}

/* ── Singly Linked List ─────────────────────────────────────────── */

void trace_ll_init(char* name) {
  printf("{\"type\":\"ll_init\",\"name\":\"%s\"}\n", name);
}

void _trace_ll_node_ll(char* list, char* id, long long value) {
  printf("{\"type\":\"ll_node\",\"list\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         list, id, value);
}

void trace_ll_link(char* list, char* from, char* to) {
  printf(
      "{\"type\":\"ll_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%s\"}\n",
      list, from, to);
}

void trace_ll_free(char* list, char* id) {
  printf("{\"type\":\"ll_free\",\"list\":\"%s\",\"id\":\"%s\"}\n", list, id);
}

void trace_ll_pointer(char* list, char* name, char* target) {
  printf(
      "{\"type\":\"ll_pointer\",\"list\":\"%s\",\"name\":\"%s\",\"target\":\"%"
      "s\"}\n",
      list, name, target);
}

void trace_ll_highlight(char* list, char* id) {
  printf("{\"type\":\"ll_highlight\",\"list\":\"%s\",\"id\":\"%s\"}\n", list,
         id);
}

/* ── Doubly Linked List ─────────────────────────────────────────── */

void trace_dll_init(char* name) {
  printf("{\"type\":\"dll_init\",\"name\":\"%s\"}\n", name);
}

void _trace_dll_node_ll(char* list, char* id, long long value) {
  printf("{\"type\":\"dll_node\",\"list\":\"%s\",\"id\":\"%s\",\"v\":%lld}\n",
         list, id, value);
}

void trace_dll_next_link(char* list, char* from, char* to) {
  printf(
      "{\"type\":\"dll_next_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_prev_link(char* list, char* from, char* to) {
  printf(
      "{\"type\":\"dll_prev_link\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_next_unlink(char* list, char* from, char* to) {
  printf(
      "{\"type\":\"dll_next_unlink\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_prev_unlink(char* list, char* from, char* to) {
  printf(
      "{\"type\":\"dll_prev_unlink\",\"list\":\"%s\",\"from\":\"%s\",\"to\":\"%"
      "s\"}\n",
      list, from, to);
}

void trace_dll_highlight(char* list, char* id) {
  printf("{\"type\":\"dll_highlight\",\"list\":\"%s\",\"id\":\"%s\"}\n", list,
         id);
}

void trace_dll_pointer(char* list, char* name, char* target) {
  printf(
      "{\"type\":\"dll_pointer\",\"list\":\"%s\",\"name\":\"%s\",\"target\":\"%"
      "s\"}\n",
      list, name, target);
}

void trace_dll_free(char* list, char* id) {
  printf("{\"type\":\"dll_free\",\"list\":\"%s\",\"id\":\"%s\"}\n", list, id);
}

/* ── Stack ──────────────────────────────────────────────────────── */

void trace_stack_init(char* name) {
  printf("{\"type\":\"stack_init\",\"name\":\"%s\"}\n", name);
}

void _trace_stack_push_ll(char* name, long long value) {
  printf("{\"type\":\"stack_push\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void trace_stack_pop(char* name) {
  printf("{\"type\":\"stack_pop\",\"name\":\"%s\"}\n", name);
}

void _trace_stack_top_ll(char* name, long long value) {
  printf("{\"type\":\"stack_top\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

/* ── Queue ──────────────────────────────────────────────────────── */

void trace_queue_init(char* name) {
  printf("{\"type\":\"queue_init\",\"name\":\"%s\"}\n", name);
}

void _trace_queue_enqueue_ll(char* name, long long value) {
  printf("{\"type\":\"queue_enqueue\",\"name\":\"%s\",\"v\":%lld}\n", name,
         value);
}

void trace_queue_dequeue(char* name) {
  printf("{\"type\":\"queue_dequeue\",\"name\":\"%s\"}\n", name);
}

void _trace_queue_front_ll(char* name, long long value) {
  printf("{\"type\":\"queue_front\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

void _trace_queue_rear_ll(char* name, long long value) {
  printf("{\"type\":\"queue_rear\",\"name\":\"%s\",\"v\":%lld}\n", name, value);
}

/* ── Hash Map ───────────────────────────────────────────────────── */

void trace_hash_init(char* name, int size) {
  printf("{\"type\":\"hash_init\",\"name\":\"%s\",\"size\":%d}\n", name, size);
}

void _trace_hash_put_ll(char* name, long long key, long long value, int index) {
  printf(
      "{\"type\":\"hash_put\",\"name\":\"%s\",\"key\":%lld,\"value\":%lld,"
      "\"index\":%d}\n",
      name, key, value, index);
}

void _trace_hash_remove_ll(char* name, long long key, int index) {
  printf("{\"type\":\"hash_remove\",\"name\":\"%s\",\"key\":%lld,\"index\":%d}\n",
         name, key, index);
}

/* ── N-ary Tree ─────────────────────────────────────────────────── */

void trace_tree_init(char* name) {
  printf("{\"type\":\"tree_init\",\"name\":\"%s\"}\n", name);
}

void trace_tree_node(char* tree, char* id, char* value) {
  printf(
      "{\"type\":\"tree_node\",\"tree\":\"%s\",\"id\":\"%s\",\"v\":\"%s\"}\n",
      tree, id, value);
}

void trace_tree_edge(char* tree, char* parent, char* child) {
  printf(
      "{\"type\":\"tree_edge\",\"tree\":\"%s\",\"parent\":\"%s\",\"child\":\"%"
      "s\"}\n",
      tree, parent, child);
}

void trace_tree_highlight(char* tree, char* id) {
  printf("{\"type\":\"tree_highlight\",\"tree\":\"%s\",\"id\":\"%s\"}\n", tree,
         id);
}

/* ── Graph ──────────────────────────────────────────────────────── */

void trace_graph_init(char* name) {
  printf("{\"type\":\"graph_init\",\"name\":\"%s\"}\n", name);
}

void trace_graph_node(char* graph, char* id) {
  printf("{\"type\":\"graph_node\",\"graph\":\"%s\",\"id\":\"%s\"}\n", graph,
         id);
}

void trace_graph_edge(char* graph, char* from, char* to) {
  printf(
      "{\"type\":\"graph_edge\",\"graph\":\"%s\",\"from\":\"%s\",\"to\":\"%s\"}"
      "\n",
      graph, from, to);
}

void trace_graph_highlight(char* graph, char* id) {
  printf("{\"type\":\"graph_highlight\",\"graph\":\"%s\",\"id\":\"%s\"}\n",
         graph, id);
}

/* ── Others ─────────────────────────────────────────────────────── */

void trace_line(int line) { printf("{\"type\":\"line\",\"n\":%d}\n", line); }
