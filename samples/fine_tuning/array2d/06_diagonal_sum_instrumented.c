#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][3] = {
    {5, 2, 8},
    {1, 7, 3},
    {4, 6, 9}
  };
  trace_array2d_init("mat", 3, 3);
  trace_array2d("mat", 0, 0, 5);
  trace_array2d("mat", 0, 1, 2);
  trace_array2d("mat", 0, 2, 8);
  trace_array2d("mat", 1, 0, 1);
  trace_array2d("mat", 1, 1, 7);
  trace_array2d("mat", 1, 2, 3);
  trace_array2d("mat", 2, 0, 4);
  trace_array2d("mat", 2, 1, 6);
  trace_array2d("mat", 2, 2, 9);

  trace_line(10);
  int sum = 0;
  trace_var_init("sum", sum);

  trace_line(12);
  for (int i = 0; i < 3; i++) {
    trace_line(12);
    trace_line(13);
    trace_array2d_highlight("mat", i, i);
    sum += mat[i][i];
    trace_var("sum", sum);
  }

  trace_line(16);
  printf("diagonal sum: %d\n", sum);

  trace_line(18);
  return 0;
}
