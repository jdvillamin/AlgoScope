#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  int stack[MAX];
  trace_line(7);
  int top = -1;
  trace_var_init("top", top);
  trace_stack_init("S");
  int values[5] = {1, 2, 3, 4, 5};
  trace_array_init("values", 5);
  trace_array("values", 0, 1);
  trace_array("values", 1, 2);
  trace_array("values", 2, 3);
  trace_array("values", 3, 4);
  trace_array("values", 4, 5);

  trace_line(10);
  for (int i = 0; i < 5; i++) {
    trace_line(10);
    trace_var("i", i);
    trace_line(11);
    top++;
    trace_var("top", top);
    trace_line(12);
    stack[top] = values[i];
    trace_stack_push("S", values[i]);
  }

  trace_line(15);
  while (top >= 0) {
    trace_line(15);
    trace_line(16);
    printf("%d ", stack[top]);
    trace_stack_pop("S");
    trace_line(17);
    top--;
    trace_var("top", top);
  }
  trace_line(19);
  printf("\n");

  trace_line(21);
  return 0;
}
