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

int lookup(int key) {
    trace_line(28);
    int idx = hash(key);
    trace_line(29);
    Entry* e = table[idx];
    trace_line(30);
    while (e != NULL) {
        trace_line(30);
        trace_line(31);
        if (e->key == key) return e->value;
        trace_line(32);
        e = e->next;
    }
    trace_line(34);
    return -1;
}

int main() {
    trace_line(38);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    trace_line(40);
    insert(2, 10);
    trace_line(41);
    insert(5, 15);
    trace_line(42);
    insert(9, 20);
    trace_line(43);
    insert(14, 8);

    trace_line(45);
    printf("lookup(5): %d\n", lookup(5));
    trace_line(46);
    printf("lookup(14): %d\n", lookup(14));

    trace_line(48);
    return 0;
}
