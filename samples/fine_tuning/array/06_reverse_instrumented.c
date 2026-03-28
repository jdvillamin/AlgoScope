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
  int left = 0;
  trace_var_init("left", left);
  trace_line(7);
  int right = n - 1;
  trace_var_init("right", right);

  trace_line(9);
  while (left < right) {
    trace_line(9);
    trace_array_highlight("arr", left);
    trace_line(10);
    int temp = arr[left];
    trace_line(11);
    arr[left] = arr[right];
    trace_array("arr", left, arr[left]);
    trace_line(12);
    arr[right] = temp;
    trace_array("arr", right, arr[right]);
    trace_line(13);
    left++;
    trace_var("left", left);
    trace_line(14);
    right--;
    trace_var("right", right);
  }

  trace_line(17);
  return 0;
}
