#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  top++; stack[top] = 3;
  top++; stack[top] = 7;
  top++; stack[top] = 5;
  top++; stack[top] = 2;

  int sum = 0;
  while (top >= 0) {
    sum += stack[top];
    top--;
  }

  printf("Sum: %d\n", sum);
  return 0;
}
