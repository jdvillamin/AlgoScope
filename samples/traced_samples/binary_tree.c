#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(const char* id, const char* value) {
  trace_line(13);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(14);
  strcpy(n->id, id);
  trace_line(15);
  strcpy(n->value, value);
  trace_line(16);
  n->left = NULL;
  trace_line(17);
  n->right = NULL;
  trace_line(18);
  return n;
}

void inorder(Node* node) {
  trace_line(22);
  if (node == NULL) return;
  trace_line(23);
  inorder(node->left);
  trace_btree_highlight("T", node->id);
  trace_line(24);
  printf("%s ", node->value);
  trace_line(25);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  // Build a binary search tree
  trace_line(30);
  Node* n50 = createNode("n50", "50");
  trace_btree_node("T", n50->id, n50->value);
  trace_line(31);
  Node* n30 = createNode("n30", "30");
  trace_btree_node("T", n30->id, n30->value);
  trace_line(32);
  Node* n70 = createNode("n70", "70");
  trace_btree_node("T", n70->id, n70->value);
  trace_line(33);
  Node* n20 = createNode("n20", "20");
  trace_btree_node("T", n20->id, n20->value);
  trace_line(34);
  Node* n40 = createNode("n40", "40");
  trace_btree_node("T", n40->id, n40->value);
  trace_line(35);
  Node* n60 = createNode("n60", "60");
  trace_btree_node("T", n60->id, n60->value);
  trace_line(36);
  Node* n80 = createNode("n80", "80");
  trace_btree_node("T", n80->id, n80->value);

  trace_line(38);
  n50->left = n30;
  trace_btree_left("T", n50->id, n50->left->id);
  trace_line(39);
  n50->right = n70;
  trace_btree_right("T", n50->id, n50->right->id);
  trace_line(40);
  n30->left = n20;
  trace_btree_left("T", n30->id, n30->left->id);
  trace_line(41);
  n30->right = n40;
  trace_btree_right("T", n30->id, n30->right->id);
  trace_line(42);
  n70->left = n60;
  trace_btree_left("T", n70->id, n70->left->id);
  trace_line(43);
  n70->right = n80;
  trace_btree_right("T", n70->id, n70->right->id);

  trace_line(45);
  inorder(n50);
  trace_line(46);
  printf("\n");

  trace_line(48);
  return 0;
}
