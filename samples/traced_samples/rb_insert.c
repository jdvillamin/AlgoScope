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

Node* createNode(int data) {
  trace_line(16);
  Node* n = (Node*)malloc(sizeof(Node));
  trace_line(17);
  n->data = data;
  trace_line(18);
  n->color = 'R';
  trace_line(19);
  n->left = NIL;
  trace_line(20);
  n->right = NIL;
  trace_line(21);
  n->parent = NIL;
  trace_btree_node("T", n, n->data);
  trace_btree_color("T", n, "R");
  trace_line(22);
  return n;
}

void leftRotate(Node** root, Node* x) {
  trace_line(26);
  Node* y = x->right;
  trace_btree_pointer("T", "x", x);
  trace_btree_pointer("T", "y", y == NIL ? NULL : y);
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

void rightRotate(Node** root, Node* y) {
  trace_line(44);
  Node* x = y->left;
  trace_btree_pointer("T", "y", y);
  trace_btree_pointer("T", "x", x == NIL ? NULL : x);
  trace_line(45);
  y->left = x->right;
  trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
  trace_line(46);
  if (x->right != NIL) {
    trace_line(47);
    x->right->parent = y;
  }
  trace_line(49);
  x->parent = y->parent;
  trace_line(50);
  if (y->parent == NIL) {
    trace_line(51);
    *root = x;
  } else if (y == y->parent->left) {
    trace_line(53);
    y->parent->left = x;
    trace_btree_left("T", y->parent, x);
  } else {
    trace_line(55);
    y->parent->right = x;
    trace_btree_right("T", y->parent, x);
  }
  trace_line(57);
  x->right = y;
  trace_btree_right("T", x, y);
  trace_line(58);
  y->parent = x;
  trace_btree_pointer("T", "x", NULL);
  trace_btree_pointer("T", "y", NULL);
}

void insertFixup(Node** root, Node* z) {
  trace_line(62);
  while (z->parent->color == 'R') {
    trace_line(62);
    trace_btree_pointer("T", "z", z);
    trace_btree_highlight("T", z);
    trace_line(63);
    if (z->parent == z->parent->parent->left) {
      trace_line(64);
      Node* u = z->parent->parent->right;
      trace_btree_pointer("T", "u", u == NIL ? NULL : u);
      trace_line(65);
      if (u->color == 'R') {
        trace_line(66);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(67);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(68);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(69);
        z = z->parent->parent;
        trace_btree_pointer("T", "z", z);
      } else {
        trace_line(71);
        if (z == z->parent->right) {
          trace_line(72);
          z = z->parent;
          trace_btree_pointer("T", "z", z);
          trace_line(73);
          leftRotate(root, z);
        }
        trace_line(75);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(76);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(77);
        rightRotate(root, z->parent->parent);
      }
    } else {
      trace_line(80);
      Node* u = z->parent->parent->left;
      trace_btree_pointer("T", "u", u == NIL ? NULL : u);
      trace_line(81);
      if (u->color == 'R') {
        trace_line(82);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(83);
        u->color = 'B';
        trace_btree_color("T", u, "B");
        trace_line(84);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(85);
        z = z->parent->parent;
        trace_btree_pointer("T", "z", z);
      } else {
        trace_line(87);
        if (z == z->parent->left) {
          trace_line(88);
          z = z->parent;
          trace_btree_pointer("T", "z", z);
          trace_line(89);
          rightRotate(root, z);
        }
        trace_line(91);
        z->parent->color = 'B';
        trace_btree_color("T", z->parent, "B");
        trace_line(92);
        z->parent->parent->color = 'R';
        trace_btree_color("T", z->parent->parent, "R");
        trace_line(93);
        leftRotate(root, z->parent->parent);
      }
    }
  }
  trace_btree_pointer("T", "z", NULL);
  trace_btree_pointer("T", "u", NULL);
  trace_line(97);
  (*root)->color = 'B';
  trace_btree_color("T", *root, "B");
}

void insert(Node** root, int data) {
  trace_line(101);
  Node* z = createNode(data);
  trace_line(102);
  Node* y = NIL;
  trace_line(103);
  Node* x = *root;
  trace_line(104);
  while (x != NIL) {
    trace_line(104);
    trace_btree_highlight("T", x);
    trace_line(105);
    y = x;
    trace_line(106);
    if (z->data < x->data) {
      trace_line(107);
      x = x->left;
    } else {
      trace_line(109);
      x = x->right;
    }
  }
  trace_line(112);
  z->parent = y;
  trace_line(113);
  if (y == NIL) {
    trace_line(114);
    *root = z;
  } else if (z->data < y->data) {
    trace_line(116);
    y->left = z;
    trace_btree_left("T", y, z);
  } else {
    trace_line(118);
    y->right = z;
    trace_btree_right("T", y, z);
  }
  trace_line(120);
  insertFixup(root, z);
}

void inorder(Node* node) {
  trace_line(124);
  if (node == NIL) return;
  trace_line(125);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(126);
  printf("%d ", node->data);
  trace_line(127);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(131);
  NIL->color = 'B';

  trace_line(133);
  int values[8] = {10, 20, 30, 15, 25, 5, 1, 2};

  trace_line(135);
  Node* root = NIL;
  trace_line(136);
  for (int i = 0; i < 8; i++) {
    trace_line(136);
    trace_line(137);
    insert(&root, values[i]);
  }

  trace_line(140);
  inorder(root);
  trace_line(141);
  printf("\n");

  trace_line(143);
  return 0;
}
