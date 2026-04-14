#include <stdio.h>

#include "tracer.h"

int main() {
  int m[3][3] = {
    {3, 7, 2},
    {8, 1, 5},
    {4, 9, 6}
  };
  trace_array2d_init("m", 3, 3);
  trace_array2d("m", 0, 0, 3);
  trace_array2d("m", 0, 1, 7);
  trace_array2d("m", 0, 2, 2);
  trace_array2d("m", 1, 0, 8);
  trace_array2d("m", 1, 1, 1);
  trace_array2d("m", 1, 2, 5);
  trace_array2d("m", 2, 0, 4);
  trace_array2d("m", 2, 1, 9);
  trace_array2d("m", 2, 2, 6);

  trace_line(10);
  for (int i = 0; i < 3; i++) {
    trace_line(10);
    trace_var_init("i", i);
    trace_line(11);
    trace_array2d_highlight("m", i, 0);
    int max = m[i][0];
    trace_var_init("max", max);
    trace_line(12);
    for (int j = 1; j < 3; j++) {
      trace_line(12);
      trace_var_init("j", j);
      trace_line(13);
      trace_array2d_highlight("m", i, j);
      if (m[i][j] > max) {
        trace_line(14);
        max = m[i][j];
        trace_var("max", max);
      }
    }
    trace_line(17);
    printf("Row %d max: %d\n", i, max);
  }

  trace_line(20);
  return 0;
}
