#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

typedef struct Node {
    char id[10];
    char value[10];
    struct Node* left;
    struct Node* right;
} Node;

int counter = 0;

Node* createNode(int val) {
    trace_line(15);
    Node* n = (Node*)malloc(sizeof(Node));
    trace_line(16);
    counter++;
    trace_line(17);
    sprintf(n->id, "n%d", counter);
    trace_line(18);
    sprintf(n->value, "%d", val);
    trace_line(19);
    n->left = NULL;
    trace_line(20);
    n->right = NULL;
    return n;
}

Node* insert(Node* root, int val) {
    trace_line(24);
    if (root == NULL) {
        Node* newNode = createNode(val);
        trace_tree_node("T", newNode->id, newNode->value);
        return newNode;
    }
    trace_line(25);
    if (val < atoi(root->value)) {
        trace_line(26);
        Node* oldLeft = root->left;
        root->left = insert(root->left, val);
        if (oldLeft == NULL) trace_tree_edge("T", root->id, root->left->id);
    } else {
        trace_line(28);
        Node* oldRight = root->right;
        root->right = insert(root->right, val);
        if (oldRight == NULL) trace_tree_edge("T", root->id, root->right->id);
    }
    trace_line(30);
    return root;
}

int search(Node* root, int val) {
    trace_line(34);
    if (root == NULL) return 0;
    trace_tree_highlight("T", root->id);
    trace_line(35);
    int nodeVal = atoi(root->value);
    trace_line(36);
    if (val == nodeVal) return 1;
    trace_line(37);
    if (val < nodeVal) return search(root->left, val);
    trace_line(38);
    return search(root->right, val);
}

int main() {
    trace_tree_init("T");

    trace_line(42);
    Node* root = NULL;

    trace_line(44);
    root = insert(root, 8);
    trace_line(45);
    root = insert(root, 3);
    trace_line(46);
    root = insert(root, 10);
    trace_line(47);
    root = insert(root, 1);
    trace_line(48);
    root = insert(root, 14);

    trace_line(50);
    if (search(root, 10)) {
        trace_line(51);
        printf("found 10\n");
    } else {
        trace_line(53);
        printf("10 not found\n");
    }

    trace_line(56);
    if (search(root, 5)) {
        trace_line(57);
        printf("found 5\n");
    } else {
        trace_line(59);
        printf("5 not found\n");
    }

    trace_line(62);
    return 0;
}
