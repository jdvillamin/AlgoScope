#include <stdio.h>

#include "tracer.h"

int main() {
  int m[4][4] = {
    {5, 1, 2, 3},
    {4, 8, 6, 7},
    {9, 0, 3, 1},
    {2, 4, 7, 6}
  };
  trace_array2d_init("m", 4, 4);
  trace_array2d("m", 0, 0, 5);
  trace_array2d("m", 0, 1, 1);
  trace_array2d("m", 0, 2, 2);
  trace_array2d("m", 0, 3, 3);
  trace_array2d("m", 1, 0, 4);
  trace_array2d("m", 1, 1, 8);
  trace_array2d("m", 1, 2, 6);
  trace_array2d("m", 1, 3, 7);
  trace_array2d("m", 2, 0, 9);
  trace_array2d("m", 2, 1, 0);
  trace_array2d("m", 2, 2, 3);
  trace_array2d("m", 2, 3, 1);
  trace_array2d("m", 3, 0, 2);
  trace_array2d("m", 3, 1, 4);
  trace_array2d("m", 3, 2, 7);
  trace_array2d("m", 3, 3, 6);

  trace_line(11);
  int trace_val = 0;
  trace_var_init("trace", 0);
  trace_line(12);
  for (int i = 0; i < 4; i++) {
    trace_line(12);
    trace_var_init("i", i);
    trace_line(13);
    trace_array2d_highlight("m", i, i);
    trace_val += m[i][i];
    trace_var("trace", trace_val);
  }

  trace_line(16);
  printf("Trace: %d\n", trace_val);

  trace_line(18);
  return 0;
}
