#include <stdio.h>

#include "tracer.h"

int main() {
  int a[3][3] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
  };
  trace_array2d_init("a", 3, 3);
  trace_array2d("a", 0, 0, 9);
  trace_array2d("a", 0, 1, 8);
  trace_array2d("a", 0, 2, 7);
  trace_array2d("a", 1, 0, 6);
  trace_array2d("a", 1, 1, 5);
  trace_array2d("a", 1, 2, 4);
  trace_array2d("a", 2, 0, 3);
  trace_array2d("a", 2, 1, 2);
  trace_array2d("a", 2, 2, 1);

  int b[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  trace_array2d_init("b", 3, 3);
  trace_array2d("b", 0, 0, 1);
  trace_array2d("b", 0, 1, 2);
  trace_array2d("b", 0, 2, 3);
  trace_array2d("b", 1, 0, 4);
  trace_array2d("b", 1, 1, 5);
  trace_array2d("b", 1, 2, 6);
  trace_array2d("b", 2, 0, 7);
  trace_array2d("b", 2, 1, 8);
  trace_array2d("b", 2, 2, 9);

  int c[3][3];
  trace_array2d_init("c", 3, 3);

  trace_line(18);
  for (int i = 0; i < 3; i++) {
    trace_line(18);
    trace_var_init("i", i);
    trace_line(19);
    for (int j = 0; j < 3; j++) {
      trace_line(19);
      trace_var_init("j", j);
      trace_line(20);
      trace_array2d_highlight("a", i, j);
      trace_array2d_highlight("b", i, j);
      c[i][j] = a[i][j] - b[i][j];
      trace_array2d("c", i, j, c[i][j]);
    }
  }

  trace_line(24);
  for (int i = 0; i < 3; i++) {
    trace_line(24);
    trace_var_init("i", i);
    trace_line(25);
    for (int j = 0; j < 3; j++) {
      trace_line(25);
      trace_var_init("j", j);
      trace_line(26);
      printf("%d ", c[i][j]);
    }
    trace_line(28);
    printf("\n");
  }

  trace_line(31);
  return 0;
}
