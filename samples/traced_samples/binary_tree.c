#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  trace_line(11);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(12);
  n->data = data;
  trace_line(13);
  n->left = NULL;
  trace_line(14);
  n->right = NULL;
  trace_btree_node("T", n, n->data);
  trace_line(15);
  return n;
}

void inorder(Node* node) {
  trace_line(19);
  if (node == NULL) return;
  trace_line(20);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(21);
  printf("%d ", node->data);
  trace_line(22);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(26);
  Node* n50 = createNode(50);
  trace_line(27);
  Node* n30 = createNode(30);
  trace_line(28);
  Node* n70 = createNode(70);
  trace_line(29);
  Node* n20 = createNode(20);
  trace_line(30);
  Node* n40 = createNode(40);
  trace_line(31);
  Node* n60 = createNode(60);
  trace_line(32);
  Node* n80 = createNode(80);

  trace_line(34);
  n50->left = n30;
  trace_btree_left("T", n50, n50->left);
  trace_line(35);
  n50->right = n70;
  trace_btree_right("T", n50, n50->right);
  trace_line(36);
  n30->left = n20;
  trace_btree_left("T", n30, n30->left);
  trace_line(37);
  n30->right = n40;
  trace_btree_right("T", n30, n30->right);
  trace_line(38);
  n70->left = n60;
  trace_btree_left("T", n70, n70->left);
  trace_line(39);
  n70->right = n80;
  trace_btree_right("T", n70, n70->right);

  trace_line(41);
  inorder(n50);
  trace_line(42);
  printf("\n");

  trace_line(44);
  return 0;
}
