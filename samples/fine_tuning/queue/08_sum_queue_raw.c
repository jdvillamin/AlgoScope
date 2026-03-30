#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;
  int sum = 0;

  rear++;
  queue[rear] = 4;

  rear++;
  queue[rear] = 9;

  rear++;
  queue[rear] = 2;

  rear++;
  queue[rear] = 11;

  while (front <= rear) {
    sum += queue[front];
    front++;
  }

  printf("sum: %d\n", sum);

  return 0;
}
