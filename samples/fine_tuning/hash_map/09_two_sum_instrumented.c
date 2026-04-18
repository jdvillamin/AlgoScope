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

int has(int key) {
    trace_line(28);
    int idx = hash(key);
    trace_line(29);
    Entry* e = table[idx];
    trace_line(30);
    while (e != NULL) {
        trace_line(30);
        trace_line(31);
        if (e->key == key) return 1;
        trace_line(32);
        e = e->next;
    }
    trace_line(34);
    return 0;
}

int main() {
    trace_line(37);
    for (int i = 0; i < SIZE; i++) table[i] = NULL;
    trace_hash_init("H", SIZE);

    int arr[] = {2, 7, 11, 15};
    trace_line(40);
    int n = 4;
    trace_var_init("n", n);
    trace_line(41);
    int target = 9;
    trace_var_init("target", target);

    trace_line(43);
    for (int i = 0; i < n; i++) {
        trace_line(43);
        trace_var_init("i", i);
        trace_line(44);
        int complement = target - arr[i];
        trace_var_init("complement", complement);
        trace_line(45);
        if (has(complement)) {
            trace_line(46);
            printf("found pair: %d + %d = %d\n", complement, arr[i], target);
            break;
        }
        trace_line(49);
        insert(arr[i], i);
    }

    trace_line(52);
    return 0;
}
