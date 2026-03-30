#include <stdio.h>
#include <string.h>

#define MAX_V 10
#define MAX_E 20

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
    addEdge(&g, C, E);

    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    visited[A] = 1;
    queue[rear++] = A;

    while (front < rear) {
        int current = queue[front++];
        printf("%s ", g.vertices[current].id);
        for (int i = 0; i < g.vertexCount; i++) {
            if (g.adj[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");

    return 0;
}
