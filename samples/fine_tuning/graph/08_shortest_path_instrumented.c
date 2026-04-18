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
    trace_line(36);
    int E = addVertex(&g, "E");
    trace_var_init("E", E);

    trace_array2d_init("adj", g.vertexCount, g.vertexCount);
    for (int _r = 0; _r < g.vertexCount; _r++)
        for (int _c = 0; _c < g.vertexCount; _c++)
            trace_array2d("adj", _r, _c, g.adj[_r][_c]);

    trace_line(38);
    addEdge(&g, A, B);
    trace_line(39);
    addEdge(&g, A, C);
    trace_line(40);
    addEdge(&g, B, D);
    trace_line(41);
    addEdge(&g, C, D);
    trace_line(42);
    addEdge(&g, D, E);

    int dist[MAX_V];
    int prev[MAX_V];
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    trace_line(48);
    int front = 0, rear = 0;
    trace_var_init("front", front);
    trace_var_init("rear", rear);

    trace_line(50);
    for (int i = 0; i < MAX_V; i++) {
        trace_line(50);
        trace_var_init("i", i);
        trace_line(51);
        dist[i] = -1;
        trace_line(52);
        prev[i] = -1;
    }

    trace_line(55);
    int src = A, dst = E;
    trace_var_init("src", src);
    trace_var_init("dst", dst);
    trace_line(56);
    dist[src] = 0;
    trace_line(57);
    visited[src] = 1;
    trace_line(58);
    queue[rear++] = src;
    trace_var("rear", rear);

    trace_line(60);
    while (front < rear) {
        trace_line(60);
        trace_line(61);
        int current = queue[front++];
        trace_var_init("current", current);
        trace_var("front", front);
        trace_graph_highlight("G", g.vertices[current].id);
        trace_line(62);
        for (int i = 0; i < g.vertexCount; i++) {
            trace_line(62);
            trace_var_init("i", i);
            trace_array2d_highlight("adj", current, i);
            trace_line(63);
            if (g.adj[current][i] && !visited[i]) {
                trace_line(64);
                visited[i] = 1;
                trace_line(65);
                dist[i] = dist[current] + 1;
                trace_line(66);
                prev[i] = current;
                trace_line(67);
                queue[rear++] = i;
                trace_var("rear", rear);
            }
        }
    }

    trace_line(72);
    if (dist[dst] == -1) {
        trace_line(73);
        printf("no path from %s to %s\n", g.vertices[src].id, g.vertices[dst].id);
    } else {
        trace_line(75);
        printf("shortest distance from %s to %s: %d\n",
               g.vertices[src].id, g.vertices[dst].id, dist[dst]);

        int path[MAX_V];
        trace_line(79);
        int pathLen = 0;
        trace_var_init("pathLen", pathLen);
        trace_line(80);
        for (int v = dst; v != -1; v = prev[v]) {
            trace_line(80);
            trace_var_init("v", v);
            trace_line(81);
            path[pathLen++] = v;
            trace_var("pathLen", pathLen);
        }
        trace_line(83);
        printf("path: ");
        trace_line(84);
        for (int i = pathLen - 1; i >= 0; i--) {
            trace_line(84);
            trace_var_init("i", i);
            trace_line(85);
            printf("%s ", g.vertices[path[i]].id);
        }
        trace_line(87);
        printf("\n");
    }

    trace_line(90);
    return 0;
}
