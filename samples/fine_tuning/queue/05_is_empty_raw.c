#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  rear++;
  queue[rear] = 7;

  rear++;
  queue[rear] = 14;

  printf("dequeued: %d\n", queue[front]);
  front++;

  printf("dequeued: %d\n", queue[front]);
  front++;

  if (front > rear) {
    printf("queue is empty\n");
  } else {
    printf("queue is not empty\n");
  }

  return 0;
}
