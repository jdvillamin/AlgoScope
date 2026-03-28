#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

#define MAX_CHILDREN 10

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* children[MAX_CHILDREN];
  int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
  trace_line(17);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(18);
  strcpy(n->id, id);
  trace_line(19);
  strcpy(n->value, value);
  trace_line(20);
  n->childCount = 0;
  trace_line(21);
  return n;
}

void addChild(Node* parent, Node* child) {
  trace_line(25);
  parent->children[parent->childCount++] = child;
}

void preorder(Node* node) {
  trace_line(29);
  if (node == NULL) return;
  trace_tree_highlight("T", node->id);
  trace_line(30);
  printf("%s ", node->value);
  trace_line(31);
  for (int i = 0; i < node->childCount; i++) {
    trace_line(31);
    trace_line(32);
    preorder(node->children[i]);
  }
}

int main() {
  trace_tree_init("T");

  // ================= BUILD TREE =================
  trace_line(38);
  Node* R = createNode("R", "R");
  trace_tree_node("T", R->id, R->value);

  trace_line(40);
  Node* n1 = createNode("n1", "1");
  trace_tree_node("T", n1->id, n1->value);
  trace_line(41);
  Node* n2 = createNode("n2", "2");
  trace_tree_node("T", n2->id, n2->value);
  trace_line(42);
  Node* n3 = createNode("n3", "3");
  trace_tree_node("T", n3->id, n3->value);
  trace_line(43);
  addChild(R, n1);
  trace_tree_edge("T", R->id, n1->id);
  trace_line(44);
  addChild(R, n2);
  trace_tree_edge("T", R->id, n2->id);
  trace_line(45);
  addChild(R, n3);
  trace_tree_edge("T", R->id, n3->id);

  trace_line(47);
  Node* n4 = createNode("n4", "4");
  trace_tree_node("T", n4->id, n4->value);
  trace_line(48);
  Node* n5 = createNode("n5", "5");
  trace_tree_node("T", n5->id, n5->value);
  trace_line(49);
  addChild(n1, n4);
  trace_tree_edge("T", n1->id, n4->id);
  trace_line(50);
  addChild(n1, n5);
  trace_tree_edge("T", n1->id, n5->id);

  trace_line(52);
  Node* n6 = createNode("n6", "6");
  trace_tree_node("T", n6->id, n6->value);
  trace_line(53);
  addChild(n2, n6);
  trace_tree_edge("T", n2->id, n6->id);

  trace_line(55);
  Node* n7 = createNode("n7", "7");
  trace_tree_node("T", n7->id, n7->value);
  trace_line(56);
  Node* n8 = createNode("n8", "8");
  trace_tree_node("T", n8->id, n8->value);
  trace_line(57);
  addChild(n3, n7);
  trace_tree_edge("T", n3->id, n7->id);
  trace_line(58);
  addChild(n3, n8);
  trace_tree_edge("T", n3->id, n8->id);

  trace_line(60);
  Node* n9 = createNode("n9", "9");
  trace_tree_node("T", n9->id, n9->value);
  trace_line(61);
  addChild(n4, n9);
  trace_tree_edge("T", n4->id, n9->id);

  // ================= PREORDER TRAVERSAL =================
  trace_line(64);
  preorder(R);
  trace_line(65);
  printf("\n");

  trace_line(67);
  return 0;
}
