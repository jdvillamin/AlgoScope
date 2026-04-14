#include <stdio.h>

#include "tracer.h"

int main() {
  int m[3][3] = {
    {5, 9, 2},
    {8, 3, 7},
    {1, 6, 4}
  };
  trace_array2d_init("m", 3, 3);
  trace_array2d("m", 0, 0, 5);
  trace_array2d("m", 0, 1, 9);
  trace_array2d("m", 0, 2, 2);
  trace_array2d("m", 1, 0, 8);
  trace_array2d("m", 1, 1, 3);
  trace_array2d("m", 1, 2, 7);
  trace_array2d("m", 2, 0, 1);
  trace_array2d("m", 2, 1, 6);
  trace_array2d("m", 2, 2, 4);

  trace_line(10);
  for (int j = 0; j < 3; j++) {
    trace_line(10);
    trace_var_init("j", j);
    trace_line(11);
    trace_array2d_highlight("m", 0, j);
    int min = m[0][j];
    trace_var_init("min", min);
    trace_line(12);
    for (int i = 1; i < 3; i++) {
      trace_line(12);
      trace_var_init("i", i);
      trace_line(13);
      trace_array2d_highlight("m", i, j);
      if (m[i][j] < min) {
        trace_line(14);
        min = m[i][j];
        trace_var("min", min);
      }
    }
    trace_line(17);
    printf("Col %d min: %d\n", j, min);
  }

  trace_line(20);
  return 0;
}
