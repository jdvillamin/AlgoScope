#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  rear++;
  queue[rear] = 5;

  rear++;
  queue[rear] = 10;

  rear++;
  queue[rear] = 15;

  rear++;
  queue[rear] = 20;

  printf("dequeued: %d\n", queue[front]);
  front++;

  printf("dequeued: %d\n", queue[front]);
  front++;

  return 0;
}
