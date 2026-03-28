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
  top++; stack[top] = 4;
  trace_var("top", top);
  trace_stack_push("S", 4);
  trace_line(10);
  top++; stack[top] = 7;
  trace_var("top", top);
  trace_stack_push("S", 7);
  trace_line(11);
  top++; stack[top] = 2;
  trace_var("top", top);
  trace_stack_push("S", 2);
  trace_line(12);
  top++; stack[top] = 11;
  trace_var("top", top);
  trace_stack_push("S", 11);
  trace_line(13);
  top++; stack[top] = 6;
  trace_var("top", top);
  trace_stack_push("S", 6);

  trace_line(15);
  while (top >= 0) {
    trace_line(15);
    trace_line(16);
    int val = stack[top];
    trace_var_init("val", val);
    trace_line(17);
    if (val % 2 == 0) {
      trace_line(18);
      printf("%d is even\n", val);
    } else {
      trace_line(20);
      printf("%d is odd\n", val);
    }
    trace_stack_pop("S");
    trace_line(22);
    top--;
    trace_var("top", top);
  }

  trace_line(25);
  return 0;
}
