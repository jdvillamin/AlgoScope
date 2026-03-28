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
  top++; stack[top] = 3;
  trace_var("top", top);
  trace_stack_push("S", 3);
  trace_line(10);
  top++; stack[top] = 7;
  trace_var("top", top);
  trace_stack_push("S", 7);
  trace_line(11);
  top++; stack[top] = 5;
  trace_var("top", top);
  trace_stack_push("S", 5);
  trace_line(12);
  top++; stack[top] = 2;
  trace_var("top", top);
  trace_stack_push("S", 2);

  trace_line(14);
  int sum = 0;
  trace_var_init("sum", sum);
  trace_line(15);
  while (top >= 0) {
    trace_line(15);
    trace_line(16);
    sum += stack[top];
    trace_var("sum", sum);
    trace_stack_pop("S");
    trace_line(17);
    top--;
    trace_var("top", top);
  }

  trace_line(20);
  printf("Sum: %d\n", sum);
  trace_line(21);
  return 0;
}
