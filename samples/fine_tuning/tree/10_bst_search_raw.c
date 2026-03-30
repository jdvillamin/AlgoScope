#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char id[10];
    char value[10];
    struct Node* left;
    struct Node* right;
} Node;

int counter = 0;

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n->id, "n%d", counter);
    sprintf(n->value, "%d", val);
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node* root, int val) {
    if (root == NULL) return createNode(val);
    if (val < atoi(root->value)) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

int search(Node* root, int val) {
    if (root == NULL) return 0;
    int nodeVal = atoi(root->value);
    if (val == nodeVal) return 1;
    if (val < nodeVal) return search(root->left, val);
    return search(root->right, val);
}

int main() {
    Node* root = NULL;

    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 14);

    if (search(root, 10)) {
        printf("found 10\n");
    } else {
        printf("10 not found\n");
    }

    if (search(root, 5)) {
        printf("found 5\n");
    } else {
        printf("5 not found\n");
    }

    return 0;
}
