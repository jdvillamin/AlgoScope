#include <stdio.h>

#include "tracer.h"

int main() {
  int mat[3][3] = {
    {4, 8, 2},
    {6, 1, 9},
    {3, 7, 5}
  };
  trace_array2d_init("mat", 3, 3);
  trace_array2d("mat", 0, 0, 4);
  trace_array2d("mat", 0, 1, 8);
  trace_array2d("mat", 0, 2, 2);
  trace_array2d("mat", 1, 0, 6);
  trace_array2d("mat", 1, 1, 1);
  trace_array2d("mat", 1, 2, 9);
  trace_array2d("mat", 2, 0, 3);
  trace_array2d("mat", 2, 1, 7);
  trace_array2d("mat", 2, 2, 5);

  trace_line(10);
  int target = 9;
  trace_var_init("target", target);
  trace_line(11);
  int found = 0;
  trace_var_init("found", found);

  trace_line(13);
  for (int i = 0; i < 3; i++) {
    trace_line(13);
    trace_line(14);
    for (int j = 0; j < 3; j++) {
      trace_line(14);
      trace_line(15);
      trace_array2d_highlight("mat", i, j);
      if (mat[i][j] == target) {
        trace_line(16);
        printf("found %d at (%d, %d)\n", target, i, j);
        trace_line(17);
        found = 1;
        trace_var("found", found);
      }
    }
  }

  trace_line(22);
  if (!found) {
    trace_line(23);
    printf("%d not found\n", target);
  }

  trace_line(26);
  return 0;
}
