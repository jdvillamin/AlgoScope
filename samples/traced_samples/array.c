#include "tracer.h"

int main() {
  // ---- Create 1D array ----
  int arr[5];
  trace_line(__LINE__ - 1);
  trace_array_init("arr", 5);

  // ---- Initialize variable ----
  int i = 0;
  trace_line(__LINE__ - 1);
  trace_var_init("i", i);
  trace_array_cell("arr", "i", i);

  // ---- Simple loop ----
  for (i = 0; i < 5; i++) {
    trace_line(__LINE__ - 1);
    trace_var("i", i);
    trace_array_cell("arr", "i", i);

    arr[i] = i * i;
    trace_line(__LINE__ - 1);
    trace_array("arr", i, arr[i]);
  }

  return 0;
}
