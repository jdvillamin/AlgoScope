/* Source: https://www.geeksforgeeks.org/dsa/kth-largest-element-bst-using-constant-extra-space/ */
// C Program to find kth largest element
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to perform Morris Traversal and 
// return kth largest element
int kthLargest(struct Node* root, int k) {

    // return -1 if root is null
    if (root == NULL) return -1;

    struct Node* curr = root;
    int cnt = 0;

    while (curr != NULL) {

        // if right tree does not exist,
        // then increment the count, check 
        // count == k. Otherwise, 
        // set curr = curr->left
        if (curr->right == NULL) {
            cnt++;

            // return current Node
            // if cnt == k.
            if (cnt == k)
                return curr->data;

            curr = curr->left;
        } else {
            struct Node* succ = curr->right;

            // find the inorder successor
            while (succ->left != NULL && succ->left != curr) {
                succ = succ->left;
            }

            // create a linkage between pred and curr
            if (succ->left == NULL) {
                succ->left = curr;
                curr = curr->right;
            }

            // if succ->left = curr, it means 
            // we have processed the right subtree,
            // and we can process curr node
            else {
                cnt++;

                // remove the link
                succ->left = NULL;

                // return current Node
                // if cnt == k.
                if (cnt == k)
                    return curr->data;

                curr = curr->left;
            }
        }
    }

    return -1;
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

    // Create a hard-coded tree:
    //         20
    //       /   \
    //      8     22
    //    /  \
    //   4   12
    //      /  \
    //     10   14
    struct Node* root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);

    int k = 3;

    printf("%d\n", kthLargest(root, k));

    return 0;
}
