/* Source: https://www.geeksforgeeks.org/dsa/minimum-number-of-squares-whose-sum-equals-to-given-number-n/ */
//Driver Code Starts
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Pair {
    int node;
    int steps;
};

struct Queue {
    struct Pair* arr;
    int front, rear, size, capacity;
};

struct Queue* createQueue(int capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = q->rear = q->size = 0;
    q->arr = (struct Pair*)malloc(capacity * sizeof(struct Pair));
    return q;
}

void enqueue(struct Queue* q, struct Pair val) {
    q->arr[q->rear++] = val;
    q->size++;
}

struct Pair dequeue(struct Queue* q) {
    return q->arr[q->front++];
}

int isEmpty(struct Queue* q) {
    return q->size == 0;
}

//Driver Code Ends

int minSquares(int n) {
  
    // Creating visited array of size n + 1
    bool* vis = (bool*)calloc(n + 1, sizeof(bool));
  
    // Queue of pair to store number and count
    // of steps to reach that number from n by 
    // subtacting a square in each step
    struct Queue* q = createQueue(n * n + 1);
  
    // Push initial number
    enqueue(q, (struct Pair){n, 0});
  
    // Mark starting node visited
    vis[n] = true;

    while (!isEmpty(q)) {
        struct Pair p = dequeue(q);
        int node = p.node;
        int steps = p.steps;
     
        if (node == 0)
            return steps;
      
        // Loop for all possible path 
        // from 1 to i*i <= current node
        for (int i = 1; i * i <= node; i++) {
          
            int next = node - (i * i);
            if (!vis[next]) {
              
                // Mark visited
                vis[next] = true;
              
                // Push it it Queue
                enqueue(q, (struct Pair){next, steps + 1});
            }
        }
    }
    return -1;
}

//Driver Code Starts

int main() {
    int n = 6;
    printf("%d", minSquares(n));
    return 0;
}

//Driver Code Ends
