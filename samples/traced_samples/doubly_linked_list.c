#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

typedef struct Node {
  char id[10];
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

int main() {
  trace_dll_init("list");

  // ---- Create first node ----
  Node* n1 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n1->id, "n1");
  trace_line(__LINE__ - 1);

  n1->value = 5;
  trace_line(__LINE__ - 1);

  n1->prev = NULL;
  n1->next = NULL;
  trace_line(__LINE__ - 2);

  Node* head = n1;
  trace_line(__LINE__ - 1);

  trace_dll_node("list", n1->id, n1->value);

  // ---- Create second node ----
  Node* n2 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n2->id, "n2");
  trace_line(__LINE__ - 1);

  n2->value = 10;
  trace_line(__LINE__ - 1);

  n2->prev = NULL;
  n2->next = NULL;
  trace_line(__LINE__ - 2);

  // Link n1 <-> n2
  n1->next = n2;
  n2->prev = n1;
  trace_line(__LINE__ - 2);

  trace_dll_node("list", n2->id, n2->value);
  trace_dll_link("list", n1->id, n2->id);

  // ---- Create third node ----
  Node* n3 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n3->id, "n3");
  trace_line(__LINE__ - 1);

  n3->value = 15;
  trace_line(__LINE__ - 1);

  n3->prev = NULL;
  n3->next = NULL;
  trace_line(__LINE__ - 2);

  // Link n2 <-> n3
  n2->next = n3;
  n3->prev = n2;
  trace_line(__LINE__ - 2);

  trace_dll_node("list", n3->id, n3->value);
  trace_dll_link("list", n2->id, n3->id);

  // ---- Forward Traversal ----
  Node* temp = head;
  trace_dll_pointer("list", "temp", temp->id);
  trace_line(__LINE__ - 2);

  while (temp != NULL) {
    trace_dll_highlight("list", temp->id);
    trace_dll_pointer("list", "temp", temp->id);

    temp = temp->next;
    trace_line(__LINE__ - 1);
  }

  // ---- Backward Traversal ----
  temp = n3;
  trace_line(__LINE__ - 1);

  while (temp != NULL) {
    trace_dll_highlight("list", temp->id);
    trace_dll_pointer("list", "temp", temp->id);

    temp = temp->prev;
    trace_line(__LINE__ - 1);
  }

  // ---- Proper Free (safe traversal) ----
  Node* curr = head;
  trace_line(__LINE__ - 1);

  while (curr != NULL) {
    Node* nextNode = curr->next;
    trace_line(__LINE__ - 1);

    // Visually remove links
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
    }

    if (curr->next != NULL) {
      curr->next->prev = NULL;
    }

    trace_dll_free("list", curr->id);
    trace_line(__LINE__ - 1);

    free(curr);
    curr = nextNode;
  }

  return 0;
}