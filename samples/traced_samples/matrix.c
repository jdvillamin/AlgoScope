#include "tracer.h"

int main() {
  // ---- Create 2D array ----
  int mat[3][5];
  trace_line(__LINE__ - 1);
  trace_array2d_init("mat", 3, 5);

  // ---- Declare r and c ----
  int r = 0;
  trace_line(__LINE__ - 1);
  trace_var_init("r", r);

  int c = 0;
  trace_line(__LINE__ - 1);
  trace_var_init("c", c);

  // ---- Fill matrix ----
  for (r = 0; r < 3; r++) {
    trace_line(__LINE__ - 1);
    trace_var("r", r);

    for (c = 0; c < 5; c++) {
      trace_line(__LINE__ - 1);
      trace_var("c", c);

      mat[r][c] = (r + 1) * (c + 1);
      trace_line(__LINE__ - 1);
      trace_array2d("mat", r, c, mat[r][c]);
    }
  }

  return 0;
}
