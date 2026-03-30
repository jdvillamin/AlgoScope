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

int visited[MAX_V] = {0};

int hasCycleDFS(Graph* g, int v, int parent) {
    trace_line(32);
    visited[v] = 1;
    trace_graph_highlight("G", g->vertices[v].id);
    trace_line(33);
    for (int i = 0; i < g->vertexCount; i++) {
        trace_line(33);
        trace_line(34);
        if (g->adj[v][i]) {
            trace_line(35);
            if (!visited[i]) {
                trace_line(36);
                if (hasCycleDFS(g, i, v)) return 1;
            } else if (i != parent) {
                trace_line(38);
                return 1;
            }
        }
    }
    trace_line(42);
    return 0;
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(48);
    int A = addVertex(&g, "A");
    trace_graph_node("G", g.vertices[A].id);
    trace_line(49);
    int B = addVertex(&g, "B");
    trace_graph_node("G", g.vertices[B].id);
    trace_line(50);
    int C = addVertex(&g, "C");
    trace_graph_node("G", g.vertices[C].id);
    trace_line(51);
    int D = addVertex(&g, "D");
    trace_graph_node("G", g.vertices[D].id);

    trace_line(53);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(54);
    addEdge(&g, B, C);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[C].id);
    trace_line(55);
    addEdge(&g, C, D);
    trace_graph_edge("G", g.vertices[C].id, g.vertices[D].id);
    trace_line(56);
    addEdge(&g, D, A);
    trace_graph_edge("G", g.vertices[D].id, g.vertices[A].id);

    trace_line(58);
    if (hasCycleDFS(&g, A, -1)) {
        trace_line(59);
        printf("cycle detected\n");
    } else {
        trace_line(61);
        printf("no cycle\n");
    }

    trace_line(64);
    return 0;
}
