#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

#define SIZE 7

typedef struct Entry {
    int key;
    int value;
    struct Entry* next;
} Entry;

Entry* table[SIZE];

int hash(int key) {
    return ((key % SIZE) + SIZE) % SIZE;
}

void insert(int key, int value) {
    trace_line(20);
    int idx = hash(key);
    trace_line(21);
    Entry* e = table[idx];
    trace_line(22);
    while (e != NULL) {
        trace_line(22);
        trace_line(23);
        if (e->key == key) {
            trace_line(24);
            e->value = value;
            trace_hash_remove("H", key, idx);
            trace_hash_put("H", key, value, idx);
            return;
        }
        trace_line(27);
        e = e->next;
    }
    trace_line(29);
    e = (Entry*)malloc(sizeof(Entry));
    trace_line(30);
    e->key = key;
    trace_line(31);
    e->value = value;
    trace_line(32);
    e->next = table[idx];
    trace_line(33);
    table[idx] = e;
    trace_hash_put("H", key, value, idx);
}

int main() {
    trace_line(36);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    trace_line(38);
    insert(5, 10);
    trace_line(39);
    insert(12, 20);
    trace_line(40);
    insert(5, 15);

    trace_line(42);
    return 0;
}
