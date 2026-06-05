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

Node* findMin(Node* node) {
  trace_btree_highlight("T", node);
  trace_line(31);
  while (node->left != NULL) {
    trace_line(31);
    trace_line(32);
    node = node->left;
    trace_btree_highlight("T", node);
  }
  trace_line(34);
  return node;
}

Node* deleteNode(Node* root, int data) {
  trace_line(38);
  if (root == NULL) return NULL;

  trace_btree_highlight("T", root);
  trace_line(40);
  if (data < root->data) {
    trace_line(41);
    root->left = deleteNode(root->left, data);
    trace_btree_left("T", root, root->left);
  } else if (data > root->data) {
    trace_line(43);
    root->right = deleteNode(root->right, data);
    trace_btree_right("T", root, root->right);
  } else {
    trace_line(45);
    if (root->left == NULL) {
      trace_line(46);
      Node* temp = root->right;
      trace_btree_delete("T", root);
      trace_line(47);
      free(root);
      trace_line(48);
      return temp;
    } else if (root->right == NULL) {
      trace_line(50);
      Node* temp = root->left;
      trace_btree_delete("T", root);
      trace_line(51);
      free(root);
      trace_line(52);
      return temp;
    }
    trace_line(54);
    Node* succ = findMin(root->right);
    trace_line(55);
    root->data = succ->data;
    trace_btree_update("T", root, root->data);
    trace_line(56);
    root->right = deleteNode(root->right, succ->data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(58);
  return root;
}

int main() {
  trace_btree_init("T");

  trace_line(62);
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  trace_line(64);
  Node* root = NULL;
  trace_line(65);
  for (int i = 0; i < 7; i++) {
    trace_line(65);
    trace_line(66);
    root = insert(root, values[i]);
  }

  trace_line(69);
  root = deleteNode(root, 20);
  trace_line(70);
  root = deleteNode(root, 30);
  trace_line(71);
  root = deleteNode(root, 50);

  trace_line(73);
  return 0;
}
