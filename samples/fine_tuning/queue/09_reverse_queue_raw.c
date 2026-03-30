#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;

  rear++;
  queue[rear] = 1;

  rear++;
  queue[rear] = 2;

  rear++;
  queue[rear] = 3;

  rear++;
  queue[rear] = 4;

  int temp[MAX];
  int count = rear - front + 1;

  for (int i = 0; i < count; i++) {
    temp[i] = queue[front];
    front++;
  }

  front = 0;
  rear = -1;

  for (int i = count - 1; i >= 0; i--) {
    rear++;
    queue[rear] = temp[i];
  }

  while (front <= rear) {
    printf("%d ", queue[front]);
    front++;
  }
  printf("\n");

  return 0;
}
