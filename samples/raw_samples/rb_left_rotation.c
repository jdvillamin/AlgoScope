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

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(10, 'B');
  Node* a = createNode(5, 'B');
  Node* y = createNode(20, 'R');
  Node* b = createNode(15, 'B');
  Node* c = createNode(25, 'B');

  root->left = a;
  a->parent = root;
  root->right = y;
  y->parent = root;
  y->left = b;
  b->parent = y;
  y->right = c;
  c->parent = y;

  inorder(root);
  printf("\n");

  leftRotate(&root, root);

  root->color = 'B';
  root->left->color = 'R';

  inorder(root);
  printf("\n");

  return 0;
}
