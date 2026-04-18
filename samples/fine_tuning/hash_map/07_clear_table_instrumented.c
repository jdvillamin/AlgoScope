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
    Entry* e = (Entry*)malloc(sizeof(Entry));
    trace_line(22);
    e->key = key;
    trace_line(23);
    e->value = value;
    trace_line(24);
    e->next = table[idx];
    trace_line(25);
    table[idx] = e;
    trace_hash_put("H", key, value, idx);
}

int main() {
    trace_line(28);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    trace_line(30);
    insert(1, 5);
    trace_line(31);
    insert(6, 10);
    trace_line(32);
    insert(13, 15);

    trace_line(34);
    for (int i = 0; i < SIZE; i++) {
        trace_line(34);
        trace_var_init("i", i);
        trace_line(35);
        Entry* e = table[i];
        trace_line(36);
        while (e != NULL) {
            trace_line(36);
            trace_line(37);
            Entry* temp = e;
            trace_line(38);
            e = e->next;
            trace_hash_remove("H", temp->key, i);
            trace_line(39);
            free(temp);
        }
        trace_line(41);
        table[i] = NULL;
    }

    trace_line(44);
    return 0;
}
