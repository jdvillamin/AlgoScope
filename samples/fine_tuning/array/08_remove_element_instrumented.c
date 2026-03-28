#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[6] = {4, 7, 4, 2, 4, 9};
  trace_array_init("arr", 6);
  trace_array("arr", 0, 4);
  trace_array("arr", 1, 7);
  trace_array("arr", 2, 4);
  trace_array("arr", 3, 2);
  trace_array("arr", 4, 4);
  trace_array("arr", 5, 9);
  trace_line(5);
  int n = 6;
  trace_var_init("n", n);
  trace_line(6);
  int target = 4;
  trace_var_init("target", target);
  trace_line(7);
  int newSize = 0;
  trace_var_init("newSize", newSize);

  trace_line(9);
  for (int i = 0; i < n; i++) {
    trace_line(9);
    trace_var("i", i);
    trace_array_highlight("arr", i);
    trace_line(10);
    if (arr[i] != target) {
      trace_line(11);
      arr[newSize] = arr[i];
      trace_array("arr", newSize, arr[newSize]);
      trace_line(12);
      newSize++;
      trace_var("newSize", newSize);
    }
  }

  trace_line(16);
  return 0;
}
