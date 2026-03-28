#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[6] = {4, 11, 2, 19, 7, 3};
  trace_array_init("arr", 6);
  trace_array("arr", 0, 4);
  trace_array("arr", 1, 11);
  trace_array("arr", 2, 2);
  trace_array("arr", 3, 19);
  trace_array("arr", 4, 7);
  trace_array("arr", 5, 3);
  trace_line(5);
  int n = 6;
  trace_var_init("n", n);
  trace_line(6);
  int max = arr[0];
  trace_var_init("max", max);

  trace_line(8);
  for (int i = 1; i < n; i++) {
    trace_line(8);
    trace_var("i", i);
    trace_array_highlight("arr", i);
    trace_line(9);
    if (arr[i] > max) {
      trace_line(10);
      max = arr[i];
      trace_var("max", max);
    }
  }

  trace_line(14);
  printf("Max: %d\n", max);
  trace_line(15);
  return 0;
}
