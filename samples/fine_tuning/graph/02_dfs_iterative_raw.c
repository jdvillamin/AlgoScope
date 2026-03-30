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
    addEdge(&g, B, D);

    int visited[MAX_V] = {0};
    int stack[MAX_V];
    int top = -1;

    stack[++top] = A;

    while (top >= 0) {
        int current = stack[top--];
        if (visited[current]) continue;
        visited[current] = 1;
        printf("%s ", g.vertices[current].id);
        for (int i = g.vertexCount - 1; i >= 0; i--) {
            if (g.adj[current][i] && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
    printf("\n");

    return 0;
}
