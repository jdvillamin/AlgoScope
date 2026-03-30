#include <stdio.h>

#include "tracer.h"

int main() {
  int a[2][2] = {
    {1, 2},
    {3, 4}
  };
  trace_array2d_init("a", 2, 2);
  trace_array2d("a", 0, 0, 1);
  trace_array2d("a", 0, 1, 2);
  trace_array2d("a", 1, 0, 3);
  trace_array2d("a", 1, 1, 4);

  int b[2][2] = {
    {5, 6},
    {7, 8}
  };
  trace_array2d_init("b", 2, 2);
  trace_array2d("b", 0, 0, 5);
  trace_array2d("b", 0, 1, 6);
  trace_array2d("b", 1, 0, 7);
  trace_array2d("b", 1, 1, 8);

  int c[2][2];
  trace_array2d_init("c", 2, 2);

  trace_line(16);
  for (int i = 0; i < 2; i++) {
    trace_line(16);
    trace_line(17);
    for (int j = 0; j < 2; j++) {
      trace_line(17);
      trace_line(18);
      c[i][j] = 0;
      trace_array2d("c", i, j, 0);
      trace_line(19);
      for (int k = 0; k < 2; k++) {
        trace_line(19);
        trace_line(20);
        trace_array2d_highlight("a", i, k);
        trace_array2d_highlight("b", k, j);
        c[i][j] += a[i][k] * b[k][j];
        trace_array2d("c", i, j, c[i][j]);
      }
    }
  }

  trace_line(25);
  for (int i = 0; i < 2; i++) {
    trace_line(25);
    trace_line(26);
    for (int j = 0; j < 2; j++) {
      trace_line(26);
      trace_line(27);
      printf("%d ", c[i][j]);
    }
    trace_line(29);
    printf("\n");
  }

  trace_line(32);
  return 0;
}
