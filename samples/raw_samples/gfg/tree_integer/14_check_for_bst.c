/* Source: https://www.geeksforgeeks.org/dsa/a-program-to-check-if-a-binary-tree-is-bst-or-not/ */
//Driver Code Starts
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
//Driver Code Ends

};

// Function to check if the binary tree 
// is a BST using Morris Traversal
int isBST(struct Node* root) {
    struct Node* curr = root;
    struct Node* pre;
    int prevValue = INT_MIN; 

    while (curr != NULL) {
        if (curr->left == NULL) {
            if (curr->data <= prevValue) {
              
                // Not in ascending order
                return 0; 
            }
            prevValue = curr->data;
            curr = curr->right;
        } else {
          
            // Find the inorder predecessor of curr
            pre = curr->left;
            while (pre->right != NULL && pre->right != curr) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
              
                // Create a temporary 
                // thread to the curr node
                pre->right = curr;
                curr = curr->left;
            } else {
                pre->right = NULL;
                if (curr->data <= prevValue) {
                  
                    // Not in ascending order
                    return 0; 
                }
                prevValue = curr->data;
                curr = curr->right;
            }
        }
    }

    return 1; 
}

//Driver Code Starts

struct Node* createNode(int value) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
  
    // Create a sample binary tree
    //     10
    //    /  \
    //   5    20
    //        / \
    //       9   25

    struct Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->right->left = createNode(9);
    root->right->right = createNode(25);

    if (isBST(root)) 
        printf("true");
    else 
         printf("false");
    
    return 0;
}

//Driver Code Ends
