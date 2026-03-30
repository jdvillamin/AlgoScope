#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  trace_array2d_init("mat", 3, 3);
  trace_array2d("mat", 0, 0, 1);
  trace_array2d("mat", 0, 1, 2);
  trace_array2d("mat", 0, 2, 3);
  trace_array2d("mat", 1, 0, 4);
  trace_array2d("mat", 1, 1, 5);
  trace_array2d("mat", 1, 2, 6);
  trace_array2d("mat", 2, 0, 7);
  trace_array2d("mat", 2, 1, 8);
  trace_array2d("mat", 2, 2, 9);

  trace_line(10);
  int sum = 0;
  trace_var_init("sum", sum);

  trace_line(12);
  for (int i = 0; i < 3; i++) {
    trace_line(12);
    trace_line(13);
    for (int j = 0; j < 3; j++) {
      trace_line(13);
      trace_line(14);
      trace_array2d_highlight("mat", i, j);
      if (i == 0 || i == 2 || j == 0 || j == 2) {
        trace_line(15);
        sum += mat[i][j];
        trace_var("sum", sum);
      }
    }
  }

  trace_line(20);
  printf("border sum: %d\n", sum);

  trace_line(22);
  return 0;
}
