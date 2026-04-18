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
    addEdge(&g, B, C);
    trace_line(39);
    addEdge(&g, C, D);

    int visited[MAX_V] = {0};
    int queue[MAX_V];
    trace_line(43);
    int front = 0, rear = 0;
    trace_var_init("front", front);
    trace_var_init("rear", rear);

    trace_line(45);
    visited[A] = 1;
    trace_line(46);
    queue[rear++] = A;
    trace_var("rear", rear);

    trace_line(48);
    while (front < rear) {
        trace_line(48);
        trace_line(49);
        int current = queue[front++];
        trace_var_init("current", current);
        trace_var("front", front);
        trace_graph_highlight("G", g.vertices[current].id);
        trace_line(50);
        for (int i = 0; i < g.vertexCount; i++) {
            trace_line(50);
            trace_var_init("i", i);
            trace_array2d_highlight("adj", current, i);
            trace_line(51);
            if (g.adj[current][i] && !visited[i]) {
                trace_line(52);
                visited[i] = 1;
                trace_line(53);
                queue[rear++] = i;
                trace_var("rear", rear);
            }
        }
    }

    trace_line(58);
    int connected = 1;
    trace_var_init("connected", connected);
    trace_line(59);
    for (int i = 0; i < g.vertexCount; i++) {
        trace_line(59);
        trace_var_init("i", i);
        trace_line(60);
        if (!visited[i]) {
            trace_line(61);
            connected = 0;
            trace_var("connected", connected);
            break;
        }
    }

    trace_line(66);
    if (connected) {
        trace_line(67);
        printf("graph is connected\n");
    } else {
        trace_line(69);
        printf("graph is not connected\n");
    }

    trace_line(72);
    return 0;
}
