#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void initGraph(Graph* g) { g->size = 0; }

int addVertex(Graph* g, char* id) {
  strcpy(g->vertices[g->size].id, id);

  g->vertices[g->size].head = NULL;

  g->size++;

  return g->size - 1;
}

void addEdge(Graph* g, int from, int to) {
  AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));

  newNode->index = to;

  newNode->next = g->vertices[from].head;

  g->vertices[from].head = newNode;
}

/* ================= BFS ================= */

void bfs(Graph* g, int start) {
  int visited[MAX] = {0};

  int queue[MAX];

  int front = 0, rear = 0;

  visited[start] = 1;

  queue[rear++] = start;

  while (front < rear) {
    int current = queue[front++];

    AdjNode* temp = g->vertices[current].head;

    while (temp != NULL) {
      if (!visited[temp->index]) {
        visited[temp->index] = 1;

        queue[rear++] = temp->index;
      }

      temp = temp->next;
    }
  }
}

/* ================= MAIN ================= */

int main() {
  Graph g;

  initGraph(&g);

  int A = addVertex(&g, "A");

  int B = addVertex(&g, "B");

  int C = addVertex(&g, "C");

  int D = addVertex(&g, "D");

  int E = addVertex(&g, "E");

  // Directed edges
  addEdge(&g, A, B);

  addEdge(&g, A, C);

  addEdge(&g, B, D);

  addEdge(&g, C, D);

  addEdge(&g, D, E);

  // BFS Traversal
  bfs(&g, A);

  return 0;
}