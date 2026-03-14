#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

typedef struct Node {
  char id[10];
  int value;
  struct Node* next;
} Node;

int main() {
  // ---- Create first node ----
  Node* n1 = (Node*)malloc(sizeof(Node));

  strcpy(n1->id, "n1");

  n1->value = 5;

  n1->next = NULL;

  Node* head = n1;

  // ---- Create second node ----
  Node* n2 = (Node*)malloc(sizeof(Node));
  strcpy(n2->id, "n2");

  n2->value = 10;

  n2->next = NULL;

  n1->next = n2;

  // ---- Create third node ----
  Node* n3 = (Node*)malloc(sizeof(Node));

  strcpy(n3->id, "n3");

  n3->value = 15;

  n3->next = NULL;

  n2->next = n3;

  // ---- Traversal ----
  Node* temp = head;

  while (temp != NULL) {
    temp = temp->next;
  }

  // ---- Free ----
  free(n1);
  n1 = NULL;

  free(n2);
  n2 = NULL;

  free(n3);
  n3 = NULL;

  return 0;
}
