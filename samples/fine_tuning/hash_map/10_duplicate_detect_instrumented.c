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

int has(int key) {
    trace_line(20);
    int idx = hash(key);
    trace_line(21);
    Entry* e = table[idx];
    trace_line(22);
    while (e != NULL) {
        trace_line(22);
        trace_line(23);
        if (e->key == key) return 1;
        trace_line(24);
        e = e->next;
    }
    trace_line(26);
    return 0;
}

void insert(int key, int value) {
    trace_line(29);
    int idx = hash(key);
    trace_line(30);
    Entry* e = (Entry*)malloc(sizeof(Entry));
    trace_line(31);
    e->key = key;
    trace_line(32);
    e->value = value;
    trace_line(33);
    e->next = table[idx];
    trace_line(34);
    table[idx] = e;
    trace_hash_put("H", key, value, idx);
}

int main() {
    trace_line(37);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    int arr[] = {4, 8, 2, 4, 7};
    trace_line(40);
    int n = 5;
    trace_var_init("n", n);
    trace_line(41);
    int duplicate = -1;
    trace_var_init("duplicate", duplicate);

    trace_line(43);
    for (int i = 0; i < n; i++) {
        trace_line(43);
        trace_line(44);
        if (has(arr[i])) {
            trace_line(45);
            duplicate = arr[i];
            trace_var("duplicate", duplicate);
            break;
        }
        trace_line(48);
        insert(arr[i], 1);
    }

    trace_line(51);
    if (duplicate != -1) {
        trace_line(52);
        printf("duplicate found: %d\n", duplicate);
    } else {
        trace_line(54);
        printf("no duplicates\n");
    }

    trace_line(57);
    return 0;
}
