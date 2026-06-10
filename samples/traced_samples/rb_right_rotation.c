#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

typedef struct Node {
  int data;
  char color;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

Node nil;
Node* NIL = &nil;

Node* createNode(int data, char color) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = color;
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, color == 'R' ? "R" : "B");
  trace_line(22);
  return n;
}

void rightRotate(Node** root, Node* y) {
  trace_line(26);
  Node* x = y->left;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x == NIL ? NULL : x);
  trace_btree_highlight("T", y);
  trace_line(27);
  y->left = x->right;
  trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
  trace_line(28);
  if (x->right != NIL) {
    trace_line(29);
    x->right->parent = y;
  }
  trace_line(31);
  x->parent = y->parent;
  trace_line(32);
  if (y->parent == NIL) {
    trace_line(33);
    *root = x;
  } else if (y == y->parent->left) {
    trace_line(35);
    y->parent->left = x;
    trace_btree_left("T", y->parent, x);
  } else {
    trace_line(37);
    y->parent->right = x;
    trace_btree_right("T", y->parent, x);
  }
  trace_line(39);
  x->right = y;
  trace_btree_right("T", x, y);
  trace_line(40);
  y->parent = x;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void inorder(Node* node) {
  trace_line(44);
  if (node == NIL) return;
  trace_line(45);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(46);
  printf("%d ", node->data);
  trace_line(47);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(51);
  NIL->color = 'B';

  trace_line(53);
  Node* root = createNode(20, 'B');
  trace_line(54);
  Node* x = createNode(10, 'R');
  trace_line(55);
  Node* a = createNode(5, 'B');
  trace_line(56);
  Node* b = createNode(15, 'B');
  trace_line(57);
  Node* c = createNode(25, 'B');

  trace_line(59);
  root->left = x;
  trace_btree_left("T", root, x);
  trace_line(60);
  x->parent = root;
  trace_line(61);
  root->right = c;
  trace_btree_right("T", root, c);
  trace_line(62);
  c->parent = root;
  trace_line(63);
  x->left = a;
  trace_btree_left("T", x, a);
  trace_line(64);
  a->parent = x;
  trace_line(65);
  x->right = b;
  trace_btree_right("T", x, b);
  trace_line(66);
  b->parent = x;

  trace_line(68);
  inorder(root);
  trace_line(69);
  printf("\n");

  trace_line(71);
  rightRotate(&root, root);

  trace_line(73);
  root->color = 'B';
  trace_btree_color("T", root, "B");
  trace_line(74);
  root->right->color = 'R';
  trace_btree_color("T", root->right, "R");

  trace_line(76);
  inorder(root);
  trace_line(77);
  printf("\n");

  trace_line(79);
  return 0;
}
