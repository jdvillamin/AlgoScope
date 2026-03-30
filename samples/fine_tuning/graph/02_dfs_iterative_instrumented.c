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
    addEdge(&g, B, D);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[D].id);

    int visited[MAX_V] = {0};
    int stack[MAX_V];
    trace_line(43);
    int top = -1;

    trace_line(45);
    stack[++top] = A;

    trace_line(47);
    while (top >= 0) {
        trace_line(47);
        trace_line(48);
        int current = stack[top--];
        trace_line(49);
        if (visited[current]) continue;
        trace_line(50);
        visited[current] = 1;
        trace_graph_highlight("G", g.vertices[current].id);
        trace_line(51);
        printf("%s ", g.vertices[current].id);
        trace_line(52);
        for (int i = g.vertexCount - 1; i >= 0; i--) {
            trace_line(52);
            trace_line(53);
            if (g.adj[current][i] && !visited[i]) {
                trace_line(54);
                stack[++top] = i;
            }
        }
    }
    trace_line(58);
    printf("\n");

    trace_line(60);
    return 0;
}
