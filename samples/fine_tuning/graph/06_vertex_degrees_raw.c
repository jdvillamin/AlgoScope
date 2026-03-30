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

    addEdge(&g, A, B);
    addEdge(&g, A, C);
    addEdge(&g, A, D);
    addEdge(&g, B, C);

    for (int i = 0; i < g.vertexCount; i++) {
        int degree = 0;
        for (int j = 0; j < g.vertexCount; j++) {
            if (g.adj[i][j]) degree++;
        }
        printf("%s: degree %d\n", g.vertices[i].id, degree);
    }

    return 0;
}
