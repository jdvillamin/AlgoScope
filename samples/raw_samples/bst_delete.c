#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(int data) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}

Node* insert(Node* root, int data) {
  if (root == NULL) {
    return createNode(data);
  }
  if (data < root->data) {
    root->left = insert(root->left, data);
  } else {
    root->right = insert(root->right, data);
  }
  return root;
}

Node* findMin(Node* node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
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
    Node* succ = findMin(root->right);
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
  }
  return root;
}

int main() {
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  root = deleteNode(root, 20);
  root = deleteNode(root, 30);
  root = deleteNode(root, 50);

  return 0;
}
