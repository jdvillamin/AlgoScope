#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0, rear = -1;

  int n;
  scanf("%d", &n);

  // ---- Enqueue values from input ----
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    rear++;
    queue[rear] = val;
  }

  // ---- Dequeue all ----
  while (front <= rear) {
    printf("dequeued: %d\n", queue[front]);
    front++;
  }

  return 0;
}
