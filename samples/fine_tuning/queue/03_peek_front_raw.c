#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  rear++;
  queue[rear] = 8;

  rear++;
  queue[rear] = 12;

  rear++;
  queue[rear] = 4;

  printf("front: %d\n", queue[front]);

  printf("dequeued: %d\n", queue[front]);
  front++;

  printf("front: %d\n", queue[front]);

  return 0;
}
