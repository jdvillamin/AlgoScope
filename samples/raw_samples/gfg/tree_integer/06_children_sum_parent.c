/* Source: https://www.geeksforgeeks.org/dsa/check-for-children-sum-property-in-a-binary-tree/ */
// C Program to check children sum property
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// returns 1 if children sum property holds
// for the given node and both of its children
int isSumProperty(struct Node* root) {

    // If root is NULL or it's a leaf node
    // then return true
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 1;

    int sum = 0;

    // If left child is not present then 0
    // is used as data of left child
    if (root->left != NULL)
        sum += root->left->data;

    // If right child is not present then 0
    // is used as data of right child
    if (root->right != NULL)
        sum += root->right->data;

    // if the node and both of its children
    // satisfy the property return 1 else 0
    return ((root->data == sum)
            && isSumProperty(root->left)
            && isSumProperty(root->right));
}

struct Node* createNode(int x) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {

    // Create a hard coded tree.
    //         35
    //       /   \
    //      20    15
    //     /  \  /  \
    //   15   5 10   5
    struct Node* root = createNode(35);
    root->left = createNode(20);
    root->right = createNode(15);
    root->left->left = createNode(15);
    root->left->right = createNode(5);
    root->right->left = createNode(10);
    root->right->right = createNode(5);

    printf("%d\n", isSumProperty(root));
    return 0;
}
