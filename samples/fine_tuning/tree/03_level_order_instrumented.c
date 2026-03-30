#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

#define MAX_CHILDREN 10
#define QUEUE_SIZE 50

typedef struct Node {
    char id[10];
    char value[10];
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
    trace_line(17);
    Node* n = (Node*)malloc(sizeof(Node));
    trace_line(18);
    strcpy(n->id, id);
    trace_line(19);
    strcpy(n->value, value);
    trace_line(20);
    n->childCount = 0;
    return n;
}

void addChild(Node* parent, Node* child) {
    trace_line(25);
    parent->children[parent->childCount++] = child;
}

int main() {
    trace_tree_init("T");

    trace_line(29);
    Node* R = createNode("R", "R");
    trace_tree_node("T", R->id, R->value);
    trace_line(30);
    Node* A = createNode("A", "A");
    trace_tree_node("T", A->id, A->value);
    trace_line(31);
    Node* B = createNode("B", "B");
    trace_tree_node("T", B->id, B->value);
    trace_line(32);
    Node* C = createNode("C", "C");
    trace_tree_node("T", C->id, C->value);
    trace_line(33);
    Node* D = createNode("D", "D");
    trace_tree_node("T", D->id, D->value);
    trace_line(34);
    Node* E = createNode("E", "E");
    trace_tree_node("T", E->id, E->value);

    trace_line(36);
    addChild(R, A);
    trace_tree_edge("T", R->id, A->id);
    trace_line(37);
    addChild(R, B);
    trace_tree_edge("T", R->id, B->id);
    trace_line(38);
    addChild(A, C);
    trace_tree_edge("T", A->id, C->id);
    trace_line(39);
    addChild(A, D);
    trace_tree_edge("T", A->id, D->id);
    trace_line(40);
    addChild(B, E);
    trace_tree_edge("T", B->id, E->id);

    Node* queue[QUEUE_SIZE];
    trace_line(43);
    int front = 0;
    trace_line(44);
    int rear = 0;
    trace_line(45);
    queue[rear++] = R;

    trace_line(47);
    while (front < rear) {
        trace_line(47);
        trace_line(48);
        Node* current = queue[front++];
        trace_tree_highlight("T", current->id);
        trace_line(49);
        printf("%s ", current->value);
        trace_line(50);
        for (int i = 0; i < current->childCount; i++) {
            trace_line(50);
            trace_line(51);
            queue[rear++] = current->children[i];
        }
    }
    trace_line(54);
    printf("\n");

    trace_line(56);
    return 0;
}
