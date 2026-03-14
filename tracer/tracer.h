#ifndef TRACER_H
#define TRACER_H

void trace_array_init(char* name, int size);
void trace_array(char* name, int index, int value);

void trace_var_init(char* name, int value);
void trace_var(char* name, int value);

void trace_array2d_init(char* name, int rows, int cols);
void trace_array2d(char* name, int r, int c, int value);

void trace_ll_init(char* name);
void trace_ll_node(char* list, char* id, int value);
void trace_ll_link(char* list, char* from, char* to);
void trace_ll_free(char* list, char* id);
void trace_ll_pointer(char* list, char* name, char* target);
void trace_ll_highlight(char* list, char* id);

void trace_dll_init(char* name);
void trace_dll_node(char* list, char* id, int value);
void trace_dll_next_link(char* list, char* from, char* to);
void trace_dll_prev_link(char* list, char* from, char* to);
void trace_dll_next_unlink(char* list, char* from, char* to);
void trace_dll_prev_unlink(char* list, char* from, char* to);
void trace_dll_highlight(char* list, char* id);
void trace_dll_pointer(char* list, char* name, char* target);
void trace_dll_free(char* list, char* id);

void trace_stack_init(char* name);
void trace_stack_push(char* name, int value);
void trace_stack_pop(char* name);
void trace_stack_top(char* name, int value);

void trace_queue_init(char* name);
void trace_queue_enqueue(char* name, int value);
void trace_queue_dequeue(char* name);
void trace_queue_front(char* name, int value);
void trace_queue_rear(char* name, int value);

void trace_hash_init(char* name, int size);
void trace_hash_put(char* name, int key, int value, int index);
void trace_hash_remove(char* name, int key, int index);

void trace_tree_init(char* name);
void trace_tree_node(char* tree, char* id, char* value);
void trace_tree_edge(char* tree, char* parent, char* child);
void trace_tree_highlight(char* tree, char* id);

void trace_graph_init(char* name);
void trace_graph_node(char* graph, char* id);
void trace_graph_edge(char* graph, char* from, char* to);
void trace_graph_highlight(char* graph, char* id);

void trace_line(int line);

#endif