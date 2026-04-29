/* Source: https://www.geeksforgeeks.org/dsa/inorder-successor-in-binary-search-tree/ */
// C Program to find Inorder Successor 
// in Binary Search Tree 

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to find leftmost node in
// subtree with given root.
struct Node* leftMost(struct Node* node) {
    struct Node* curr = node;
    while (curr->left != NULL) 
        curr = curr->left;
    return curr;
}

struct Node* getSucc(struct Node* root, int target) {
    
    // Base Case 1: No Inorder Successor
    if (root == NULL)
        return NULL;
     
    // Base Case 2: root is same as target and 
    // right child is not empty
    if (root->data == target && root->right != NULL)
        return leftMost(root->right);

    // Use BST properties to search for 
    // target and successor
    struct Node* succ = NULL;
    struct Node* curr = root; 
    while (curr != NULL) {
      
        // If curr node is greater, then it
        // is a potential successor
        if (target < curr->data) {
            succ = curr;
            curr = curr->left;
        }
      
        // If smaller, then successor must
        // be in the right child
        else if (target >= curr->data) 
            curr = curr->right;
    }

    return succ;
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
  
    // Construct a BST
    //            20
    //          /    \
    //         8      22
    //       /   \
    //      4    12
    //          /  \
    //         10   14
    struct Node *root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);
  
    int target = 14;
    struct Node* succ = getSucc(root, target);
    if (succ != NULL)
        printf("%d", succ->data);
    else
        printf("null");
    return 0;
}
