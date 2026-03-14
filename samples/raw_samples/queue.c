#include <stdio.h>

#define MAX 10

int main() {
  int queue[MAX];
  int front = 0, rear = -1;

  // enqueue 5
  rear++;
  queue[rear] = 5;

  // enqueue 10
  rear++;
  queue[rear] = 10;

  // enqueue 15
  rear++;
  queue[rear] = 15;

  // dequeue
  front++;

  return 0;
}