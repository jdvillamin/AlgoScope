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

int pathExists(Graph* g, int src, int dst) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    trace_line(31);
    int front = 0, rear = 0;
    trace_var_init("front", front);
    trace_var_init("rear", rear);

    trace_line(33);
    visited[src] = 1;
    trace_line(34);
    queue[rear++] = src;
    trace_var("rear", rear);

    trace_line(36);
    while (front < rear) {
        trace_line(36);
        trace_line(37);
        int current = queue[front++];
        trace_var_init("current", current);
        trace_var("front", front);
        trace_graph_highlight("G", g->vertices[current].id);
        trace_line(38);
        if (current == dst) return 1;
        trace_line(39);
        for (int i = 0; i < g->vertexCount; i++) {
            trace_line(39);
            trace_var_init("i", i);
            trace_array2d_highlight("adj", current, i);
            trace_line(40);
            if (g->adj[current][i] && !visited[i]) {
                trace_line(41);
                visited[i] = 1;
                trace_line(42);
                queue[rear++] = i;
                trace_var("rear", rear);
            }
        }
    }
    trace_line(46);
    return 0;
}

int main() {
    Graph g;
    trace_line(51);
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(53);
    int A = addVertex(&g, "A");
    trace_var_init("A", A);
    trace_line(54);
    int B = addVertex(&g, "B");
    trace_var_init("B", B);
    trace_line(55);
    int C = addVertex(&g, "C");
    trace_var_init("C", C);
    trace_line(56);
    int D = addVertex(&g, "D");
    trace_var_init("D", D);
    trace_line(57);
    int E = addVertex(&g, "E");
    trace_var_init("E", E);

    trace_array2d_init("adj", g.vertexCount, g.vertexCount);
    for (int _r = 0; _r < g.vertexCount; _r++)
        for (int _c = 0; _c < g.vertexCount; _c++)
            trace_array2d("adj", _r, _c, g.adj[_r][_c]);

    trace_line(59);
    addEdge(&g, A, B);
    trace_line(60);
    addEdge(&g, B, C);
    trace_line(61);
    addEdge(&g, C, D);

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
