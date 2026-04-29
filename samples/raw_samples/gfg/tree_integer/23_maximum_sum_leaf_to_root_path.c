/* Source: https://www.geeksforgeeks.org/dsa/find-the-maximum-sum-path-in-a-binary-tree/ */
// C program to find maximum sum leaf to
// root path in Binary Tree
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Helper function to find the leaf node that contributes 
// to the maximum sum and returns the maximum sum from the
// root to that leaf
void findMaxSum(struct Node* root, int currSum, int* mxSum) {
    if (root == NULL)
        return;

    // Add the current node's data to the path sum
    currSum += root->data;

    // Check if this node is a leaf node
    if (root->left == NULL && root->right == NULL) {
        
        // Update the maximum sum if a higher sum is found
        if (currSum > *mxSum) {
            *mxSum = currSum;
        }
    }

    // Recursively check for the maximum 
  	// sum in the left and right subtrees
    findMaxSum(root->left, currSum, mxSum);
    findMaxSum(root->right, currSum, mxSum);
}

// Function to return the maximum sum path from root to leaf
int maxPathSum(struct Node* root) {

    // Empty tree has sum 0
    if (root == NULL)
        return 0;

    // Initialize max sum as the smallest possible integer
    int mxSum = INT_MIN;

    // Find the target leaf and maximum sum
    findMaxSum(root, 0, &mxSum);

    // Return the maximum sum found
    return mxSum;
}

struct Node* createNode(int data) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
  
    // Constructing tree:
    //           10
    //         /    \
    //       -2      7
    //      /  \
    //     8   -4
  
    struct Node* root = createNode(10);
    root->left = createNode(-2);
    root->right = createNode(7);
    root->left->left = createNode(8);
    root->left->right = createNode(-4);

    int sum = maxPathSum(root);
    printf("%d\n", sum);

    return 0;
}
