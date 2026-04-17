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
  trace_ll_init("head");

  // ---- Create first node ----
  Node* n1 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n1->id, "n1");
  trace_line(__LINE__ - 1);

  n1->value = 5;
  trace_line(__LINE__ - 1);

  n1->next = NULL;
  trace_line(__LINE__ - 1);

  Node* head = n1;
  trace_line(__LINE__ - 1);

  trace_ll_node("head", n1->id, n1->value);
  trace_ll_pointer("head", "head", n1->id);

  // ---- Create second node ----
  Node* n2 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n2->id, "n2");
  trace_line(__LINE__ - 1);

  n2->value = 10;
  trace_line(__LINE__ - 1);

  n2->next = NULL;
  trace_line(__LINE__ - 1);

  n1->next = n2;
  trace_line(__LINE__ - 1);

  trace_ll_node("head", n2->id, n2->value);
  trace_ll_link("head", n1->id, n2->id);

  // ---- Create third node ----
  Node* n3 = (Node*)malloc(sizeof(Node));
  trace_line(__LINE__ - 1);

  strcpy(n3->id, "n3");
  trace_line(__LINE__ - 1);

  n3->value = 15;
  trace_line(__LINE__ - 1);

  n3->next = NULL;
  trace_line(__LINE__ - 1);

  n2->next = n3;
  trace_line(__LINE__ - 1);

  trace_ll_node("head", n3->id, n3->value);
  trace_ll_link("head", n2->id, n3->id);

  // ---- Traversal ----
  Node* temp = head;
  trace_line(__LINE__ - 1);
  trace_ll_pointer("head", "temp", temp->id);

  while (temp != NULL) {
    trace_ll_highlight("head", temp->id);
    trace_ll_pointer("head", "temp", temp->id);

    temp = temp->next;
    trace_line(__LINE__ - 1);
  }

  // ---- Free ----
  trace_ll_free("head", n1->id);
  trace_line(__LINE__ + 1);
  free(n1);
  n1 = NULL;

  trace_ll_free("head", n2->id);
  trace_line(__LINE__ + 1);
  free(n2);
  n2 = NULL;

  trace_ll_free("head", n3->id);
  trace_line(__LINE__ + 1);
  free(n3);
  n3 = NULL;

  return 0;
}
