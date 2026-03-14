#include <stdio.h>

#define MAX 10

int main() {
  int stack[MAX];
  int top = -1;

  // ---- push 5 ----
  top++;

  stack[top] = 5;

  // ---- push 10 ----
  top++;

  stack[top] = 10;

  // ---- push 15 ----
  top++;

  stack[top] = 15;

  // ---- pop ----

  top--;

  return 0;
}