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

void removeKey(int key) {
    int idx = hash(key);
    Entry* e = table[idx];
    Entry* prev = NULL;
    while (e != NULL) {
        if (e->key == key) {
            if (prev == NULL) {
                table[idx] = e->next;
            } else {
                prev->next = e->next;
            }
            free(e);
            return;
        }
        prev = e;
        e = e->next;
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    insert(4, 12);
    insert(11, 7);
    insert(18, 3);

    removeKey(11);

    return 0;
}
