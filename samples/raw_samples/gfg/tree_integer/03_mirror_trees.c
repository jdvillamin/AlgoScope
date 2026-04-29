/* Source: https://www.geeksforgeeks.org/dsa/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/ */
#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// helper struct to store {node, start, end}
struct Data {
    struct Node* node;
    int start;
    int end;
};

// queue element for Node + level
struct QueueNode {
    struct Node* node;
    int level;
    struct QueueNode* next;
};

// queue for Data
struct DataQueueNode {
    struct Data data;
    struct DataQueueNode* next;
};

// -------- Queue for levelOrder --------
struct QueueNode* createQueueNode(struct Node* node, int level) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->node = node;
    temp->level = level;
    temp->next = NULL;
    return temp;
}

void enqueue(struct QueueNode** front, struct QueueNode** rear, struct Node* node, int level) {
    struct QueueNode* temp = createQueueNode(node, level);
    if (*rear == NULL) {
        *front = *rear = temp;
        return;
    }
    (*rear)->next = temp;
    *rear = temp;
}

struct QueueNode* dequeue(struct QueueNode** front, struct QueueNode** rear) {
    if (*front == NULL) return NULL;
    struct QueueNode* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) *rear = NULL;
    return temp;
}

int isQueueEmpty(struct QueueNode* front) {
    return front == NULL;
}

// -------- Queue for Data --------
struct DataQueueNode* createDataNode(struct Data d) {
    struct DataQueueNode* temp = (struct DataQueueNode*)malloc(sizeof(struct DataQueueNode));
    temp->data = d;
    temp->next = NULL;
    return temp;
}

void enqueueData(struct DataQueueNode** front, struct DataQueueNode** rear, struct Data d) {
    struct DataQueueNode* temp = createDataNode(d);
    if (*rear == NULL) {
        *front = *rear = temp;
        return;
    }
    (*rear)->next = temp;
    *rear = temp;
}

struct Data dequeueData(struct DataQueueNode** front, struct DataQueueNode** rear) {
    struct DataQueueNode* temp = *front;
    struct Data d = temp->data;
    *front = (*front)->next;
    if (*front == NULL) *rear = NULL;
    free(temp);
    return d;
}

int isDataQueueEmpty(struct DataQueueNode* front) {
    return front == NULL;
}

// -------- Node and Tree functions --------
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int getHeight(struct Node* root, int h) {
    if (root == NULL) return h - 1;
    int left = getHeight(root->left, h + 1);
    int right = getHeight(root->right, h + 1);
    return (left > right) ? left : right;
}

void levelOrder(struct Node* root) {
    struct QueueNode* front = NULL;
    struct QueueNode* rear = NULL;

    enqueue(&front, &rear, root, 0);

    int lastLevel = 0;

    // function to get the height of tree
    int height = getHeight(root, 0);

    // printing the level order of tree
    while (!isQueueEmpty(front)) {
        struct QueueNode* top = dequeue(&front, &rear);

        struct Node* node = top->node;
        int lvl = top->level;
        free(top);

        if (lvl > lastLevel) {
            printf("\n");
            lastLevel = lvl;
        }

        // all levels are printed
        if (lvl > height) break;

        if (node->data != -1) printf("%d ", node->data);
        
        // printing null node
        else printf("%s ", "N");

        // null node has no children
        if (node->data == -1) continue;

        if (node->left == NULL)
            enqueue(&front, &rear, newNode(-1), lvl + 1);
        else
            enqueue(&front, &rear, node->left, lvl + 1);

        if (node->right == NULL)
            enqueue(&front, &rear, newNode(-1), lvl + 1);
        else
            enqueue(&front, &rear, node->right, lvl + 1);
    }
}

struct Node* sortedArrayToBST(int arr[], int n) {
    if (n == 0) return NULL;

    // create the root node.
    int mid = (n - 1) / 2;
    struct Node* root = newNode(arr[mid]);

    struct DataQueueNode* front = NULL;
    struct DataQueueNode* rear = NULL;

    struct Data d = {root, 0, n - 1};
    enqueueData(&front, &rear, d);

    while (!isDataQueueEmpty(front)) {
        struct Data currData = dequeueData(&front, &rear);

        struct Node* curr = currData.node;
        int st = currData.start, en = currData.end;
        mid = (st + en) / 2;

        // if left subtree exists
        if (st < mid) {
            int leftVal = (st + mid - 1) / 2;
            struct Node* left = newNode(arr[leftVal]);
            curr->left = left;
            struct Data newD = {left, st, mid - 1};
            enqueueData(&front, &rear, newD);
        }

        // if right subtree exists
        if (en > mid) {
            int rightVal = (mid + 1 + en) / 2;
            struct Node* right = newNode(arr[rightVal]);
            curr->right = right;
            struct Data newD = {right, mid + 1, en};
            enqueueData(&front, &rear, newD);
        }
    }

    return root;
}

int main() {
    int arr[] = {1, 5, 9, 14, 23, 27};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = sortedArrayToBST(arr, n);
    levelOrder(root);

    return 0;
}
