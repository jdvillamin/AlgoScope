/* Source: https://www.geeksforgeeks.org/dsa/lowest-common-ancestor-binary-tree-set-1/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

// Finds the path from root to given node
bool findPath(struct Node* root, struct Node** path, int* pathLen, struct Node* n) {
    if (root == NULL) return false;

    // Store current node
    path[(*pathLen)++] = root;

    if (root == n || findPath(root->left, path, pathLen, n) || findPath(root->right, path, pathLen, n))
        return true;

    // remove root from path and return false
    (*pathLen)--;
    return false;
}

struct Node* lca(struct Node* root, struct Node* n1, struct Node* n2) {
    struct Node* path1[100]; int len1 = 0;
    struct Node* path2[100]; int len2 = 0;

    // Find paths from root to n1
    // and root to n2.
    if (!findPath(root, path1, &len1, n1) || !findPath(root, path2, &len2, n2))
        return NULL;

    // Compare the paths to get the first
    // different value
    int i = 0;
    for (i = 0; i < len1 && i < len2; i++) {
        if (path1[i] != path2[i]) return path1[i-1];
    }
    return path1[i-1];
}

int main() {
    // Create binary tree:
    //			   1
    //           /   \
    //          2     3
    //               / \
    //              6   7
    //             /
    //            8

    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->left->left = newNode(8);

    struct Node* n1 = root->right->right;
    struct Node* n2 = root->right->left->left;

    struct Node* ans = lca(root, n1, n2);
    if (ans != NULL)
        printf("%d\n", ans->data);
}
