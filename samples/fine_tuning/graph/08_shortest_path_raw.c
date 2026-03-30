#include <stdio.h>
#include <string.h>

#define MAX_V 10

typedef struct {
    char id[10];
} Vertex;

typedef struct {
    Vertex vertices[MAX_V];
    int adj[MAX_V][MAX_V];
    int vertexCount;
} Graph;

int addVertex(Graph* g, const char* id) {
    int idx = g->vertexCount;
    strcpy(g->vertices[idx].id, id);
    g->vertexCount++;
    return idx;
}

void addEdge(Graph* g, int from, int to) {
    g->adj[from][to] = 1;
    g->adj[to][from] = 1;
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));

    int A = addVertex(&g, "A");
    int B = addVertex(&g, "B");
    int C = addVertex(&g, "C");
    int D = addVertex(&g, "D");
    int E = addVertex(&g, "E");

    addEdge(&g, A, B);
    addEdge(&g, A, C);
    addEdge(&g, B, D);
    addEdge(&g, C, D);
    addEdge(&g, D, E);

    int dist[MAX_V];
    int prev[MAX_V];
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    for (int i = 0; i < MAX_V; i++) {
        dist[i] = -1;
        prev[i] = -1;
    }

    int src = A, dst = E;
    dist[src] = 0;
    visited[src] = 1;
    queue[rear++] = src;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < g.vertexCount; i++) {
            if (g.adj[current][i] && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[current] + 1;
                prev[i] = current;
                queue[rear++] = i;
            }
        }
    }

    if (dist[dst] == -1) {
        printf("no path from %s to %s\n", g.vertices[src].id, g.vertices[dst].id);
    } else {
        printf("shortest distance from %s to %s: %d\n",
               g.vertices[src].id, g.vertices[dst].id, dist[dst]);

        int path[MAX_V];
        int pathLen = 0;
        for (int v = dst; v != -1; v = prev[v]) {
            path[pathLen++] = v;
        }
        printf("path: ");
        for (int i = pathLen - 1; i >= 0; i--) {
            printf("%s ", g.vertices[path[i]].id);
        }
        printf("\n");
    }

    return 0;
}
