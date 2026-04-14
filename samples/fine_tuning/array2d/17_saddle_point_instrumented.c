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
  for (int i = 0; i < 3; i++) {
    trace_line(10);
    trace_var_init("i", i);
    trace_line(11);
    trace_array2d_highlight("m", i, 0);
    int maxVal = m[i][0];
    trace_var_init("maxVal", maxVal);
    trace_line(12);
    int maxCol = 0;
    trace_var_init("maxCol", 0);
    trace_line(13);
    for (int j = 1; j < 3; j++) {
      trace_line(13);
      trace_var_init("j", j);
      trace_line(14);
      trace_array2d_highlight("m", i, j);
      if (m[i][j] > maxVal) {
        trace_line(15);
        maxVal = m[i][j];
        trace_var("maxVal", maxVal);
        trace_line(16);
        maxCol = j;
        trace_var("maxCol", maxCol);
      }
    }

    trace_line(20);
    int isSaddle = 1;
    trace_var_init("isSaddle", 1);
    trace_line(21);
    for (int k = 0; k < 3; k++) {
      trace_line(21);
      trace_var_init("k", k);
      trace_line(22);
      trace_array2d_highlight("m", k, maxCol);
      if (m[k][maxCol] < maxVal) {
        trace_line(23);
        isSaddle = 0;
        trace_var("isSaddle", isSaddle);
      }
    }

    trace_line(27);
    if (isSaddle) {
      trace_line(28);
      printf("Saddle at (%d,%d) = %d\n", i, maxCol, maxVal);
    }
  }

  trace_line(32);
  return 0;
}
