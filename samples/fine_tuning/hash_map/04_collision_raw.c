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

int main() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    /* Keys 1, 8, 15 all hash to index 1 */
    insert(1, 10);
    insert(8, 20);
    insert(15, 5);

    /* Keys 3, 10 hash to index 3 */
    insert(3, 12);
    insert(10, 18);

    return 0;
}
