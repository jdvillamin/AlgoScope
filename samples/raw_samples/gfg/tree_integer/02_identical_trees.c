/* Source: https://www.geeksforgeeks.org/dsa/write-c-code-to-determine-if-two-trees-are-identical/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} 

// Queue node for level order traversal
struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
}

// Queue structure
struct Queue {
    QueueNode* front;
    QueueNode* rear;
} 

// Create a new tree node
Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Queue functions
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (isEmpty(q))
        return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

bool isIdentical(Node* r1, Node* r2) {
    if (r1 == NULL && r2 == NULL)
        return true;

    if (r1 == NULL || r2 == NULL)
        return false;

    // Use two queues for level order traversal
    Queue* q1 = createQueue();
    Queue* q2 = createQueue();
    enqueue(q1, r1);
    enqueue(q2, r2);

    while (!isEmpty(q1) && !isEmpty(q2)) {
        Node* node1 = dequeue(q1);
        Node* node2 = dequeue(q2);

        // Check if the current nodes are identical
        if (node1->data != node2->data)
            return false;

        // Check left children
        if (node1->left && node2->left) {
            enqueue(q1, node1->left);
            enqueue(q2, node2->left);
        } else if (node1->left || node2->left) {
            return false;
        }

        // Check right children
        if (node1->right && node2->right) {
            enqueue(q1, node1->right);
            enqueue(q2, node2->right);
        } else if (node1->right || node2->right) {
            return false;
        }
    }
    // If both queues are empty, the trees are identical
    return isEmpty(q1) && isEmpty(q2);
}

int main() {
    // Representation of input binary tree 1
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    Node* r1 = newNode(1);
    r1->left = newNode(2);
    r1->right = newNode(3);
    r1->left->left = newNode(4);

    // Representation of input binary tree 2
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    Node* r2 = newNode(1);
    r2->left = newNode(2);
    r2->right = newNode(3);
    r2->left->left = newNode(4);

    if (isIdentical(r1, r2))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}
