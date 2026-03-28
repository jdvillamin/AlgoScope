#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  top++;
  stack[top] = 8;

  top++;
  stack[top] = 14;

  top++;
  stack[top] = 3;

  printf("top: %d\n", stack[top]);

  top--;

  printf("top: %d\n", stack[top]);

  return 0;
}
