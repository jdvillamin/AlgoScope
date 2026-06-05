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

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%d ", node->data);
  inorder(node->right);
}

int main() {
  int values[7] = {50, 30, 70, 20, 40, 60, 80};

  Node* root = NULL;
  for (int i = 0; i < 7; i++) {
    root = insert(root, values[i]);
  }

  inorder(root);
  printf("\n");

  return 0;
}
