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
}

void rightRotate(Node** root, Node* y) {
  trace_line(44);
  Node* x = y->left;
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
}

void insertFixup(Node** root, Node* z) {
  trace_line(62);
  while (z->parent->color == 'R') {
    trace_line(62);
    trace_btree_highlight("T", z);
    trace_line(63);
    if (z->parent == z->parent->parent->left) {
      trace_line(64);
      Node* u = z->parent->parent->right;
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
      } else {
        trace_line(71);
        if (z == z->parent->right) {
          trace_line(72);
          z = z->parent;
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
      } else {
        trace_line(87);
        if (z == z->parent->left) {
          trace_line(88);
          z = z->parent;
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

Node* search(Node* root, int key) {
  trace_line(124);
  Node* cur = root;
  trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  trace_line(125);
  while (cur != NIL && cur->data != key) {
    trace_line(125);
    trace_btree_highlight("T", cur);
    trace_line(126);
    if (key < cur->data) {
      trace_line(127);
      cur = cur->left;
    } else {
      trace_line(129);
      cur = cur->right;
    }
    trace_btree_pointer("T", "cur", cur == NIL ? NULL : cur);
  }
  trace_btree_pointer("T", "cur", NULL);
  trace_line(132);
  return cur;
}

Node* minimum(Node* x) {
  trace_line(136);
  while (x->left != NIL) {
    trace_line(136);
    trace_btree_highlight("T", x);
    trace_line(137);
    x = x->left;
  }
  trace_btree_highlight("T", x);
  trace_line(139);
  return x;
}

void transplant(Node** root, Node* u, Node* v) {
  trace_line(143);
  if (u->parent == NIL) {
    trace_line(144);
    *root = v;
  } else if (u == u->parent->left) {
    trace_line(146);
    u->parent->left = v;
    trace_btree_left("T", u->parent, v == NIL ? NULL : v);
  } else {
    trace_line(148);
    u->parent->right = v;
    trace_btree_right("T", u->parent, v == NIL ? NULL : v);
  }
  trace_line(150);
  v->parent = u->parent;
}

void deleteFixup(Node** root, Node* x) {
  trace_line(154);
  while (x != *root && x->color == 'B') {
    trace_line(154);
    trace_btree_highlight("T", x == NIL ? NULL : x);
    trace_line(155);
    if (x == x->parent->left) {
      trace_line(156);
      Node* w = x->parent->right;
      trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      trace_line(157);
      if (w->color == 'R') {
        trace_line(158);
        w->color = 'B';
        trace_btree_color("T", w, "B");
        trace_line(159);
        x->parent->color = 'R';
        trace_btree_color("T", x->parent, "R");
        trace_line(160);
        leftRotate(root, x->parent);
        trace_line(161);
        w = x->parent->right;
        trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      }
      trace_line(163);
      if (w->left->color == 'B' && w->right->color == 'B') {
        trace_line(164);
        w->color = 'R';
        trace_btree_color("T", w, "R");
        trace_line(165);
        x = x->parent;
      } else {
        trace_line(167);
        if (w->right->color == 'B') {
          trace_line(168);
          w->left->color = 'B';
          trace_btree_color("T", w->left == NIL ? NULL : w->left, "B");
          trace_line(169);
          w->color = 'R';
          trace_btree_color("T", w, "R");
          trace_line(170);
          rightRotate(root, w);
          trace_line(171);
          w = x->parent->right;
          trace_btree_pointer("T", "w", w == NIL ? NULL : w);
        }
        trace_line(173);
        w->color = x->parent->color;
        trace_btree_color("T", w, w->color == 'R' ? "R" : "B");
        trace_line(174);
        x->parent->color = 'B';
        trace_btree_color("T", x->parent, "B");
        trace_line(175);
        w->right->color = 'B';
        trace_btree_color("T", w->right == NIL ? NULL : w->right, "B");
        trace_line(176);
        leftRotate(root, x->parent);
        trace_line(177);
        x = *root;
      }
    } else {
      trace_line(180);
      Node* w = x->parent->left;
      trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      trace_line(181);
      if (w->color == 'R') {
        trace_line(182);
        w->color = 'B';
        trace_btree_color("T", w, "B");
        trace_line(183);
        x->parent->color = 'R';
        trace_btree_color("T", x->parent, "R");
        trace_line(184);
        rightRotate(root, x->parent);
        trace_line(185);
        w = x->parent->left;
        trace_btree_pointer("T", "w", w == NIL ? NULL : w);
      }
      trace_line(187);
      if (w->right->color == 'B' && w->left->color == 'B') {
        trace_line(188);
        w->color = 'R';
        trace_btree_color("T", w, "R");
        trace_line(189);
        x = x->parent;
      } else {
        trace_line(191);
        if (w->left->color == 'B') {
          trace_line(192);
          w->right->color = 'B';
          trace_btree_color("T", w->right == NIL ? NULL : w->right, "B");
          trace_line(193);
          w->color = 'R';
          trace_btree_color("T", w, "R");
          trace_line(194);
          leftRotate(root, w);
          trace_line(195);
          w = x->parent->left;
          trace_btree_pointer("T", "w", w == NIL ? NULL : w);
        }
        trace_line(197);
        w->color = x->parent->color;
        trace_btree_color("T", w, w->color == 'R' ? "R" : "B");
        trace_line(198);
        x->parent->color = 'B';
        trace_btree_color("T", x->parent, "B");
        trace_line(199);
        w->left->color = 'B';
        trace_btree_color("T", w->left == NIL ? NULL : w->left, "B");
        trace_line(200);
        rightRotate(root, x->parent);
        trace_line(201);
        x = *root;
      }
    }
  }
  trace_btree_pointer("T", "w", NULL);
  trace_line(205);
  x->color = 'B';
  trace_btree_color("T", x == NIL ? NULL : x, "B");
}

void deleteNode(Node** root, Node* z) {
  trace_btree_highlight("T", z);
  trace_line(209);
  Node* y = z;
  trace_line(210);
  Node* x;
  trace_line(211);
  char yColor = y->color;
  trace_line(212);
  if (z->left == NIL) {
    trace_line(213);
    x = z->right;
    trace_line(214);
    transplant(root, z, z->right);
  } else if (z->right == NIL) {
    trace_line(216);
    x = z->left;
    trace_line(217);
    transplant(root, z, z->left);
  } else {
    trace_line(219);
    y = minimum(z->right);
    trace_btree_pointer("T", "y", y);
    trace_line(220);
    yColor = y->color;
    trace_line(221);
    x = y->right;
    trace_line(222);
    if (y->parent == z) {
      trace_line(223);
      x->parent = y;
    } else {
      trace_line(225);
      transplant(root, y, y->right);
      trace_line(226);
      y->right = z->right;
      trace_btree_right("T", y, y->right == NIL ? NULL : y->right);
      trace_line(227);
      y->right->parent = y;
    }
    trace_line(229);
    transplant(root, z, y);
    trace_line(230);
    y->left = z->left;
    trace_btree_left("T", y, y->left == NIL ? NULL : y->left);
    trace_line(231);
    y->left->parent = y;
    trace_line(232);
    y->color = z->color;
    trace_btree_color("T", y, y->color == 'R' ? "R" : "B");
    trace_btree_pointer("T", "y", NULL);
  }
  trace_btree_delete("T", z);
  trace_line(234);
  free(z);
  trace_line(235);
  if (yColor == 'B') {
    trace_line(236);
    deleteFixup(root, x);
  }
}

void deleteValue(Node** root, int key) {
  trace_line(241);
  Node* z = search(*root, key);
  trace_line(242);
  if (z != NIL) {
    trace_line(243);
    deleteNode(root, z);
  }
}

void inorder(Node* node) {
  trace_line(248);
  if (node == NIL) return;
  trace_line(249);
  inorder(node->left);
  trace_btree_highlight("T", node);
  trace_line(250);
  printf("%d ", node->data);
  trace_line(251);
  inorder(node->right);
}

int main() {
  trace_btree_init("T");
  trace_line(255);
  NIL->color = 'B';

  trace_line(257);
  int values[7] = {10, 5, 15, 3, 7, 12, 20};
  trace_line(258);
  Node* root = NIL;
  trace_line(259);
  for (int i = 0; i < 7; i++) {
    trace_line(259);
    trace_line(260);
    insert(&root, values[i]);
  }
  trace_line(262);
  inorder(root);
  trace_line(263);
  printf("\n");

  trace_line(265);
  int keys[5] = {3, 5, 15, 10, 7};
  trace_line(266);
  for (int i = 0; i < 5; i++) {
    trace_line(266);
    trace_line(267);
    deleteValue(&root, keys[i]);
    trace_line(268);
    inorder(root);
    trace_line(269);
    printf("\n");
  }

  trace_line(272);
  return 0;
}
