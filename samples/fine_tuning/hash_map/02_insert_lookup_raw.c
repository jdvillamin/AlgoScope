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

void insert(int key, int value) {
    int idx = hash(key);
    Entry* e = (Entry*)malloc(sizeof(Entry));
    e->key = key;
    e->value = value;
    e->next = table[idx];
    table[idx] = e;
}

int lookup(int key) {
    int idx = hash(key);
    Entry* e = table[idx];
    while (e != NULL) {
        if (e->key == key) return e->value;
        e = e->next;
    }
    return -1;
}

int main() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    insert(2, 10);
    insert(5, 15);
    insert(9, 20);
    insert(14, 8);

    printf("lookup(5): %d\n", lookup(5));
    printf("lookup(14): %d\n", lookup(14));

    return 0;
}
