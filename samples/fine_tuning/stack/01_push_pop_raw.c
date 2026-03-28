#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  top++;
  stack[top] = 5;

  top++;
  stack[top] = 10;

  top++;
  stack[top] = 15;

  top++;
  stack[top] = 20;

  printf("popped: %d\n", stack[top]);
  top--;

  printf("popped: %d\n", stack[top]);
  top--;

  return 0;
}
