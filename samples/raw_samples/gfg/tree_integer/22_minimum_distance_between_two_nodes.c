/* Source: https://www.geeksforgeeks.org/dsa/find-distance-between-two-nodes-of-a-binary-tree/ */
// C Program to Find distance between two
// nodes of a Binary Tree

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Function to find the level of a node
int findLevel(struct Node *root, int k, int level) {
    if (root == NULL)
        return -1;
    if (root->data == k)
        return level;

    // Recursively call function on left child
    int leftLevel = findLevel(root->left, k, level + 1);

    // If node is found on left, return level
    // Else continue searching on the right child
    if (leftLevel != -1) {
        return leftLevel;
    }
    else {
        return findLevel(root->right, k, level + 1);
    }
}

// Function to find the lowest common ancestor
// and calculate distance between two nodes
struct Node *findLcaAndDistance(struct Node *root, int a, int b,
                                int *d1, int *d2, int *dist, int lvl) {
    if (root == NULL)
        return NULL;

    if (root->data == a) {

        // If first node found, store level and
        // return the node
        *d1 = lvl;
        return root;
    }
    if (root->data == b) {

        // If second node found, store level and
        // return the node
        *d2 = lvl;
        return root;
    }

    // Recursively call function on left child
    struct Node *left = findLcaAndDistance
      					(root->left, a, b, d1, d2, dist, lvl + 1);

    // Recursively call function on right child
    struct Node *right = findLcaAndDistance
      					(root->right, a, b, d1, d2, dist, lvl + 1);

    if (left != NULL && right != NULL) {

        // If both nodes are found in different
        // subtrees, calculate the distance
        *dist = *d1 + *d2 - 2 * lvl;
    }

    // Return node found or NULL if not found
    if (left != NULL) {
        return left;
    }
    else {
        return right;
    }
}

// Function to find distance between two nodes
int findDist(struct Node *root, int a, int b) {
    int d1 = -1, d2 = -1, dist;

    // Find lowest common ancestor and calculate distance
    struct Node *lca = findLcaAndDistance(root, a, b, &d1, &d2, &dist, 1);

    if (d1 != -1 && d2 != -1) {

        // Return the distance if both nodes 
       // are found
        return dist;
    }

    if (d1 != -1) {

        // If only first node is found, find
        // distance to second node
        dist = findLevel(lca, b, 0);
        return dist;
    }

    if (d2 != -1) {

        // If only second node is found, find
        // distance to first node
        dist = findLevel(lca, a, 0);
        return dist;
    }

    // Return -1 if both nodes not found
    return -1;
}

struct Node* createNode(int value) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

int main() {

    // Hardcoded binary tree
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7

    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int a = 4, b = 7;
    printf("%d\n", findDist(root, a, b));

    return 0;
}
