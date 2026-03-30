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
    Node* R = createNode("R", "4");
    Node* A = createNode("A", "2");
    Node* B = createNode("B", "6");
    Node* C = createNode("C", "1");
    Node* D = createNode("D", "3");

    R->left = A;
    R->right = B;
    A->left = C;
    A->right = D;

    inorder(R);
    printf("\n");

    return 0;
}
