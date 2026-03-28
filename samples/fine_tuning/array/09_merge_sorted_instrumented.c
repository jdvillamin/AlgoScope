#include <stdio.h>

#include "tracer.h"

int main() {
  int a[3] = {1, 4, 7};
  trace_array_init("a", 3);
  trace_array("a", 0, 1);
  trace_array("a", 1, 4);
  trace_array("a", 2, 7);
  int b[3] = {2, 5, 8};
  trace_array_init("b", 3);
  trace_array("b", 0, 2);
  trace_array("b", 1, 5);
  trace_array("b", 2, 8);
  int merged[6];
  trace_array_init("merged", 6);
  trace_line(7);
  int i = 0, j = 0, k = 0;
  trace_var_init("i", i);
  trace_var_init("j", j);
  trace_var_init("k", k);

  trace_line(9);
  while (i < 3 && j < 3) {
    trace_line(9);
    trace_array_highlight("a", i);
    trace_line(10);
    if (a[i] <= b[j]) {
      trace_line(11);
      merged[k] = a[i];
      trace_array("merged", k, merged[k]);
      trace_line(12);
      i++;
      trace_var("i", i);
    } else {
      trace_line(14);
      merged[k] = b[j];
      trace_array("merged", k, merged[k]);
      trace_line(15);
      j++;
      trace_var("j", j);
    }
    trace_line(17);
    k++;
    trace_var("k", k);
  }

  trace_line(20);
  while (i < 3) {
    trace_line(20);
    trace_line(21);
    merged[k] = a[i];
    trace_array("merged", k, merged[k]);
    trace_line(22);
    i++;
    trace_var("i", i);
    trace_line(23);
    k++;
    trace_var("k", k);
  }

  trace_line(26);
  while (j < 3) {
    trace_line(26);
    trace_line(27);
    merged[k] = b[j];
    trace_array("merged", k, merged[k]);
    trace_line(28);
    j++;
    trace_var("j", j);
    trace_line(29);
    k++;
    trace_var("k", k);
  }

  trace_line(32);
  return 0;
}
