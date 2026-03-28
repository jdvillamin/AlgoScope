#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;
  int values[5] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++) {
    top++;
    stack[top] = values[i];
  }

  while (top >= 0) {
    printf("%d ", stack[top]);
    top--;
  }
  printf("\n");

  return 0;
}
