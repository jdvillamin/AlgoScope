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

int visited[MAX_V] = {0};

int hasCycleDFS(Graph* g, int v, int parent) {
    visited[v] = 1;
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->adj[v][i]) {
            if (!visited[i]) {
                if (hasCycleDFS(g, i, v)) return 1;
            } else if (i != parent) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));

    int A = addVertex(&g, "A");
    int B = addVertex(&g, "B");
    int C = addVertex(&g, "C");
    int D = addVertex(&g, "D");

    addEdge(&g, A, B);
    addEdge(&g, B, C);
    addEdge(&g, C, D);
    addEdge(&g, D, A);

    if (hasCycleDFS(&g, A, -1)) {
        printf("cycle detected\n");
    } else {
        printf("no cycle\n");
    }

    return 0;
}
