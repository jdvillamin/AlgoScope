#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tracer.h"

#define MAX 10

typedef struct AdjNode {
  int index;
  struct AdjNode* next;
} AdjNode;

typedef struct {
  char id[20];
  AdjNode* head;
} Vertex;

typedef struct {
  Vertex vertices[MAX];
  int size;
} Graph;

/* ================= GRAPH FUNCTIONS ================= */

void initGraph(Graph* g) {
  g->size = 0;
  trace_line(__LINE__ - 1);
}

int addVertex(Graph* g, char* id) {
  strcpy(g->vertices[g->size].id, id);
  trace_line(__LINE__ - 1);

  g->vertices[g->size].head = NULL;
  trace_line(__LINE__ - 1);

  trace_graph_node("G", id);

  g->size++;
  trace_line(__LINE__ - 1);

  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
  trace_line(__LINE__ - 1);

  newNode->index = to;
  trace_line(__LINE__ - 1);

  newNode->next = g->vertices[from].head;
  trace_line(__LINE__ - 1);

  g->vertices[from].head = newNode;
  trace_line(__LINE__ - 1);

  trace_graph_edge("G", g->vertices[from].id, g->vertices[to].id);
}

/* ================= BFS ================= */

void bfs(Graph* g, int start) {
  int visited[MAX] = {0};
  trace_line(__LINE__ - 1);

  int queue[MAX];
  trace_line(__LINE__ - 1);

  int front = 0, rear = 0;
  trace_line(__LINE__ - 1);

  visited[start] = 1;
  trace_line(__LINE__ - 1);

  queue[rear++] = start;
  trace_line(__LINE__ - 1);

  while (front < rear) {
    trace_line(__LINE__ - 1);

    int current = queue[front++];
    trace_line(__LINE__ - 1);

    trace_graph_highlight("G", g->vertices[current].id);

    AdjNode* temp = g->vertices[current].head;
    trace_line(__LINE__ - 1);

    while (temp != NULL) {
      trace_line(__LINE__ - 1);

      if (!visited[temp->index]) {
        trace_line(__LINE__ - 1);

        visited[temp->index] = 1;
        trace_line(__LINE__ - 1);

        queue[rear++] = temp->index;
        trace_line(__LINE__ - 1);
      }

      temp = temp->next;
      trace_line(__LINE__ - 1);
    }
  }
}

/* ================= MAIN ================= */

int main() {
  Graph g;
  trace_line(__LINE__ - 1);

  initGraph(&g);

  trace_graph_init("G");

  int A = addVertex(&g, "A");
  trace_line(__LINE__ - 1);

  int B = addVertex(&g, "B");
  trace_line(__LINE__ - 1);

  int C = addVertex(&g, "C");
  trace_line(__LINE__ - 1);

  int D = addVertex(&g, "D");
  trace_line(__LINE__ - 1);

  int E = addVertex(&g, "E");
  trace_line(__LINE__ - 1);

  // Directed edges
  addEdge(&g, A, B);
  trace_line(__LINE__ - 1);

  addEdge(&g, A, C);
  trace_line(__LINE__ - 1);

  addEdge(&g, B, D);
  trace_line(__LINE__ - 1);

  addEdge(&g, C, D);
  trace_line(__LINE__ - 1);

  addEdge(&g, D, E);
  trace_line(__LINE__ - 1);

  // BFS Traversal
  bfs(&g, A);
  trace_line(__LINE__ - 1);

  return 0;
}