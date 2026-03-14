#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

typedef struct Node {
  char id[10];
  char value[10];
} Node;

int main() {
  trace_tree_init("T");

  // ================= ROOT =================
  Node* R = (Node*)malloc(sizeof(Node));
  strcpy(R->id, "R");
  strcpy(R->value, "R");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", R->id, R->value);

  // ================= LEVEL 1 =================
  Node* n1 = (Node*)malloc(sizeof(Node));
  strcpy(n1->id, "n1");
  strcpy(n1->value, "1");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n1->id, n1->value);
  trace_tree_edge("T", "R", "n1");

  Node* n2 = (Node*)malloc(sizeof(Node));
  strcpy(n2->id, "n2");
  strcpy(n2->value, "2");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n2->id, n2->value);
  trace_tree_edge("T", "R", "n2");

  Node* n3 = (Node*)malloc(sizeof(Node));
  strcpy(n3->id, "n3");
  strcpy(n3->value, "3");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n3->id, n3->value);
  trace_tree_edge("T", "R", "n3");

  // ================= LEVEL 2 =================

  // Children of n1
  Node* n4 = (Node*)malloc(sizeof(Node));
  strcpy(n4->id, "n4");
  strcpy(n4->value, "4");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n4->id, n4->value);
  trace_tree_edge("T", "n1", "n4");

  Node* n5 = (Node*)malloc(sizeof(Node));
  strcpy(n5->id, "n5");
  strcpy(n5->value, "5");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n5->id, n5->value);
  trace_tree_edge("T", "n1", "n5");

  // Child of n2
  Node* n6 = (Node*)malloc(sizeof(Node));
  strcpy(n6->id, "n6");
  strcpy(n6->value, "6");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n6->id, n6->value);
  trace_tree_edge("T", "n2", "n6");

  // Children of n3
  Node* n7 = (Node*)malloc(sizeof(Node));
  strcpy(n7->id, "n7");
  strcpy(n7->value, "7");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n7->id, n7->value);
  trace_tree_edge("T", "n3", "n7");

  Node* n8 = (Node*)malloc(sizeof(Node));
  strcpy(n8->id, "n8");
  strcpy(n8->value, "8");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n8->id, n8->value);
  trace_tree_edge("T", "n3", "n8");

  // ================= LEVEL 3 =================

  Node* n9 = (Node*)malloc(sizeof(Node));
  strcpy(n9->id, "n9");
  strcpy(n9->value, "9");
  trace_line(__LINE__ - 3);
  trace_tree_node("T", n9->id, n9->value);
  trace_tree_edge("T", "n5", "n9");

  // ================= HIGHLIGHT TEST =================
  trace_tree_highlight("T", "R");
  trace_tree_highlight("T", "n5");
  trace_tree_highlight("T", "n9");

  return 0;
}