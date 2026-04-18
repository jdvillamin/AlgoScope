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

int visited[MAX_V] = {0};
int path[MAX_V];
int pathLen = 0;

void findAllPaths(Graph* g, int src, int dst) {
    trace_line(33);
    visited[src] = 1;
    trace_graph_highlight("G", g->vertices[src].id);
    trace_line(34);
    path[pathLen++] = src;
    trace_var("pathLen", pathLen);

    trace_line(36);
    if (src == dst) {
        trace_line(37);
        for (int i = 0; i < pathLen; i++) {
            trace_line(37);
            trace_var_init("i", i);
            trace_line(38);
            printf("%s ", g->vertices[path[i]].id);
        }
        trace_line(40);
        printf("\n");
    } else {
        trace_line(42);
        for (int i = 0; i < g->vertexCount; i++) {
            trace_line(42);
            trace_var_init("i", i);
            trace_array2d_highlight("adj", src, i);
            trace_line(43);
            if (g->adj[src][i] && !visited[i]) {
                trace_line(44);
                findAllPaths(g, i, dst);
            }
        }
    }

    trace_line(49);
    pathLen--;
    trace_var("pathLen", pathLen);
    trace_line(50);
    visited[src] = 0;
}

int main() {
    Graph g;
    trace_line(55);
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(57);
    int A = addVertex(&g, "A");
    trace_var_init("A", A);
    trace_line(58);
    int B = addVertex(&g, "B");
    trace_var_init("B", B);
    trace_line(59);
    int C = addVertex(&g, "C");
    trace_var_init("C", C);
    trace_line(60);
    int D = addVertex(&g, "D");
    trace_var_init("D", D);

    trace_array2d_init("adj", g.vertexCount, g.vertexCount);
    for (int _r = 0; _r < g.vertexCount; _r++)
        for (int _c = 0; _c < g.vertexCount; _c++)
            trace_array2d("adj", _r, _c, g.adj[_r][_c]);

    trace_line(62);
    addEdge(&g, A, B);
    trace_line(63);
    addEdge(&g, A, C);
    trace_line(64);
    addEdge(&g, B, C);
    trace_line(65);
    addEdge(&g, B, D);
    trace_line(66);
    addEdge(&g, C, D);

    trace_line(68);
    printf("All paths from A to D:\n");
    trace_line(69);
    findAllPaths(&g, A, D);

    trace_line(71);
    return 0;
}
