#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][3] = {
    {3, 7, 2},
    {9, 1, 8},
    {4, 6, 5}
  };
  trace_array2d_init("mat", 3, 3);
  trace_array2d("mat", 0, 0, 3);
  trace_array2d("mat", 0, 1, 7);
  trace_array2d("mat", 0, 2, 2);
  trace_array2d("mat", 1, 0, 9);
  trace_array2d("mat", 1, 1, 1);
  trace_array2d("mat", 1, 2, 8);
  trace_array2d("mat", 2, 0, 4);
  trace_array2d("mat", 2, 1, 6);
  trace_array2d("mat", 2, 2, 5);

  trace_line(10);
  int max = mat[0][0];
  trace_var_init("max", max);

  trace_line(12);
  for (int i = 0; i < 3; i++) {
    trace_line(12);
    trace_line(13);
    for (int j = 0; j < 3; j++) {
      trace_line(13);
      trace_line(14);
      trace_array2d_highlight("mat", i, j);
      if (mat[i][j] > max) {
        trace_line(15);
        max = mat[i][j];
        trace_var("max", max);
      }
    }
  }

  trace_line(20);
  printf("max: %d\n", max);

  trace_line(22);
  return 0;
}
