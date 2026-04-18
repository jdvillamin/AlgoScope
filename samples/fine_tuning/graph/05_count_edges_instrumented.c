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
    trace_line(17);
    int idx = g->vertexCount;
    trace_var_init("idx", idx);
    trace_line(18);
    strcpy(g->vertices[idx].id, id);
    trace_graph_node("G", g->vertices[idx].id);
    trace_line(19);
    g->vertexCount++;
    return idx;
}

void addEdge(Graph* g, int from, int to) {
    trace_line(24);
    g->adj[from][to] = 1;
    trace_array2d("adj", from, to, 1);
    trace_line(25);
    g->adj[to][from] = 1;
    trace_array2d("adj", to, from, 1);
    trace_graph_edge("G", g->vertices[from].id, g->vertices[to].id);
}

int main() {
    Graph g;
    trace_line(30);
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(32);
    int A = addVertex(&g, "A");
    trace_var_init("A", A);
    trace_line(33);
    int B = addVertex(&g, "B");
    trace_var_init("B", B);
    trace_line(34);
    int C = addVertex(&g, "C");
    trace_var_init("C", C);
    trace_line(35);
    int D = addVertex(&g, "D");
    trace_var_init("D", D);

    trace_array2d_init("adj", g.vertexCount, g.vertexCount);
    for (int _r = 0; _r < g.vertexCount; _r++)
        for (int _c = 0; _c < g.vertexCount; _c++)
            trace_array2d("adj", _r, _c, g.adj[_r][_c]);

    trace_line(37);
    addEdge(&g, A, B);
    trace_line(38);
    addEdge(&g, A, C);
    trace_line(39);
    addEdge(&g, B, C);
    trace_line(40);
    addEdge(&g, C, D);

    trace_line(42);
    int edges = 0;
    trace_var_init("edges", edges);
    trace_line(43);
    for (int i = 0; i < g.vertexCount; i++) {
        trace_line(43);
        trace_var_init("i", i);
        trace_line(44);
        for (int j = i + 1; j < g.vertexCount; j++) {
            trace_line(44);
            trace_var_init("j", j);
            trace_array2d_highlight("adj", i, j);
            trace_line(45);
            if (g.adj[i][j]) {
                edges++;
                trace_var("edges", edges);
            }
        }
    }

    trace_line(49);
    printf("edges: %d\n", edges);

    trace_line(51);
    return 0;
}
