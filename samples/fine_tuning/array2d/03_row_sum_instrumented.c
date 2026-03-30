#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
  };
  trace_array2d_init("mat", 3, 4);
  trace_array2d("mat", 0, 0, 1);
  trace_array2d("mat", 0, 1, 2);
  trace_array2d("mat", 0, 2, 3);
  trace_array2d("mat", 0, 3, 4);
  trace_array2d("mat", 1, 0, 5);
  trace_array2d("mat", 1, 1, 6);
  trace_array2d("mat", 1, 2, 7);
  trace_array2d("mat", 1, 3, 8);
  trace_array2d("mat", 2, 0, 9);
  trace_array2d("mat", 2, 1, 10);
  trace_array2d("mat", 2, 2, 11);
  trace_array2d("mat", 2, 3, 12);

  trace_line(10);
  for (int i = 0; i < 3; i++) {
    trace_line(10);
    trace_line(11);
    int sum = 0;
    trace_var_init("sum", sum);
    trace_line(12);
    for (int j = 0; j < 4; j++) {
      trace_line(12);
      trace_line(13);
      trace_array2d_highlight("mat", i, j);
      sum += mat[i][j];
      trace_var("sum", sum);
    }
    trace_line(15);
    printf("row %d sum: %d\n", i, sum);
  }

  trace_line(18);
  return 0;
}
