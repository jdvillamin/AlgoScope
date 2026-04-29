/* Source: https://www.geeksforgeeks.org/dsa/diameter-of-a-binary-tree/ */
#include <stdio.h>
#include <stdlib.h>

// Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to compute the height of a tree.
int height(struct Node* root) {
    
    if (root == NULL)
        return 0;

    // If tree is not empty then height = 1 + max of left height and right heights
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + 
    (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to get diameter of a binary tree
int diameter(struct Node* root) {
    if (root == NULL)
        return 0;

    // Get the height of left and right sub-trees
    int lheight = height(root->left);
    int rheight = height(root->right);

    // Get the diameter of left and right sub-trees
    int ldiameter = diameter(root->left);
    int rdiameter = diameter(root->right);
    
    // Diameter of current subtree 
    int curr = lheight+rheight;

    if (ldiameter > rdiameter && ldiameter > curr)
        return ldiameter;
    else if (rdiameter > ldiameter && rdiameter > curr) 
        return rdiameter;
    return curr;
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
    
    struct Node* root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);
    root->right->right = createNode(4);
  	root->right->left->left = createNode(5);
  	root->right->right->right = createNode(6);
    printf("%d\n", diameter(root));

    return 0;
}
