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

Node* minimum(Node* x) {
  while (x->left != NIL) {
    x = x->left;
  }
  return x;
}

void transplant(Node** root, Node* u, Node* v) {
  if (u->parent == NIL) {
    *root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void deleteFixup(Node** root, Node* x) {
  while (x != *root && x->color == 'B') {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        leftRotate(root, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == 'B' && w->right->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->right->color == 'B') {
          w->left->color = 'B';
          w->color = 'R';
          rightRotate(root, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        leftRotate(root, x->parent);
        x = *root;
      }
    } else {
      Node* w = x->parent->left;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        rightRotate(root, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == 'B' && w->left->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->left->color == 'B') {
          w->right->color = 'B';
          w->color = 'R';
          leftRotate(root, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        rightRotate(root, x->parent);
        x = *root;
      }
    }
  }
  x->color = 'B';
}

void deleteNode(Node** root, Node* z) {
  Node* y = z;
  Node* x;
  char yColor = y->color;
  if (z->left == NIL) {
    x = z->right;
    transplant(root, z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    transplant(root, z, z->left);
  } else {
    y = minimum(z->right);
    yColor = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  free(z);
  if (yColor == 'B') {
    deleteFixup(root, x);
  }
}

void deleteValue(Node** root, int key) {
  Node* z = search(*root, key);
  if (z != NIL) {
    deleteNode(root, z);
  }
}

void inorder(Node* node) {
  if (node == NIL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  NIL->color = 'B';

  int values[7] = {10, 5, 15, 3, 7, 12, 20};
  Node* root = NIL;
  for (int i = 0; i < 7; i++) {
    insert(&root, values[i]);
  }
  inorder(root);
  printf("\n");

  int keys[5] = {3, 5, 15, 10, 7};
  for (int i = 0; i < 5; i++) {
    deleteValue(&root, keys[i]);
    inorder(root);
    printf("\n");
  }

  return 0;
}
