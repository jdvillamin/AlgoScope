#include <stdio.h>
#include <stdlib.h>

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

Entry* find(int key) {
    int idx = hash(key);
    Entry* e = table[idx];
    while (e != NULL) {
        if (e->key == key) return e;
        e = e->next;
    }
    return NULL;
}

void insert(int key, int value) {
    int idx = hash(key);
    Entry* e = (Entry*)malloc(sizeof(Entry));
    e->key = key;
    e->value = value;
    e->next = table[idx];
    table[idx] = e;
}

int main() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    int arr[] = {3, 5, 3, 2, 5, 3, 2};
    int n = 7;

    for (int i = 0; i < n; i++) {
        Entry* e = find(arr[i]);
        if (e != NULL) {
            e->value++;
        } else {
            insert(arr[i], 1);
        }
    }

    return 0;
}
