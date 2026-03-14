#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char id[10];
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

int main() {
  // ---- Create first node ----
  Node* n1 = (Node*)malloc(sizeof(Node));

  strcpy(n1->id, "n1");

  n1->value = 5;

  n1->prev = NULL;
  n1->next = NULL;

  Node* head = n1;

  // ---- Create second node ----
  Node* n2 = (Node*)malloc(sizeof(Node));

  strcpy(n2->id, "n2");

  n2->value = 10;

  n2->prev = NULL;
  n2->next = NULL;

  // Link n1 <-> n2
  n1->next = n2;
  n2->prev = n1;

  // ---- Create third node ----
  Node* n3 = (Node*)malloc(sizeof(Node));

  strcpy(n3->id, "n3");

  n3->value = 15;

  n3->prev = NULL;
  n3->next = NULL;

  // Link n2 <-> n3
  n2->next = n3;
  n3->prev = n2;

  // ---- Forward Traversal ----
  Node* temp = head;

  while (temp != NULL) {
    temp = temp->next;
  }

  // ---- Backward Traversal ----
  temp = n3;

  while (temp != NULL) {
    temp = temp->prev;
  }

  // ---- Proper Free (safe traversal) ----
  Node* curr = head;

  while (curr != NULL) {
    Node* nextNode = curr->next;

    // Visually remove links
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
    }

    if (curr->next != NULL) {
      curr->next->prev = NULL;
    }

    free(curr);
    curr = nextNode;
  }

  return 0;
}
