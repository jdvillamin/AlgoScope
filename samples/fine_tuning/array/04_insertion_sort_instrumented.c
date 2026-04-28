#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[5] = {7, 3, 5, 1, 9};
  trace_array_init_bars("arr", 5);
  trace_array("arr", 0, 7);
  trace_array("arr", 1, 3);
  trace_array("arr", 2, 5);
  trace_array("arr", 3, 1);
  trace_array("arr", 4, 9);
  trace_line(5);
  int n = 5;
  trace_var_init("n", n);

  trace_line(7);
  for (int i = 1; i < n; i++) {
    trace_line(7);
    trace_var("i", i);
    trace_line(8);
    int key = arr[i];
    trace_var_init("key", key);
    trace_array_highlight("arr", i);
    trace_line(9);
    int j = i - 1;
    trace_var_init("j", j);
    trace_line(10);
    while (j >= 0 && arr[j] > key) {
      trace_line(10);
      trace_array_highlight("arr", j);
      trace_line(11);
      arr[j + 1] = arr[j];
      trace_array("arr", j + 1, arr[j + 1]);
      trace_line(12);
      j--;
      trace_var("j", j);
    }
    trace_line(14);
    arr[j + 1] = key;
    trace_array("arr", j + 1, arr[j + 1]);
  }

  trace_line(17);
  return 0;
}
