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
  int top = 0, bottom = 2, left = 0, right = 2;
  trace_var_init("top", 0);
  trace_var_init("bottom", 2);
  trace_var_init("left", 0);
  trace_var_init("right", 2);

  trace_line(12);
  while (top <= bottom && left <= right) {
    trace_line(12);
    trace_line(13);
    for (int i = left; i <= right; i++) {
      trace_line(13);
      trace_var_init("i", i);
      trace_line(14);
      trace_array2d_highlight("m", top, i);
      printf("%d ", m[top][i]);
    }
    trace_line(16);
    top++;
    trace_var("top", top);

    trace_line(18);
    for (int i = top; i <= bottom; i++) {
      trace_line(18);
      trace_var_init("i", i);
      trace_line(19);
      trace_array2d_highlight("m", i, right);
      printf("%d ", m[i][right]);
    }
    trace_line(21);
    right--;
    trace_var("right", right);

    trace_line(23);
    if (top <= bottom) {
      trace_line(24);
      for (int i = right; i >= left; i--) {
        trace_line(24);
        trace_var_init("i", i);
        trace_line(25);
        trace_array2d_highlight("m", bottom, i);
        printf("%d ", m[bottom][i]);
      }
      trace_line(27);
      bottom--;
      trace_var("bottom", bottom);
    }

    trace_line(30);
    if (left <= right) {
      trace_line(31);
      for (int i = bottom; i >= top; i--) {
        trace_line(31);
        trace_var_init("i", i);
        trace_line(32);
        trace_array2d_highlight("m", i, left);
        printf("%d ", m[i][left]);
      }
      trace_line(34);
      left++;
      trace_var("left", left);
    }
  }

  trace_line(38);
  printf("\n");

  trace_line(40);
  return 0;
}
