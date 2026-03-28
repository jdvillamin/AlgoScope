#include <stdio.h>

#include "tracer.h"

#define MAX 20

int main() {
  int stack[MAX];
  trace_line(7);
  int top = -1;
  trace_var_init("top", top);
  trace_stack_init("S");
  trace_line(8);
  int n;
  trace_line(9);
  scanf("%d", &n);
  trace_var_init("n", n);

  trace_line(11);
  for (int i = 0; i < n; i++) {
    trace_line(11);
    trace_var("i", i);
    trace_line(12);
    int val;
    trace_line(13);
    scanf("%d", &val);
    trace_var_init("val", val);
    trace_line(14);
    top++;
    trace_var("top", top);
    trace_line(15);
    stack[top] = val;
    trace_stack_push("S", val);
  }

  trace_line(18);
  while (top >= 0) {
    trace_line(18);
    trace_line(19);
    printf("%d ", stack[top]);
    trace_stack_pop("S");
    trace_line(20);
    top--;
    trace_var("top", top);
  }
  trace_line(22);
  printf("\n");

  trace_line(24);
  return 0;
}
