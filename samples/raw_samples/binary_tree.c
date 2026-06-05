#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* left;
  struct Node* right;
} Node;

Node* createNode(const char* id, const char* value) {
  Node* n = (Node*)malloc(sizeof(Node));
  strcpy(n->id, id);
  strcpy(n->value, value);
  n->left = NULL;
  n->right = NULL;
  return n;
}

void inorder(Node* node) {
  if (node == NULL) return;
  inorder(node->left);
  printf("%s ", node->value);
  inorder(node->right);
}

int main() {
  // Build a binary search tree
  Node* n50 = createNode("n50", "50");
  Node* n30 = createNode("n30", "30");
  Node* n70 = createNode("n70", "70");
  Node* n20 = createNode("n20", "20");
  Node* n40 = createNode("n40", "40");
  Node* n60 = createNode("n60", "60");
  Node* n80 = createNode("n80", "80");

  n50->left = n30;
  n50->right = n70;
  n30->left = n20;
  n30->right = n40;
  n70->left = n60;
  n70->right = n80;

  inorder(n50);
  printf("\n");

  return 0;
}
