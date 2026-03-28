#include <stdio.h>

#include "tracer.h"

int main() {
  int arr[5] = {3, 7, 1, 9, 4};
  trace_array_init("arr", 5);
  trace_array("arr", 0, 3);
  trace_array("arr", 1, 7);
  trace_array("arr", 2, 1);
  trace_array("arr", 3, 9);
  trace_array("arr", 4, 4);
  trace_line(5);
  int target = 9;
  trace_var_init("target", target);
  trace_line(6);
  int found = -1;
  trace_var_init("found", found);

  trace_line(8);
  for (int i = 0; i < 5; i++) {
    trace_line(8);
    trace_var("i", i);
    trace_array_highlight("arr", i);
    trace_line(9);
    if (arr[i] == target) {
      trace_line(10);
      found = i;
      trace_var("found", found);
      trace_line(11);
      break;
    }
  }

  trace_line(15);
  if (found >= 0) {
    trace_line(16);
    printf("Found at index %d\n", found);
  } else {
    trace_line(18);
    printf("Not found\n");
  }

  trace_line(21);
  return 0;
}
