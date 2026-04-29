/* Source: https://www.geeksforgeeks.org/dsa/find-maximum-path-sum-two-leaves-binary-tree/ */
// C++ program to find maximum path 
//sum between two leaves of  a binary tree

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// mxPathSum function to calculate maximum path
// sum between two leaves and maximum sum from node 
// to leaf in a single traversal
int mxPathSum(struct Node* root, int* maxPathSum) {
  
    // Base case: If the node is null, 
  	// return 0
    if (root == NULL) {
        return 0;
    }

    // Recursively calculate the maximum sum 
  	// from node to leaf for left and right subtrees
    int mxLeft = mxPathSum(root->left, maxPathSum);
    int mxRight = mxPathSum(root->right, maxPathSum);

    // If both left and right children exist, 
  	// update maxPathSum
    if (root->left != NULL && root->right != NULL) {
      
        // This is the sum of the left path,
      	// right path, and the node's data
        int maxSumPathViaNode = mxLeft + mxRight + root->data;
        
        // Update the maximum sum path between two leaves
        if (maxSumPathViaNode > *maxPathSum) {
            *maxPathSum = maxSumPathViaNode;
        }

        // Return the maximum sum from the current 
      	// node to a leaf
        return root->data + 
        (mxLeft > mxRight ? mxLeft : mxRight);
    }

    // If only one child exists, return the sum
  	// from the node to leaf
    return root->data + (root->left ? mxLeft : mxRight);
}

// Function to return the maximum path 
// sum between any two leaves in the binary tree
int findMaxSum(struct Node* root) {
  
    // Edge case: If the tree is empty,
  	// return 0
    if (root == NULL) {
        return 0;
    }

    int maxPathSum = INT_MIN;
    
    // Call the helper function to compute
  	// the result
    mxPathSum(root, &maxPathSum);
    
    return maxPathSum;
}

struct Node* createNode(int x) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
  
    // Construct a sample binary tree
    //
    //         1
    //       /   \
    //     -2     3
    //     / \   / \
    //    8  -1  4  -5
    
    struct Node* root = createNode(1);
    root->left = createNode(-2);
    root->right = createNode(3);
    root->left->left = createNode(8);
    root->left->right = createNode(-1);
    root->right->left = createNode(4);
    root->right->right = createNode(-5);

    int result = findMaxSum(root);
    printf("%d\n", result); 

    return 0;
}
