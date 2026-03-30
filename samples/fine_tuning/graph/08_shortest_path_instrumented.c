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
    trace_line(36);
    int E = addVertex(&g, "E");
    trace_graph_node("G", g.vertices[E].id);

    trace_line(38);
    addEdge(&g, A, B);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[B].id);
    trace_line(39);
    addEdge(&g, A, C);
    trace_graph_edge("G", g.vertices[A].id, g.vertices[C].id);
    trace_line(40);
    addEdge(&g, B, D);
    trace_graph_edge("G", g.vertices[B].id, g.vertices[D].id);
    trace_line(41);
    addEdge(&g, C, D);
    trace_graph_edge("G", g.vertices[C].id, g.vertices[D].id);
    trace_line(42);
    addEdge(&g, D, E);
    trace_graph_edge("G", g.vertices[D].id, g.vertices[E].id);

    int dist[MAX_V];
    int prev[MAX_V];
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    trace_line(48);
    int front = 0, rear = 0;

    trace_line(50);
    for (int i = 0; i < MAX_V; i++) {
        trace_line(50);
        trace_line(51);
        dist[i] = -1;
        trace_line(52);
        prev[i] = -1;
    }

    trace_line(55);
    int src = A, dst = E;
    trace_line(56);
    dist[src] = 0;
    trace_line(57);
    visited[src] = 1;
    trace_line(58);
    queue[rear++] = src;

    trace_line(60);
    while (front < rear) {
        trace_line(60);
        trace_line(61);
        int current = queue[front++];
        trace_graph_highlight("G", g.vertices[current].id);
        trace_line(62);
        for (int i = 0; i < g.vertexCount; i++) {
            trace_line(62);
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
            }
        }
    }

    trace_line(71);
    if (dist[dst] == -1) {
        trace_line(72);
        printf("no path from %s to %s\n", g.vertices[src].id, g.vertices[dst].id);
    } else {
        trace_line(74);
        printf("shortest distance from %s to %s: %d\n",
               g.vertices[src].id, g.vertices[dst].id, dist[dst]);

        int path[MAX_V];
        trace_line(78);
        int pathLen = 0;
        trace_var_init("pathLen", pathLen);
        trace_line(79);
        for (int v = dst; v != -1; v = prev[v]) {
            trace_line(79);
            trace_line(80);
            path[pathLen++] = v;
            trace_var("pathLen", pathLen);
        }
        trace_line(82);
        printf("path: ");
        trace_line(83);
        for (int i = pathLen - 1; i >= 0; i--) {
            trace_line(83);
            trace_line(84);
            printf("%s ", g.vertices[path[i]].id);
        }
        trace_line(86);
        printf("\n");
    }

    trace_line(89);
    return 0;
}
