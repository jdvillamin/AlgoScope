/* Source: https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/ */
//Driver Code Starts
#include <stdio.h>

#define V 6
#define MAXQ 100

//Driver Code Ends

// BFS for a single connected component
void bfsConnected(int adj[V][V], int src, int visited[V], int res[V], int *resSize) {
    int q[MAXQ];
    int front = 0, rear = 0;
    visited[src] = 1;
    q[rear++] = src;

    while (front < rear) {
        int curr = q[front++];
        res[(*resSize)++] = curr;

        // visit all the unvisited
        // neighbours of current node
        for (int x = 0; x < V; x++) {
            if (adj[curr][x] && !visited[x]) {
                visited[x] = 1;
                q[rear++] = x;
            }
        }
    }
}

// BFS for all components (handles disconnected graphs)
void bfs(int adj[V][V], int res[V], int *resSize) {
    int visited[V] = {0};

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            bfsConnected(adj, i, visited, res, resSize);
    }
}

//Driver Code Starts

void addEdge(int adj[V][V], int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; 
}

int main() {
    int adj[V][V] = {0};

    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 0, 3);
    addEdge(adj, 4, 5);

    int res[V];
    int resSize = 0;

    bfs(adj, res, &resSize);

    for (int i = 0; i < resSize; i++)
        printf("%d ", res[i]);

    return 0;
}
//Driver Code Ends
