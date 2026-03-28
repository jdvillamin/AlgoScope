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
  top++;
  trace_var("top", top);
  trace_line(10);
  stack[top] = 5;
  trace_stack_push("S", 5);

  trace_line(12);
  top++;
  trace_var("top", top);
  trace_line(13);
  stack[top] = 10;
  trace_stack_push("S", 10);

  trace_line(15);
  top++;
  trace_var("top", top);
  trace_line(16);
  stack[top] = 15;
  trace_stack_push("S", 15);

  trace_line(18);
  top++;
  trace_var("top", top);
  trace_line(19);
  stack[top] = 20;
  trace_stack_push("S", 20);

  trace_line(21);
  printf("popped: %d\n", stack[top]);
  trace_stack_pop("S");
  trace_line(22);
  top--;
  trace_var("top", top);

  trace_line(24);
  printf("popped: %d\n", stack[top]);
  trace_stack_pop("S");
  trace_line(25);
  top--;
  trace_var("top", top);

  trace_line(27);
  return 0;
}
