#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct Node {
  int key;
  int value;
  struct Node* next;
} Node;

Node* table[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  int index = hash(key);

  Node* newNode = (Node*)malloc(sizeof(Node));

  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;

  if (table[index] == NULL) {
    table[index] = newNode;
  } else {
    Node* temp = table[index];
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void removeKey(int key) {
  int index = hash(key);

  Node* temp = table[index];
  Node* prev = NULL;

  while (temp != NULL && temp->key != key) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    return;
  }

  if (prev == NULL) {
    table[index] = temp->next;
  } else {
    prev->next = temp->next;
  }

  free(temp);
}

int main() {
  // Initialize table
  for (int i = 0; i < SIZE; i++) {
    table[i] = NULL;
  }

  // Insert values
  put(10, 100);
  put(15, 150);
  put(20, 200);
  put(7, 70);

  // Remove one key
  removeKey(15);

  return 0;
}