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

Node* createNode(const char* id, const char* value) {
    trace_line(14);
    Node* n = (Node*)malloc(sizeof(Node));
    trace_line(15);
    strcpy(n->id, id);
    trace_line(16);
    strcpy(n->value, value);
    trace_line(17);
    n->left = NULL;
    trace_line(18);
    n->right = NULL;
    return n;
}

void inorder(Node* node) {
    trace_line(22);
    if (node == NULL) return;
    trace_line(23);
    inorder(node->left);
    trace_tree_highlight("T", node->id);
    trace_line(24);
    printf("%s ", node->value);
    trace_line(25);
    inorder(node->right);
}

int main() {
    trace_tree_init("T");

    trace_line(29);
    Node* R = createNode("R", "4");
    trace_tree_node("T", R->id, R->value);
    trace_line(30);
    Node* A = createNode("A", "2");
    trace_tree_node("T", A->id, A->value);
    trace_line(31);
    Node* B = createNode("B", "6");
    trace_tree_node("T", B->id, B->value);
    trace_line(32);
    Node* C = createNode("C", "1");
    trace_tree_node("T", C->id, C->value);
    trace_line(33);
    Node* D = createNode("D", "3");
    trace_tree_node("T", D->id, D->value);

    trace_line(35);
    R->left = A;
    trace_tree_edge("T", R->id, A->id);
    trace_line(36);
    R->right = B;
    trace_tree_edge("T", R->id, B->id);
    trace_line(37);
    A->left = C;
    trace_tree_edge("T", A->id, C->id);
    trace_line(38);
    A->right = D;
    trace_tree_edge("T", A->id, D->id);

    trace_line(40);
    inorder(R);
    trace_line(41);
    printf("\n");

    trace_line(43);
    return 0;
}
