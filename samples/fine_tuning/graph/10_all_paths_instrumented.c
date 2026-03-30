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
int path[MAX_V];
int pathLen = 0;

void findAllPaths(Graph* g, int src, int dst) {
    trace_line(34);
    visited[src] = 1;
    trace_graph_highlight("G", g->vertices[src].id);
    trace_line(35);
    path[pathLen++] = src;
    trace_var("pathLen", pathLen);

    trace_line(37);
    if (src == dst) {
        trace_line(38);
        for (int i = 0; i < pathLen; i++) {
            trace_line(38);
            trace_line(39);
            printf("%s ", g->vertices[path[i]].id);
        }
        trace_line(41);
        printf("\n");
    } else {
        trace_line(43);
        for (int i = 0; i < g->vertexCount; i++) {
            trace_line(43);
            trace_line(44);
            if (g->adj[src][i] && !visited[i]) {
                trace_line(45);
                findAllPaths(g, i, dst);
            }
        }
    }

    trace_line(50);
    pathLen--;
    trace_var("pathLen", pathLen);
    trace_line(51);
    visited[src] = 0;
}

int main() {
    Graph g;
    memset(&g, 0, sizeof(Graph));
    trace_graph_init("G");

    trace_line(57);
    int A = addVertex(&g, "A");
    trace_graph_node("G", g.vertices[A].id);
    trace_line(58);
    int B = addVertex(&g, "B");
    trace_graph_node("G", g.vertices[B].id);
    trace_line(59);
    int C = addVertex(&g, "C");
    trace_graph_node("G", g.vertices[C].id);
    trace_line(60);
    int D = addVertex(&g, "D");
    trace_graph_node("G", g.vertices[D].id);

    trace_line(62);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(63);
    addEdge(&g, A, C);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[C].id);
    trace_line(64);
    addEdge(&g, B, C);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[C].id);
    trace_line(65);
    addEdge(&g, B, D);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[D].id);
    trace_line(66);
    addEdge(&g, C, D);
    trace_graph_edge("G", g.vertices[C].id, g.vertices[D].id);

    trace_line(68);
    printf("All paths from A to D:\n");
    trace_line(69);
    findAllPaths(&g, A, D);

    trace_line(71);
    return 0;
}
