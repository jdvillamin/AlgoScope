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

    insert(2, 5);
    insert(9, 11);
    insert(4, 17);
    insert(13, 3);
    insert(6, 8);

    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        Entry* e = table[i];
        while (e != NULL) {
            count++;
            e = e->next;
        }
    }

    printf("total entries: %d\n", count);

    return 0;
}
