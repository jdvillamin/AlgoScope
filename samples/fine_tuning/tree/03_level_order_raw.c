#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define QUEUE_SIZE 50

typedef struct Node {
    char id[10];
    char value[10];
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

Node* createNode(const char* id, const char* value) {
    Node* n = (Node*)malloc(sizeof(Node));
    strcpy(n->id, id);
    strcpy(n->value, value);
    n->childCount = 0;
    return n;
}

void addChild(Node* parent, Node* child) {
    parent->children[parent->childCount++] = child;
}

int main() {
    Node* R = createNode("R", "R");
    Node* A = createNode("A", "A");
    Node* B = createNode("B", "B");
    Node* C = createNode("C", "C");
    Node* D = createNode("D", "D");
    Node* E = createNode("E", "E");

    addChild(R, A);
    addChild(R, B);
    addChild(A, C);
    addChild(A, D);
    addChild(B, E);

    Node* queue[QUEUE_SIZE];
    int front = 0;
    int rear = 0;
    queue[rear++] = R;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%s ", current->value);
        for (int i = 0; i < current->childCount; i++) {
            queue[rear++] = current->children[i];
        }
    }
    printf("\n");

    return 0;
}
