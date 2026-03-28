#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  int s1[MAX], s2[MAX];
  trace_line(7);
  int top1 = -1, top2 = -1;
  trace_var_init("top1", top1);
  trace_var_init("top2", top2);
  trace_stack_init("S1");
  trace_stack_init("S2");

  trace_line(9);
  top1++;
  trace_var("top1", top1);
  trace_line(10);
  s1[top1] = 3;
  trace_stack_push("S1", 3);
  trace_line(11);
  top1++;
  trace_var("top1", top1);
  trace_line(12);
  s1[top1] = 6;
  trace_stack_push("S1", 6);

  trace_line(14);
  top2++;
  trace_var("top2", top2);
  trace_line(15);
  s2[top2] = 9;
  trace_stack_push("S2", 9);
  trace_line(16);
  top2++;
  trace_var("top2", top2);
  trace_line(17);
  s2[top2] = 12;
  trace_stack_push("S2", 12);

  trace_line(19);
  printf("s1 top: %d\n", s1[top1]);
  trace_line(20);
  printf("s2 top: %d\n", s2[top2]);

  trace_stack_pop("S1");
  trace_line(22);
  top1--;
  trace_var("top1", top1);
  trace_stack_pop("S2");
  trace_line(23);
  top2--;
  trace_var("top2", top2);

  trace_line(25);
  return 0;
}
