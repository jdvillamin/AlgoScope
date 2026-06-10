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

void leftRotate(Node** root, Node* x) {
  trace_line(26);
  Node* y = x->right;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y == NIL ? NULL : y);
  trace_btree_highlight("T", x);
  trace_line(27);
  x->right = y->left;
  trace_btree_right("T", x, x->right == NIL ? NULL : x->right);
  trace_line(28);
  if (y->left != NIL) {
    trace_line(29);
    y->left->parent = x;
  }
  trace_line(31);
  y->parent = x->parent;
  trace_line(32);
  if (x->parent == NIL) {
    trace_line(33);
    *root = y;
  } else if (x == x->parent->left) {
    trace_line(35);
    x->parent->left = y;
    trace_btree_left("T", x->parent, y);
  } else {
    trace_line(37);
    x->parent->right = y;
    trace_btree_right("T", x->parent, y);
  }
  trace_line(39);
  y->left = x;
  trace_btree_left("T", y, x);
  trace_line(40);
  x->parent = y;
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
  Node* root = createNode(10, 'B');
  trace_line(54);
  Node* a = createNode(5, 'B');
  trace_line(55);
  Node* y = createNode(20, 'R');
  trace_line(56);
  Node* b = createNode(15, 'B');
  trace_line(57);
  Node* c = createNode(25, 'B');

  trace_line(59);
  root->left = a;
  trace_btree_left("T", root, a);
  trace_line(60);
  a->parent = root;
  trace_line(61);
  root->right = y;
  trace_btree_right("T", root, y);
  trace_line(62);
  y->parent = root;
  trace_line(63);
  y->left = b;
  trace_btree_left("T", y, b);
  trace_line(64);
  b->parent = y;
  trace_line(65);
  y->right = c;
  trace_btree_right("T", y, c);
  trace_line(66);
  c->parent = y;

  trace_line(68);
  inorder(root);
  trace_line(69);
  printf("\n");

  trace_line(71);
  leftRotate(&root, root);

  trace_line(73);
  root->color = 'B';
  trace_btree_color("T", root, "B");
  trace_line(74);
  root->left->color = 'R';
  trace_btree_color("T", root->left, "R");

  trace_line(76);
  inorder(root);
  trace_line(77);
  printf("\n");

  trace_line(79);
  return 0;
}
