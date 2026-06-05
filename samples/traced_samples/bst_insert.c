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

Node* insert(Node* root, int data) {
  trace_line(19);
  if (root == NULL) {
    trace_line(20);
    return createNode(data);
  }
  trace_btree_highlight("T", root);
  trace_line(22);
  if (data < root->data) {
    trace_line(23);
    root->left = insert(root->left, data);
    trace_btree_left("T", root, root->left);
  } else {
    trace_line(25);
    root->right = insert(root->right, data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(27);
  return root;
}

void inorder(Node* node) {
  trace_line(31);
  if (node == NULL) return;
  trace_line(32);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(33);
  printf("%d ", node->data);
  trace_line(34);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(38);
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  trace_line(40);
  Node* root = NULL;
  trace_line(41);
  for (int i = 0; i < 7; i++) {
    trace_line(41);
    trace_line(42);
    root = insert(root, values[i]);
  }

  trace_line(45);
  inorder(root);
  trace_line(46);
  printf("\n");

  trace_line(48);
  return 0;
}
