#include <stdio.h>
#include <string.h>

#include "tracer.h"

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
    trace_line(18);
    int idx = g->vertexCount;
    trace_line(19);
    strcpy(g->vertices[idx].id, id);
    trace_line(20);
    g->vertexCount++;
    return idx;
}

void addEdge(Graph* g, int from, int to) {
    trace_line(25);
    g->adj[from][to] = 1;
    trace_line(26);
    g->adj[to][from] = 1;
}

int pathExists(Graph* g, int src, int dst) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    trace_line(32);
    int front = 0, rear = 0;

    trace_line(34);
    visited[src] = 1;
    trace_line(35);
    queue[rear++] = src;

    trace_line(37);
    while (front < rear) {
        trace_line(37);
        trace_line(38);
        int current = queue[front++];
        trace_graph_highlight("G", g->vertices[current].id);
        trace_line(39);
        if (current == dst) return 1;
        trace_line(40);
        for (int i = 0; i < g->vertexCount; i++) {
            trace_line(40);
            trace_line(41);
            if (g->adj[current][i] && !visited[i]) {
                trace_line(42);
                visited[i] = 1;
                trace_line(43);
                queue[rear++] = i;
            }
        }
    }
    trace_line(47);
    return 0;
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(53);
    int A = addVertex(&g, "A");
    trace_graph_node("G", g.vertices[A].id);
    trace_line(54);
    int B = addVertex(&g, "B");
    trace_graph_node("G", g.vertices[B].id);
    trace_line(55);
    int C = addVertex(&g, "C");
    trace_graph_node("G", g.vertices[C].id);
    trace_line(56);
    int D = addVertex(&g, "D");
    trace_graph_node("G", g.vertices[D].id);
    trace_line(57);
    int E = addVertex(&g, "E");
    trace_graph_node("G", g.vertices[E].id);

    trace_line(59);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(60);
    addEdge(&g, B, C);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[C].id);
    trace_line(61);
    addEdge(&g, C, D);
    trace_graph_edge("G", g.vertices[C].id, g.vertices[D].id);

    trace_line(63);
    if (pathExists(&g, A, D)) {
        trace_line(64);
        printf("path exists from A to D\n");
    } else {
        trace_line(66);
        printf("no path from A to D\n");
    }

    trace_line(69);
    if (pathExists(&g, A, E)) {
        trace_line(70);
        printf("path exists from A to E\n");
    } else {
        trace_line(72);
        printf("no path from A to E\n");
    }

    trace_line(75);
    return 0;
}
