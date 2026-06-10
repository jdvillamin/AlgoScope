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

Node* search(Node* root, int key) {
  Node* cur = root;
  while (cur != NIL && cur->data != key) {
    if (key < cur->data) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return cur;
}

int main() {
  NIL->color = 'B';

  Node* root = createNode(15, 'B');
  Node* l = createNode(10, 'R');
  Node* r = createNode(20, 'R');
  Node* a = createNode(5, 'B');
  Node* b = createNode(12, 'B');
  Node* c = createNode(17, 'B');
  Node* d = createNode(25, 'B');

  root->left = l;
  l->parent = root;
  root->right = r;
  r->parent = root;
  l->left = a;
  a->parent = l;
  l->right = b;
  b->parent = l;
  r->left = c;
  c->parent = r;
  r->right = d;
  d->parent = r;

  Node* found = search(root, 12);
  if (found != NIL) {
    printf("Found %d (%c)\n", found->data, found->color);
  } else {
    printf("12 not found\n");
  }

  found = search(root, 19);
  if (found != NIL) {
    printf("Found %d (%c)\n", found->data, found->color);
  } else {
    printf("19 not found\n");
  }

  return 0;
}
