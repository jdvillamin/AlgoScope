#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  top++; stack[top] = 4;
  top++; stack[top] = 7;
  top++; stack[top] = 2;
  top++; stack[top] = 11;
  top++; stack[top] = 6;

  while (top >= 0) {
    int val = stack[top];
    if (val % 2 == 0) {
      printf("%d is even\n", val);
    } else {
      printf("%d is odd\n", val);
    }
    top--;
  }

  return 0;
}
