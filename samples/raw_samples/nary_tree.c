#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10

typedef struct Node {
  char id[10];
  char value[10];
  struct Node* children[MAX_CHILDREN];
  int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
  Node* n = (Node*)malloc(sizeof(Node));
  strcpy(n->id, id);
  strcpy(n->value, value);
  n->childCount = 0;
  return n;
}

void addChild(Node* parent, Node* child) {
  parent->children[parent->childCount++] = child;
}

void preorder(Node* node) {
  if (node == NULL) return;
  printf("%s ", node->value);
  for (int i = 0; i < node->childCount; i++) {
    preorder(node->children[i]);
  }
}

int main() {
  // ================= BUILD TREE =================
  Node* R = createNode("R", "R");

  Node* n1 = createNode("n1", "1");
  Node* n2 = createNode("n2", "2");
  Node* n3 = createNode("n3", "3");
  addChild(R, n1);
  addChild(R, n2);
  addChild(R, n3);

  Node* n4 = createNode("n4", "4");
  Node* n5 = createNode("n5", "5");
  addChild(n1, n4);
  addChild(n1, n5);

  Node* n6 = createNode("n6", "6");
  addChild(n2, n6);

  Node* n7 = createNode("n7", "7");
  Node* n8 = createNode("n8", "8");
  addChild(n3, n7);
  addChild(n3, n8);

  Node* n9 = createNode("n9", "9");
  addChild(n4, n9);

  // ================= PREORDER TRAVERSAL =================
  preorder(R);
  printf("\n");

  return 0;
}
