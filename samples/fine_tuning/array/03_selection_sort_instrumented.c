#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[5] = {8, 4, 2, 9, 1};
  trace_array_init("arr", 5);
  trace_array("arr", 0, 8);
  trace_array("arr", 1, 4);
  trace_array("arr", 2, 2);
  trace_array("arr", 3, 9);
  trace_array("arr", 4, 1);
  trace_line(5);
  int n = 5;
  trace_var_init("n", n);

  trace_line(7);
  for (int i = 0; i < n - 1; i++) {
    trace_line(7);
    trace_var("i", i);
    trace_line(8);
    int minIdx = i;
    trace_var_init("minIdx", minIdx);
    trace_line(9);
    for (int j = i + 1; j < n; j++) {
      trace_line(9);
      trace_var("j", j);
      trace_array_highlight("arr", j);
      trace_line(10);
      if (arr[j] < arr[minIdx]) {
        trace_line(11);
        minIdx = j;
        trace_var("minIdx", minIdx);
      }
    }
    trace_line(14);
    int temp = arr[i];
    trace_line(15);
    arr[i] = arr[minIdx];
    trace_array("arr", i, arr[i]);
    trace_line(16);
    arr[minIdx] = temp;
    trace_array("arr", minIdx, arr[minIdx]);
  }

  trace_line(19);
  return 0;
}
