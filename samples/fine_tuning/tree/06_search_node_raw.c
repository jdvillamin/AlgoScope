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

int search(Node* node, const char* target) {
    if (node == NULL) return 0;
    if (strcmp(node->value, target) == 0) return 1;
    for (int i = 0; i < node->childCount; i++) {
        if (search(node->children[i], target)) return 1;
    }
    return 0;
}

int main() {
    Node* R = createNode("R", "R");
    Node* A = createNode("A", "A");
    Node* B = createNode("B", "B");
    Node* C = createNode("C", "C");
    Node* D = createNode("D", "D");

    addChild(R, A);
    addChild(R, B);
    addChild(A, C);
    addChild(B, D);

    if (search(R, "C")) {
        printf("found C\n");
    } else {
        printf("C not found\n");
    }

    return 0;
}
