#include <stdio.h>

#include "tracer.h"

int main() {
  int m[3][3] = {
    {1, 2, 3},
    {2, 5, 6},
    {3, 6, 9}
  };
  trace_array2d_init("m", 3, 3);
  trace_array2d("m", 0, 0, 1);
  trace_array2d("m", 0, 1, 2);
  trace_array2d("m", 0, 2, 3);
  trace_array2d("m", 1, 0, 2);
  trace_array2d("m", 1, 1, 5);
  trace_array2d("m", 1, 2, 6);
  trace_array2d("m", 2, 0, 3);
  trace_array2d("m", 2, 1, 6);
  trace_array2d("m", 2, 2, 9);

  trace_line(10);
  int symmetric = 1;
  trace_var_init("symmetric", 1);
  trace_line(11);
  for (int i = 0; i < 3; i++) {
    trace_line(11);
    trace_var_init("i", i);
    trace_line(12);
    for (int j = 0; j < i; j++) {
      trace_line(12);
      trace_var_init("j", j);
      trace_line(13);
      trace_array2d_highlight("m", i, j);
      trace_array2d_highlight("m", j, i);
      if (m[i][j] != m[j][i]) {
        trace_line(14);
        symmetric = 0;
        trace_var("symmetric", symmetric);
      }
    }
  }

  trace_line(19);
  if (symmetric) {
    trace_line(20);
    printf("Matrix is symmetric\n");
  } else {
    trace_line(22);
    printf("Matrix is not symmetric\n");
  }

  trace_line(25);
  return 0;
}
