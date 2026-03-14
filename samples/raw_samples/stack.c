#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  trace_stack_init("S");

  int stack[MAX];
  int top = -1;
  trace_line(__LINE__ - 1);

  // ---- push 5 ----
  top++;
  trace_line(__LINE__ - 1);

  stack[top] = 5;
  trace_line(__LINE__ - 1);

  trace_stack_push("S", 5);

  // ---- push 10 ----
  top++;
  trace_line(__LINE__ - 1);

  stack[top] = 10;
  trace_line(__LINE__ - 1);

  trace_stack_push("S", 10);

  // ---- push 15 ----
  top++;
  trace_line(__LINE__ - 1);

  stack[top] = 15;
  trace_line(__LINE__ - 1);

  trace_stack_push("S", 15);

  // ---- pop ----
  trace_line(__LINE__ - 1);
  trace_stack_pop("S");

  top--;
  trace_line(__LINE__ - 1);

  return 0;
}