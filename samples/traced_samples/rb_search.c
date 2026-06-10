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

Node* search(Node* root, int key) {
  trace_line(26);
  Node* cur = root;
  trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  trace_line(27);
  while (cur != NIL && cur->data != key) {
    trace_line(27);
    trace_btree_highlight("T", cur);
    trace_line(28);
    if (key < cur->data) {
      trace_line(29);
      cur = cur->left;
    } else {
      trace_line(31);
      cur = cur->right;
    }
    trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  }
  trace_btree_highlight("T", cur == NIL ? NULL : cur);
  trace_btree_pointer("T", "cur", NULL);
  trace_line(34);
  return cur;
}

int main() {
  trace_btree_init("T");
  trace_line(38);
  NIL->color = 'B';

  trace_line(40);
  Node* root = createNode(15, 'B');
  trace_line(41);
  Node* l = createNode(10, 'R');
  trace_line(42);
  Node* r = createNode(20, 'R');
  trace_line(43);
  Node* a = createNode(5, 'B');
  trace_line(44);
  Node* b = createNode(12, 'B');
  trace_line(45);
  Node* c = createNode(17, 'B');
  trace_line(46);
  Node* d = createNode(25, 'B');

  trace_line(48);
  root->left = l;
  trace_btree_left("T", root, l);
  trace_line(49);
  l->parent = root;
  trace_line(50);
  root->right = r;
  trace_btree_right("T", root, r);
  trace_line(51);
  r->parent = root;
  trace_line(52);
  l->left = a;
  trace_btree_left("T", l, a);
  trace_line(53);
  a->parent = l;
  trace_line(54);
  l->right = b;
  trace_btree_right("T", l, b);
  trace_line(55);
  b->parent = l;
  trace_line(56);
  r->left = c;
  trace_btree_left("T", r, c);
  trace_line(57);
  c->parent = r;
  trace_line(58);
  r->right = d;
  trace_btree_right("T", r, d);
  trace_line(59);
  d->parent = r;

  trace_line(61);
  Node* found = search(root, 12);
  trace_btree_pointer("T", "found", found == NIL ? NULL : found);
  trace_line(62);
  if (found != NIL) {
    trace_line(63);
    printf("Found %d (%c)\n", found->data, found->color);
  } else {
    trace_line(65);
    printf("12 not found\n");
  }

  trace_line(68);
  found = search(root, 19);
  trace_btree_pointer("T", "found", found == NIL ? NULL : found);
  trace_line(69);
  if (found != NIL) {
    trace_line(70);
    printf("Found %d (%c)\n", found->data, found->color);
  } else {
    trace_line(72);
    printf("19 not found\n");
  }

  trace_line(75);
  return 0;
}
