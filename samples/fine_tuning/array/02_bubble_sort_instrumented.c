#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[5] = {5, 3, 8, 1, 2};
  trace_array_init_bars("arr", 5);
  trace_array("arr", 0, 5);
  trace_array("arr", 1, 3);
  trace_array("arr", 2, 8);
  trace_array("arr", 3, 1);
  trace_array("arr", 4, 2);
  trace_line(5);
  int n = 5;
  trace_var_init("n", n);

  trace_line(7);
  for (int i = 0; i < n - 1; i++) {
    trace_line(7);
    trace_var("i", i);
    trace_line(8);
    for (int j = 0; j < n - 1 - i; j++) {
      trace_line(8);
      trace_var("j", j);
      trace_array_highlight("arr", j);
      trace_line(9);
      if (arr[j] > arr[j + 1]) {
        trace_line(10);
        int temp = arr[j];
        trace_line(11);
        arr[j] = arr[j + 1];
        trace_array("arr", j, arr[j]);
        trace_line(12);
        arr[j + 1] = temp;
        trace_array("arr", j + 1, arr[j + 1]);
      }
    }
  }

  trace_line(17);
  return 0;
}
