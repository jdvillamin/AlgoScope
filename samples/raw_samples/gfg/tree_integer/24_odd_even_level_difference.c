/* Source: https://www.geeksforgeeks.org/dsa/difference-between-sums-of-odd-and-even-levels/ */
// C program to find the difference between 
// sums of odd and even level in a Binary tree 
// using Recursion
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Helper function for getLevelDiff
void getLevelDiffHelper(struct Node* root, int level, 
                        int* oddSum, int* evenSum) {

    // Base case: If the node is NULL, return
    if (root == NULL) {
        return;
    }

    // Add to oddSum or evenSum based on the level
    if (level % 2 != 0) {
        *oddSum += root->data;
    }
    else {
        *evenSum += root->data;
    }

    // Recur for left and right children with 
    // incremented level
    getLevelDiffHelper(root->left, level + 1, 
                                 oddSum, evenSum);
  
    getLevelDiffHelper(root->right, level + 1, 
                                 oddSum, evenSum);
}

// Function to calculate the difference between
// sums of odd and even levels
int getLevelDiff(struct Node* root) {

    // Initialize sums for odd and even levels
    int oddSum = 0, evenSum = 0;

    // Start the recursion from level 1
    getLevelDiffHelper(root, 1, &oddSum, &evenSum);

    // Return the difference between odd
    // and even sums
    return oddSum - evenSum;
}

struct Node* createNode(int x) {
    struct Node* newNode = 
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {

    // Hardcoded input binary tree
    //       10
    //      /  \
    //     20   30
    //    /  \         
    //  40    60 
    struct Node* root = createNode(10);
    root->left = createNode(20);
    root->right = createNode(30);
    root->left->left = createNode(40);
    root->left->right = createNode(60);

    printf("%d\n", getLevelDiff(root));

    return 0;
}
