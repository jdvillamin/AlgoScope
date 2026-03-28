#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  trace_array_init("arr", 5);
  trace_array("arr", 0, 1);
  trace_array("arr", 1, 2);
  trace_array("arr", 2, 3);
  trace_array("arr", 3, 4);
  trace_array("arr", 4, 5);
  trace_line(5);
  int n = 5;
  trace_var_init("n", n);
  trace_line(6);
  int k = 2;
  trace_var_init("k", k);

  trace_line(8);
  for (int r = 0; r < k; r++) {
    trace_line(8);
    trace_var("r", r);
    trace_line(9);
    int first = arr[0];
    trace_var_init("first", first);
    trace_array_highlight("arr", 0);
    trace_line(10);
    for (int i = 0; i < n - 1; i++) {
      trace_line(10);
      trace_var("i", i);
      trace_line(11);
      arr[i] = arr[i + 1];
      trace_array("arr", i, arr[i]);
    }
    trace_line(13);
    arr[n - 1] = first;
    trace_array("arr", n - 1, arr[n - 1]);
  }

  trace_line(16);
  return 0;
}
