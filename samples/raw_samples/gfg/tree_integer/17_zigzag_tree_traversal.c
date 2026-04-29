/* Source: https://www.geeksforgeeks.org/dsa/zigzag-tree-traversal/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Finding the Tree Height
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;
    int lHeight = treeHeight(root->left);
    int rHeight = treeHeight(root->right);
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

// Function to traverse from left to right traversal at a certain level
void leftToRightTrav(struct Node* root, int level, int* res, int* index) {
    if (root == NULL) return;

    if (level == 1) {
        res[(*index)++] = root->data;
    } else {
        leftToRightTrav(root->left, level - 1, res, index);
        leftToRightTrav(root->right, level - 1, res, index);
    }
}

// Function to traverse from right to left traversal at a certain level
void rightToLeftTrav(struct Node* root, int level, int* res, int* index) {
    if (root == NULL) return;

    if (level == 1) {
        res[(*index)++] = root->data;
    } else {
        rightToLeftTrav(root->right, level - 1, res, index);
        rightToLeftTrav(root->left, level - 1, res, index);
    }
}

// Function to traverse the tree in zigzag order
void zigZagTraversal(struct Node* root, int* res, int* size) {
    bool leftToRight = true;
    int height = treeHeight(root);
    int index = 0;

    for (int i = 1; i <= height; i++) {
        if (leftToRight)
            leftToRightTrav(root, i, res, &index);
        else
            rightToLeftTrav(root, i, res, &index);

        leftToRight = !leftToRight;
    }
  
  	// Set the size of the result
    *size = index; 
}

struct Node* createNode(int val) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

int main() {
  
    // Create a input binary tree
    //         20
    //       /   \
    //      8     22
    //    /  \     \
    //   4   12    11
    //      /  \
    //     10   14
    struct Node* root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->right->right = createNode(11);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);
	
  	// Array to hold zigzag traversal results
    int res[200]; 
    int size = 0;

    zigZagTraversal(root, res, &size);

    for (int i = 0; i < size; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}
