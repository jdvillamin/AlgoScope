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
  stack[top] = 8;
  trace_stack_push("S", 8);

  trace_line(12);
  top++;
  trace_var("top", top);
  trace_line(13);
  stack[top] = 14;
  trace_stack_push("S", 14);

  trace_line(15);
  top++;
  trace_var("top", top);
  trace_line(16);
  stack[top] = 3;
  trace_stack_push("S", 3);

  trace_line(18);
  printf("top: %d\n", stack[top]);
  trace_stack_top("S", stack[top]);

  trace_stack_pop("S");
  trace_line(20);
  top--;
  trace_var("top", top);

  trace_line(22);
  printf("top: %d\n", stack[top]);
  trace_stack_top("S", stack[top]);

  trace_line(24);
  return 0;
}
