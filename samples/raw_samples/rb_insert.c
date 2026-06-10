#include <stdio.h>
#include <stdlib.h>

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
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = 'R';
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
}

void leftRotate(Node** root, Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NIL) {
    *root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rightRotate(Node** root, Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != NIL) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NIL) {
    *root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void insertFixup(Node** root, Node* z) {
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      Node* u = z->parent->parent->right;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(root, z->parent->parent);
      }
    } else {
      Node* u = z->parent->parent->left;
      if (u->color == 'R') {
        z->parent->color = 'B';
        u->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(root, z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(root, z->parent->parent);
      }
    }
  }
  (*root)->color = 'B';
}

void insert(Node** root, int data) {
  Node* z = createNode(data);
  Node* y = NIL;
  Node* x = *root;
  while (x != NIL) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NIL) {
    *root = z;
  } else if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }
  insertFixup(root, z);
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  int values[8] = {10, 20, 30, 15, 25, 5, 1, 2};

  Node* root = NIL;
  for (int i = 0; i < 8; i++) {
    insert(&root, values[i]);
  }

  inorder(root);
  printf("\n");

  return 0;
}
