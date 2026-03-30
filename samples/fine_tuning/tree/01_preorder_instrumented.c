#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

#define MAX_CHILDREN 10

typedef struct Node {
    char id[10];
    char value[10];
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
    trace_line(16);
    Node* n = (Node*)malloc(sizeof(Node));
    trace_line(17);
    strcpy(n->id, id);
    trace_line(18);
    strcpy(n->value, value);
    trace_line(19);
    n->childCount = 0;
    return n;
}

void addChild(Node* parent, Node* child) {
    trace_line(24);
    parent->children[parent->childCount++] = child;
}

void preorder(Node* node) {
    trace_line(28);
    if (node == NULL) return;
    trace_tree_highlight("T", node->id);
    trace_line(29);
    printf("%s ", node->value);
    trace_line(30);
    for (int i = 0; i < node->childCount; i++) {
        trace_line(30);
        trace_line(31);
        preorder(node->children[i]);
    }
}

int main() {
    trace_tree_init("T");

    trace_line(35);
    Node* R = createNode("R", "R");
    trace_tree_node("T", R->id, R->value);
    trace_line(36);
    Node* A = createNode("A", "A");
    trace_tree_node("T", A->id, A->value);
    trace_line(37);
    Node* B = createNode("B", "B");
    trace_tree_node("T", B->id, B->value);
    trace_line(38);
    Node* C = createNode("C", "C");
    trace_tree_node("T", C->id, C->value);
    trace_line(39);
    Node* D = createNode("D", "D");
    trace_tree_node("T", D->id, D->value);

    trace_line(41);
    addChild(R, A);
    trace_tree_edge("T", R->id, A->id);
    trace_line(42);
    addChild(R, B);
    trace_tree_edge("T", R->id, B->id);
    trace_line(43);
    addChild(A, C);
    trace_tree_edge("T", A->id, C->id);
    trace_line(44);
    addChild(A, D);
    trace_tree_edge("T", A->id, D->id);

    trace_line(46);
    preorder(R);
    trace_line(47);
    printf("\n");

    trace_line(49);
    return 0;
}
