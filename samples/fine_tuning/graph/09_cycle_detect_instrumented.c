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
    trace_line(23);
    g->adj[from][to] = 1;
    trace_array2d("adj", from, to, 1);
    trace_line(24);
    g->adj[to][from] = 1;
    trace_array2d("adj", to, from, 1);
    trace_graph_edge("G", g->vertices[from].id, g->vertices[to].id);
}

int visited[MAX_V] = {0};

int hasCycleDFS(Graph* g, int v, int parent) {
    trace_line(31);
    visited[v] = 1;
    trace_graph_highlight("G", g->vertices[v].id);
    trace_line(32);
    for (int i = 0; i < g->vertexCount; i++) {
        trace_line(32);
        trace_var_init("i", i);
        trace_array2d_highlight("adj", v, i);
        trace_line(33);
        if (g->adj[v][i]) {
            trace_line(34);
            if (!visited[i]) {
                trace_line(35);
                if (hasCycleDFS(g, i, v)) return 1;
            } else if (i != parent) {
                trace_line(37);
                return 1;
            }
        }
    }
    trace_line(41);
    return 0;
}

int main() {
    Graph g;
    trace_line(46);
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(48);
    int A = addVertex(&g, "A");
    trace_var_init("A", A);
    trace_line(49);
    int B = addVertex(&g, "B");
    trace_var_init("B", B);
    trace_line(50);
    int C = addVertex(&g, "C");
    trace_var_init("C", C);
    trace_line(51);
    int D = addVertex(&g, "D");
    trace_var_init("D", D);

    trace_array2d_init("adj", g.vertexCount, g.vertexCount);
    for (int _r = 0; _r < g.vertexCount; _r++)
        for (int _c = 0; _c < g.vertexCount; _c++)
            trace_array2d("adj", _r, _c, g.adj[_r][_c]);

    trace_line(53);
    addEdge(&g, A, B);
    trace_line(54);
    addEdge(&g, B, C);
    trace_line(55);
    addEdge(&g, C, D);
    trace_line(56);
    addEdge(&g, D, A);

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
