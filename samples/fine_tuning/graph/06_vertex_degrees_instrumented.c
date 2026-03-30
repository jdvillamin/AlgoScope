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

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(32);
    int A = addVertex(&g, "A");
    trace_graph_node("G", g.vertices[A].id);
    trace_line(33);
    int B = addVertex(&g, "B");
    trace_graph_node("G", g.vertices[B].id);
    trace_line(34);
    int C = addVertex(&g, "C");
    trace_graph_node("G", g.vertices[C].id);
    trace_line(35);
    int D = addVertex(&g, "D");
    trace_graph_node("G", g.vertices[D].id);

    trace_line(37);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(38);
    addEdge(&g, A, C);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[C].id);
    trace_line(39);
    addEdge(&g, A, D);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[D].id);
    trace_line(40);
    addEdge(&g, B, C);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[C].id);

    trace_line(42);
    for (int i = 0; i < g.vertexCount; i++) {
        trace_line(42);
        trace_graph_highlight("G", g.vertices[i].id);
        trace_line(43);
        int degree = 0;
        trace_var_init("degree", degree);
        trace_line(44);
        for (int j = 0; j < g.vertexCount; j++) {
            trace_line(44);
            trace_line(45);
            if (g.adj[i][j]) {
                degree++;
                trace_var("degree", degree);
            }
        }
        trace_line(47);
        printf("%s: degree %d\n", g.vertices[i].id, degree);
    }

    trace_line(50);
    return 0;
}
