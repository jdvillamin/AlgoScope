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

int has(int key) {
    int idx = hash(key);
    Entry* e = table[idx];
    while (e != NULL) {
        if (e->key == key) return 1;
        e = e->next;
    }
    return 0;
}

int main() {
    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    int arr[] = {2, 7, 11, 15};
    int n = 4;
    int target = 9;

    for (int i = 0; i < n; i++) {
        int complement = target - arr[i];
        if (has(complement)) {
            printf("found pair: %d + %d = %d\n", complement, arr[i], target);
            break;
        }
        insert(arr[i], i);
    }

    return 0;
}
