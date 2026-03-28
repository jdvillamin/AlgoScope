#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  int stack[MAX];
  trace_line(7);
  int top = -1;
  trace_var_init("top", top);
  trace_stack_init("S");

  trace_line(9);
  if (top == -1) {
    trace_line(10);
    printf("Stack is empty\n");
  }

  trace_line(13);
  top++;
  trace_var("top", top);
  trace_line(14);
  stack[top] = 7;
  trace_stack_push("S", 7);

  trace_line(16);
  top++;
  trace_var("top", top);
  trace_line(17);
  stack[top] = 12;
  trace_stack_push("S", 12);

  trace_line(19);
  if (top == -1) {
    trace_line(20);
    printf("Stack is empty\n");
  } else {
    trace_line(22);
    printf("Stack has %d elements\n", top + 1);
  }

  trace_line(25);
  return 0;
}
