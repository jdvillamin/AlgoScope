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

    insert(1, 5);
    insert(6, 10);
    insert(13, 15);

    for (int i = 0; i < SIZE; i++) {
        Entry* e = table[i];
        while (e != NULL) {
            Entry* temp = e;
            e = e->next;
            free(temp);
        }
        table[i] = NULL;
    }

    return 0;
}
