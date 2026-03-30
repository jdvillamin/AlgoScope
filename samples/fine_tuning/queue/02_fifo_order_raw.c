#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  rear++;
  queue[rear] = 3;

  rear++;
  queue[rear] = 7;

  rear++;
  queue[rear] = 11;

  rear++;
  queue[rear] = 15;

  rear++;
  queue[rear] = 19;

  while (front <= rear) {
    printf("%d ", queue[front]);
    front++;
  }
  printf("\n");

  return 0;
}
