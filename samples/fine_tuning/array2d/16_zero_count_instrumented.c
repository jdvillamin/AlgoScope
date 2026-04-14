#include <stdio.h>

#include "tracer.h"

int main() {
  int m[3][3] = {
    {0, 2, 0},
    {4, 0, 6},
    {0, 8, 0}
  };
  trace_array2d_init("m", 3, 3);
  trace_array2d("m", 0, 0, 0);
  trace_array2d("m", 0, 1, 2);
  trace_array2d("m", 0, 2, 0);
  trace_array2d("m", 1, 0, 4);
  trace_array2d("m", 1, 1, 0);
  trace_array2d("m", 1, 2, 6);
  trace_array2d("m", 2, 0, 0);
  trace_array2d("m", 2, 1, 8);
  trace_array2d("m", 2, 2, 0);

  trace_line(10);
  int count = 0;
  trace_var_init("count", 0);
  trace_line(11);
  for (int i = 0; i < 3; i++) {
    trace_line(11);
    trace_var_init("i", i);
    trace_line(12);
    for (int j = 0; j < 3; j++) {
      trace_line(12);
      trace_var_init("j", j);
      trace_line(13);
      trace_array2d_highlight("m", i, j);
      if (m[i][j] == 0) {
        trace_line(14);
        count++;
        trace_var("count", count);
      }
    }
  }

  trace_line(19);
  printf("Zeros: %d\n", count);

  trace_line(21);
  return 0;
}
