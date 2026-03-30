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

int has(int key) {
    int idx = hash(key);
    Entry* e = table[idx];
    while (e != NULL) {
        if (e->key == key) return 1;
        e = e->next;
    }
    return 0;
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

    int arr[] = {4, 8, 2, 4, 7};
    int n = 5;
    int duplicate = -1;

    for (int i = 0; i < n; i++) {
        if (has(arr[i])) {
            duplicate = arr[i];
            break;
        }
        insert(arr[i], 1);
    }

    if (duplicate != -1) {
        printf("duplicate found: %d\n", duplicate);
    } else {
        printf("no duplicates\n");
    }

    return 0;
}
