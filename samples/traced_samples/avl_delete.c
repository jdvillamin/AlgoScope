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
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "T2", T2);
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
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "T2", NULL);
  return x;
}

Node* leftRotate(Node* x) {
  trace_line(45);
  Node* y = x->right;
  trace_line(46);
  Node* T2 = y->left;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "T2", T2);
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
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
  trace_btree_pointer("T", "T2", NULL);
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

Node* minValueNode(Node* node) {
  trace_line(87);
  Node* current = node;
  trace_btree_highlight("T", current);
  trace_line(88);
  while (current->left != NULL) {
    trace_line(89);
    current = current->left;
    trace_btree_highlight("T", current);
  }
  trace_line(91);
  return current;
}

Node* deleteNode(Node* root, int data) {
  trace_line(95);
  if (root == NULL) return NULL;
  trace_btree_highlight("T", root);
  trace_line(97);
  if (data < root->data) {
    trace_line(98);
    root->left = deleteNode(root->left, data);
    trace_btree_left("T", root, root->left);
  } else if (data > root->data) {
    trace_line(100);
    root->right = deleteNode(root->right, data);
    trace_btree_right("T", root, root->right);
  } else {
    trace_line(102);
    if (root->left == NULL) {
      trace_line(103);
      Node* temp = root->right;
      trace_btree_delete("T", root);
      trace_line(104);
      free(root);
      trace_line(105);
      return temp;
    } else if (root->right == NULL) {
      trace_line(107);
      Node* temp = root->left;
      trace_btree_delete("T", root);
      trace_line(108);
      free(root);
      trace_line(109);
      return temp;
    }
    trace_line(111);
    Node* succ = minValueNode(root->right);
    trace_line(112);
    root->data = succ->data;
    trace_btree_update("T", root, root->data);
    trace_line(113);
    root->right = deleteNode(root->right, succ->data);
    trace_btree_right("T", root, root->right);
  }
  trace_line(116);
  root->height = 1 + max(height(root->left), height(root->right));
  trace_line(117);
  int balance = getBalance(root);
  trace_line(119);
  if (balance > 1 && getBalance(root->left) >= 0) {
    trace_line(120);
    return rightRotate(root);
  }
  trace_line(122);
  if (balance > 1 && getBalance(root->left) < 0) {
    trace_line(123);
    root->left = leftRotate(root->left);
    trace_btree_left("T", root, root->left);
    trace_line(124);
    return rightRotate(root);
  }
  trace_line(126);
  if (balance < -1 && getBalance(root->right) <= 0) {
    trace_line(127);
    return leftRotate(root);
  }
  trace_line(129);
  if (balance < -1 && getBalance(root->right) > 0) {
    trace_line(130);
    root->right = rightRotate(root->right);
    trace_btree_right("T", root, root->right);
    trace_line(131);
    return leftRotate(root);
  }
  trace_line(134);
  return root;
}

void inorder(Node* node) {
  trace_line(138);
  if (node == NULL) return;
  trace_line(139);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(140);
  printf("%d ", node->data);
  trace_line(141);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");

  trace_line(145);
  int values[7] = {9, 5, 10, 0, 6, 11, -1};

  trace_line(147);
  Node* root = NULL;
  trace_line(148);
  for (int i = 0; i < 7; i++) {
    trace_line(148);
    trace_line(149);
    root = insert(root, values[i]);
  }

  trace_line(152);
  root = deleteNode(root, 10);

  trace_line(154);
  inorder(root);
  trace_line(155);
  printf("\n");

  trace_line(157);
  return 0;
}
