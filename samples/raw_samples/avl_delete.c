#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
  int height;
} Node;

int height(Node* n) {
  if (n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}

int getBalance(Node* n) {
  if (n == NULL) return 0;
  return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* insert(Node* node, int data) {
  if (node == NULL) return createNode(data);

  if (data < node->data) {
    node->left = insert(node->left, data);
  } else if (data > node->data) {
    node->right = insert(node->right, data);
  } else {
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node* minValueNode(Node* node) {
  Node* current = node;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node* deleteNode(Node* root, int data) {
  if (root == NULL) return NULL;

  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == NULL) {
      Node* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node* temp = root->left;
      free(root);
      return temp;
    }
    Node* succ = minValueNode(root->right);
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {9, 5, 10, 0, 6, 11, -1};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  root = deleteNode(root, 10);

  inorder(root);
  printf("\n");

  return 0;
}
