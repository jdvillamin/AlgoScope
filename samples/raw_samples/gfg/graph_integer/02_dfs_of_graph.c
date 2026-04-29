/* Source: https://www.geeksforgeeks.org/dsa/depth-first-search-or-dfs-for-a-graph/ */
//Driver Code Starts
#include <stdio.h>

#define V 6

//Driver Code Ends

void dfsRec(int adj[V][V], int visited[V], int s, int res[V], int *idx) {
    
    visited[s] = 1;

    res[(*idx)++] = s;

    // Recursively visit all adjacent 
    // vertices that are not visited yet
    for (int i = 0; i < V; i++)
        if (adj[s][i] && visited[i] == 0)
            dfsRec(adj, visited, i, res, idx);
}

void dfs(int adj[V][V], int res[V], int *resSize) {
    int visited[V] = {0};
    int idx = 0;
    // Loop through all vertices 
    // to handle disconnected graph
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            dfsRec(adj, visited, i, res, &idx);
        }
    }
    *resSize = idx;
}

//Driver Code Starts
void addEdge(int adj[V][V], int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;  // undirected
}
int main() {
    int adj[V][V] = {0};

    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 0, 3);
    addEdge(adj, 4, 5);

    // Perform DFS
    int res[V];
    int resSize = 0;
    dfs(adj, res, &resSize);

    for (int i = 0; i < resSize; i++)
        printf("%d ", res[i]);

    return 0;
}
//Driver Code Ends
