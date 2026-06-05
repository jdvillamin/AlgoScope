#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  trace_line(21);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(22);
  n->data = data;
  trace_line(23);
  n->left = NULL;
  trace_line(24);
  n->right = NULL;
  trace_line(25);
  n->height = 1;
  trace_btree_node("T", n, n->data);
  trace_line(26);
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  trace_line(35);
  Node* x = y->left;
  trace_line(36);
  Node* T2 = x->right;
  trace_btree_highlight("T", y);
  trace_btree_highlight("T", x);
  trace_line(37);
  x->right = y;
  trace_btree_right("T", x, x->right);
  trace_line(38);
  y->left = T2;
  trace_btree_left("T", y, y->left);
  trace_line(39);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(40);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(41);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_highlight("T", x);
  trace_btree_highlight("T", y);
  trace_line(47);
  y->left = x;
  trace_btree_left("T", y, y->left);
  trace_line(48);
  x->right = T2;
  trace_btree_right("T", x, x->right);
  trace_line(49);
  x->height = max(height(x->left), height(x->right)) + 1;
  trace_line(50);
  y->height = max(height(y->left), height(y->right)) + 1;
  trace_line(51);
  return y;
}

Node* insert(Node* node, int data) {
  trace_line(55);
  if (node == NULL) return createNode(data);
  trace_btree_highlight("T", node);
  trace_line(57);
  if (data < node->data) {
    trace_line(58);
    node->left = insert(node->left, data);
    trace_btree_left("T", node, node->left);
  } else if (data > node->data) {
    trace_line(60);
    node->right = insert(node->right, data);
    trace_btree_right("T", node, node->right);
  } else {
    trace_line(62);
    return node;
  }
  trace_line(65);
  node->height = 1 + max(height(node->left), height(node->right));
  trace_line(66);
  int balance = getBalance(node);
  trace_line(68);
  if (balance > 1 && data < node->left->data) {
    trace_line(69);
    return rightRotate(node);
  }
  trace_line(71);
  if (balance < -1 && data > node->right->data) {
    trace_line(72);
    return leftRotate(node);
  }
  trace_line(74);
  if (balance > 1 && data > node->left->data) {
    trace_line(75);
    node->left = leftRotate(node->left);
    trace_btree_left("T", node, node->left);
    trace_line(76);
    return rightRotate(node);
  }
  trace_line(78);
  if (balance < -1 && data < node->right->data) {
    trace_line(79);
    node->right = rightRotate(node->right);
    trace_btree_right("T", node, node->right);
    trace_line(80);
    return leftRotate(node);
  }
  trace_line(83);
  return node;
}

void inorder(Node* node) {
  trace_line(87);
  if (node == NULL) return;
  trace_line(88);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(89);
  printf("%d ", node->data);
  trace_line(90);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(94);
  Node* root = NULL;

  trace_line(96);
  root = insert(root, 10);
  trace_line(97);
  root = insert(root, 20);
  trace_line(98);
  root = insert(root, 30);

  trace_line(100);
  inorder(root);
  trace_line(101);
  printf("\n");

  trace_line(103);
  return 0;
}
