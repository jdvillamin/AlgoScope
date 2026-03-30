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
    addEdge(&g, B, C);
    addEdge(&g, C, D);

    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    visited[A] = 1;
    queue[rear++] = A;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < g.vertexCount; i++) {
            if (g.adj[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    int connected = 1;
    for (int i = 0; i < g.vertexCount; i++) {
        if (!visited[i]) {
            connected = 0;
            break;
        }
    }

    if (connected) {
        printf("graph is connected\n");
    } else {
        printf("graph is not connected\n");
    }

    return 0;
}
