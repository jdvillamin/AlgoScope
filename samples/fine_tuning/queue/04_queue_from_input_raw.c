#include <stdio.h>

#define MAX 20

int main() {
  int queue[MAX];
  int front = 0;
  int rear = -1;
  int n;

  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    rear++;
    queue[rear] = val;
  }

  while (front <= rear) {
    printf("%d ", queue[front]);
    front++;
  }
  printf("\n");

  return 0;
}
