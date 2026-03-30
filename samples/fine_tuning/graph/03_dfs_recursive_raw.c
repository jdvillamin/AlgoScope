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

int visited[MAX_V] = {0};

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

void dfs(Graph* g, int v) {
    visited[v] = 1;
    printf("%s ", g->vertices[v].id);
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->adj[v][i] && !visited[i]) {
            dfs(g, i);
        }
    }
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
    addEdge(&g, C, E);

    dfs(&g, A);
    printf("\n");

    return 0;
}
