#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  int src[MAX], tmp[MAX], dst[MAX];
  trace_line(7);
  int srcTop = -1, tmpTop = -1, dstTop = -1;
  trace_var_init("srcTop", srcTop);
  trace_var_init("tmpTop", tmpTop);
  trace_var_init("dstTop", dstTop);
  trace_stack_init("Src");
  trace_stack_init("Tmp");
  trace_stack_init("Dst");

  trace_line(9);
  srcTop++; src[srcTop] = 1;
  trace_var("srcTop", srcTop);
  trace_stack_push("Src", 1);
  trace_line(10);
  srcTop++; src[srcTop] = 2;
  trace_var("srcTop", srcTop);
  trace_stack_push("Src", 2);
  trace_line(11);
  srcTop++; src[srcTop] = 3;
  trace_var("srcTop", srcTop);
  trace_stack_push("Src", 3);

  trace_line(13);
  while (srcTop >= 0) {
    trace_line(13);
    trace_line(14);
    tmpTop++;
    trace_var("tmpTop", tmpTop);
    trace_line(15);
    tmp[tmpTop] = src[srcTop];
    trace_stack_push("Tmp", src[srcTop]);
    trace_stack_pop("Src");
    trace_line(16);
    srcTop--;
    trace_var("srcTop", srcTop);
  }

  trace_line(19);
  while (tmpTop >= 0) {
    trace_line(19);
    trace_line(20);
    dstTop++;
    trace_var("dstTop", dstTop);
    trace_line(21);
    dst[dstTop] = tmp[tmpTop];
    trace_stack_push("Dst", tmp[tmpTop]);
    trace_stack_pop("Tmp");
    trace_line(22);
    tmpTop--;
    trace_var("tmpTop", tmpTop);
  }

  trace_line(25);
  return 0;
}
