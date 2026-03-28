#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX], minStack[MAX];
  int top = -1, minTop = -1;

  int vals[4] = {5, 3, 7, 1};

  for (int i = 0; i < 4; i++) {
    top++;
    stack[top] = vals[i];

    if (minTop == -1 || vals[i] <= minStack[minTop]) {
      minTop++;
      minStack[minTop] = vals[i];
    }
  }

  printf("min: %d\n", minStack[minTop]);

  top--;
  if (stack[top + 1] == minStack[minTop]) {
    minTop--;
  }

  printf("min: %d\n", minStack[minTop]);

  return 0;
}
