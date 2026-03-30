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
int path[MAX_V];
int pathLen = 0;

void findAllPaths(Graph* g, int src, int dst) {
    visited[src] = 1;
    path[pathLen++] = src;

    if (src == dst) {
        for (int i = 0; i < pathLen; i++) {
            printf("%s ", g->vertices[path[i]].id);
        }
        printf("\n");
    } else {
        for (int i = 0; i < g->vertexCount; i++) {
            if (g->adj[src][i] && !visited[i]) {
                findAllPaths(g, i, dst);
            }
        }
    }

    pathLen--;
    visited[src] = 0;
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
    addEdge(&g, B, C);
    addEdge(&g, B, D);
    addEdge(&g, C, D);

    printf("All paths from A to D:\n");
    findAllPaths(&g, A, D);

    return 0;
}
