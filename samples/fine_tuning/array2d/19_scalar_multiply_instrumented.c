#include <stdio.h>

#include "tracer.h"

int main() {
  int m[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  trace_array2d_init("m", 3, 3);
  trace_array2d("m", 0, 0, 1);
  trace_array2d("m", 0, 1, 2);
  trace_array2d("m", 0, 2, 3);
  trace_array2d("m", 1, 0, 4);
  trace_array2d("m", 1, 1, 5);
  trace_array2d("m", 1, 2, 6);
  trace_array2d("m", 2, 0, 7);
  trace_array2d("m", 2, 1, 8);
  trace_array2d("m", 2, 2, 9);

  trace_line(10);
  int scalar = 3;
  trace_var_init("scalar", 3);

  trace_line(12);
  for (int i = 0; i < 3; i++) {
    trace_line(12);
    trace_var_init("i", i);
    trace_line(13);
    for (int j = 0; j < 3; j++) {
      trace_line(13);
      trace_var_init("j", j);
      trace_line(14);
      trace_array2d_highlight("m", i, j);
      m[i][j] = m[i][j] * scalar;
      trace_array2d("m", i, j, m[i][j]);
    }
  }

  trace_line(18);
  for (int i = 0; i < 3; i++) {
    trace_line(18);
    trace_line(19);
    for (int j = 0; j < 3; j++) {
      trace_line(19);
      trace_line(20);
      printf("%d ", m[i][j]);
    }
    trace_line(22);
    printf("\n");
  }

  trace_line(25);
  return 0;
}
