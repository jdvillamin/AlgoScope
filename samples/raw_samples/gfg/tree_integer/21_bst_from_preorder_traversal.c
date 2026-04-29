/* Source: https://www.geeksforgeeks.org/dsa/construct-bst-from-given-preorder-traversa/ */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Static index to keep track of position in the preorder array
static int idx;

// A recursive function to construct BST from pre[].
// idx is used to keep track of index in pre[].
struct Node* constructUtil(int pre[], int min,
                           int max, int n) {
    if (idx >= n)
        return NULL;

    int key = pre[idx];
    if (key <= min || key >= max)
        return NULL;

    // If current element of pre[] is in range,
    // then only it is part of the current subtree
    struct Node* root = newNode(key);
    idx++;

    // All nodes in range {min .. key}
    // go to the left subtree
    root->left = constructUtil(pre, min, key, n);

    // All nodes in range {key .. max} 
    // go to the right subtree
    root->right = constructUtil(pre, key, max, n);

    return root;
}

// The main function to construct BST from
// given preorder traversal
struct Node* constructTree(int pre[], int n) {
    idx = 0;  // Reset the static index
              // before starting construction
    return constructUtil(pre, INT_MIN, INT_MAX, n);
}

// A utility function to print inorder 
void inorder(struct Node* node) {
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Driver code
int main() {
    int pre[] = {10, 5, 1, 7, 40, 50};
    int n = sizeof(pre) / sizeof(pre[0]);

    struct Node* root = constructTree(pre, n);
    inorder(root);
    printf("\n");

    return 0;
}
