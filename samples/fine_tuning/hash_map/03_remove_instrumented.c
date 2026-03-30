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

void removeKey(int key) {
    trace_line(28);
    int idx = hash(key);
    trace_line(29);
    Entry* e = table[idx];
    trace_line(30);
    Entry* prev = NULL;
    trace_line(31);
    while (e != NULL) {
        trace_line(31);
        trace_line(32);
        if (e->key == key) {
            trace_line(33);
            if (prev == NULL) {
                trace_line(34);
                table[idx] = e->next;
            } else {
                trace_line(36);
                prev->next = e->next;
            }
            trace_hash_remove("H", key, idx);
            trace_line(38);
            free(e);
            return;
        }
        trace_line(41);
        prev = e;
        trace_line(42);
        e = e->next;
    }
}

int main() {
    trace_line(46);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    trace_line(48);
    insert(4, 12);
    trace_line(49);
    insert(11, 7);
    trace_line(50);
    insert(18, 3);

    trace_line(52);
    removeKey(11);

    trace_line(54);
    return 0;
}
