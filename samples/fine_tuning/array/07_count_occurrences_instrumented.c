#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[8] = {3, 7, 3, 2, 3, 8, 7, 3};
  trace_array_init("arr", 8);
  trace_array("arr", 0, 3);
  trace_array("arr", 1, 7);
  trace_array("arr", 2, 3);
  trace_array("arr", 3, 2);
  trace_array("arr", 4, 3);
  trace_array("arr", 5, 8);
  trace_array("arr", 6, 7);
  trace_array("arr", 7, 3);
  trace_line(5);
  int n = 8;
  trace_var_init("n", n);
  trace_line(6);
  int target = 3;
  trace_var_init("target", target);
  trace_line(7);
  int count = 0;
  trace_var_init("count", count);

  trace_line(9);
  for (int i = 0; i < n; i++) {
    trace_line(9);
    trace_var("i", i);
    trace_array_highlight("arr", i);
    trace_line(10);
    if (arr[i] == target) {
      trace_line(11);
      count++;
      trace_var("count", count);
    }
  }

  trace_line(15);
  printf("Count: %d\n", count);
  trace_line(16);
  return 0;
}
