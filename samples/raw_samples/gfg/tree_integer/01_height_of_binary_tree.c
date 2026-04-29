/* Source: https://www.geeksforgeeks.org/dsa/find-the-maximum-depth-or-height-of-a-tree/ */
#include <stdio.h>
#include <stdlib.h>

// Node Structure
struct Node {
    int data;
    struct Node *left, *right;
} 

// Function to create a new node
Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Queue structure
struct Queue {
    Node** arr;
    int front, rear, size, capacity;
} 

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->arr = (Node**)malloc(capacity * sizeof(Node*));
    return q;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, Node* node) {
    if (q->size == q->capacity) return;
    q->arr[q->rear] = node;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    Node* node = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return node;
}

int height(Node* root) {
    if (!root) return 0;

    // Initializing a queue to traverse
    // the tree level by level
    Queue* q = createQueue(100); 
    enqueue(q, root);
    int depth = 0;

    // Loop until the queue is empty
    while (!isEmpty(q)) {
        int levelSize = q->size;

        // Traverse all nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            Node* curr = dequeue(q);
            
            // enqueue their child nodes 
            if (curr->left) enqueue(q, curr->left);
            if (curr->right) enqueue(q, curr->right);
        }

        // Increment depth after traversing each level
        depth++;
    }
    return depth - 1;
}

int main() {
  
    // Representation of the input tree:
    //     12
    //    /  \
    //   8   18
    //  / \
    // 5   11
    Node *root = newNode(12);
    root->left = newNode(8);
    root->right = newNode(18);
    root->left->left = newNode(5);
    root->left->right = newNode(11);
    
    printf("%d", height(root));
    
    return 0;
}
