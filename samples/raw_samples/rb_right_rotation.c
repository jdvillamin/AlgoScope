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

Node* createNode(int data, char color) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->color = color;
  n->left = NIL;
  n->right = NIL;
  n->parent = NIL;
  return n;
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

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(20, 'B');
  Node* x = createNode(10, 'R');
  Node* a = createNode(5, 'B');
  Node* b = createNode(15, 'B');
  Node* c = createNode(25, 'B');

  root->left = x;
  x->parent = root;
  root->right = c;
  c->parent = root;
  x->left = a;
  a->parent = x;
  x->right = b;
  b->parent = x;

  inorder(root);
  printf("\n");

  rightRotate(&root, root);

  root->color = 'B';
  root->right->color = 'R';

  inorder(root);
  printf("\n");

  return 0;
}
