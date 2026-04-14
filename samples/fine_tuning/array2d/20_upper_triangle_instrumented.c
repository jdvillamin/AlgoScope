#include <stdio.h>

#include "tracer.h"

int main() {
  int m[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  trace_array2d_init("m", 4, 4);
  for (int _r = 0; _r < 4; _r++)
    for (int _c = 0; _c < 4; _c++)
      trace_array2d("m", _r, _c, m[_r][_c]);

  int u[4][4];
  trace_array2d_init("u", 4, 4);

  trace_line(13);
  for (int i = 0; i < 4; i++) {
    trace_line(13);
    trace_var_init("i", i);
    trace_line(14);
    for (int j = 0; j < 4; j++) {
      trace_line(14);
      trace_var_init("j", j);
      trace_line(15);
      trace_array2d_highlight("m", i, j);
      if (j >= i) {
        trace_line(16);
        u[i][j] = m[i][j];
        trace_array2d("u", i, j, u[i][j]);
      } else {
        trace_line(18);
        u[i][j] = 0;
        trace_array2d("u", i, j, 0);
      }
    }
  }

  trace_line(23);
  for (int i = 0; i < 4; i++) {
    trace_line(23);
    trace_line(24);
    for (int j = 0; j < 4; j++) {
      trace_line(24);
      trace_line(25);
      printf("%d ", u[i][j]);
    }
    trace_line(27);
    printf("\n");
  }

  trace_line(30);
  return 0;
}
