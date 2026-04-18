#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
  trace_array2d_init("mat", 3, 3);
  trace_array2d("mat", 0, 0, 1);
  trace_array2d("mat", 0, 1, 0);
  trace_array2d("mat", 0, 2, 0);
  trace_array2d("mat", 1, 0, 0);
  trace_array2d("mat", 1, 1, 1);
  trace_array2d("mat", 1, 2, 0);
  trace_array2d("mat", 2, 0, 0);
  trace_array2d("mat", 2, 1, 0);
  trace_array2d("mat", 2, 2, 1);

  trace_line(10);
  int isIdentity = 1;
  trace_var_init("isIdentity", isIdentity);

  trace_line(12);
  for (int i = 0; i < 3; i++) {
    trace_line(12);
    trace_var_init("i", i);
    trace_line(13);
    for (int j = 0; j < 3; j++) {
      trace_line(13);
      trace_var_init("j", j);
      trace_line(14);
      trace_array2d_highlight("mat", i, j);
      if (i == j && mat[i][j] != 1) {
        trace_line(15);
        isIdentity = 0;
        trace_var("isIdentity", isIdentity);
      }
      trace_line(17);
      if (i != j && mat[i][j] != 0) {
        trace_line(18);
        isIdentity = 0;
        trace_var("isIdentity", isIdentity);
      }
    }
  }

  trace_line(23);
  if (isIdentity) {
    trace_line(24);
    printf("identity matrix\n");
  } else {
    trace_line(26);
    printf("not identity matrix\n");
  }

  trace_line(29);
  return 0;
}
