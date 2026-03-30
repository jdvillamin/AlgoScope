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

int visited[MAX_V] = {0};

int addVertex(Graph* g, const char* id) {
    trace_line(19);
    int idx = g->vertexCount;
    trace_line(20);
    strcpy(g->vertices[idx].id, id);
    trace_line(21);
    g->vertexCount++;
    return idx;
}

void addEdge(Graph* g, int from, int to) {
    trace_line(26);
    g->adj[from][to] = 1;
    trace_line(27);
    g->adj[to][from] = 1;
}

void dfs(Graph* g, int v) {
    trace_line(31);
    visited[v] = 1;
    trace_graph_highlight("G", g->vertices[v].id);
    trace_line(32);
    printf("%s ", g->vertices[v].id);
    trace_line(33);
    for (int i = 0; i < g->vertexCount; i++) {
        trace_line(33);
        trace_line(34);
        if (g->adj[v][i] && !visited[i]) {
            trace_line(35);
            dfs(g, i);
        }
    }
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(43);
    int A = addVertex(&g, "A");
    trace_graph_node("G", g.vertices[A].id);
    trace_line(44);
    int B = addVertex(&g, "B");
    trace_graph_node("G", g.vertices[B].id);
    trace_line(45);
    int C = addVertex(&g, "C");
    trace_graph_node("G", g.vertices[C].id);
    trace_line(46);
    int D = addVertex(&g, "D");
    trace_graph_node("G", g.vertices[D].id);
    trace_line(47);
    int E = addVertex(&g, "E");
    trace_graph_node("G", g.vertices[E].id);

    trace_line(49);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(50);
    addEdge(&g, A, C);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[C].id);
    trace_line(51);
    addEdge(&g, B, D);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[D].id);
    trace_line(52);
    addEdge(&g, C, E);
    trace_graph_edge("G", g.vertices[C].id, g.vertices[E].id);

    trace_line(54);
    dfs(&g, A);
    trace_line(55);
    printf("\n");

    trace_line(57);
    return 0;
}
