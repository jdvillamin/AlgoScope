#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  int stack[MAX], minStack[MAX];
  trace_line(7);
  int top = -1, minTop = -1;
  trace_var_init("top", top);
  trace_var_init("minTop", minTop);
  trace_stack_init("S");
  trace_stack_init("Min");

  int vals[4] = {5, 3, 7, 1};
  trace_array_init("vals", 4);
  trace_array("vals", 0, 5);
  trace_array("vals", 1, 3);
  trace_array("vals", 2, 7);
  trace_array("vals", 3, 1);

  trace_line(11);
  for (int i = 0; i < 4; i++) {
    trace_line(11);
    trace_var("i", i);
    trace_line(12);
    top++;
    trace_var("top", top);
    trace_line(13);
    stack[top] = vals[i];
    trace_stack_push("S", vals[i]);

    trace_line(15);
    if (minTop == -1 || vals[i] <= minStack[minTop]) {
      trace_line(16);
      minTop++;
      trace_var("minTop", minTop);
      trace_line(17);
      minStack[minTop] = vals[i];
      trace_stack_push("Min", vals[i]);
    }
  }

  trace_line(21);
  printf("min: %d\n", minStack[minTop]);

  trace_stack_pop("S");
  trace_line(23);
  top--;
  trace_var("top", top);
  trace_line(24);
  if (stack[top + 1] == minStack[minTop]) {
    trace_stack_pop("Min");
    trace_line(25);
    minTop--;
    trace_var("minTop", minTop);
  }

  trace_line(28);
  printf("min: %d\n", minStack[minTop]);

  trace_line(30);
  return 0;
}
