#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  if (top == -1) {
    printf("Stack is empty\n");
  }

  top++;
  stack[top] = 7;

  top++;
  stack[top] = 12;

  if (top == -1) {
    printf("Stack is empty\n");
  } else {
    printf("Stack has %d elements\n", top + 1);
  }

  return 0;
}
