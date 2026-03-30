#include <stdio.h>

#include "tracer.h"

#define MAX 20

int main() {
  int q1[MAX];
  trace_line(7);
  int f1 = 0;
  trace_var_init("f1", f1);
  trace_line(8);
  int r1 = -1;
  trace_var_init("r1", r1);
  trace_queue_init("Q1");

  int q2[MAX];
  trace_line(11);
  int f2 = 0;
  trace_var_init("f2", f2);
  trace_line(12);
  int r2 = -1;
  trace_var_init("r2", r2);
  trace_queue_init("Q2");

  int result[MAX];
  trace_line(15);
  int fr = 0;
  trace_var_init("fr", fr);
  trace_line(16);
  int rr = -1;
  trace_var_init("rr", rr);
  trace_queue_init("Result");

  trace_line(18);
  r1++;
  trace_var("r1", r1);
  trace_line(19);
  q1[r1] = 1;
  trace_queue_enqueue("Q1", 1);

  trace_line(21);
  r1++;
  trace_var("r1", r1);
  trace_line(22);
  q1[r1] = 3;
  trace_queue_enqueue("Q1", 3);

  trace_line(24);
  r1++;
  trace_var("r1", r1);
  trace_line(25);
  q1[r1] = 5;
  trace_queue_enqueue("Q1", 5);

  trace_line(27);
  r2++;
  trace_var("r2", r2);
  trace_line(28);
  q2[r2] = 2;
  trace_queue_enqueue("Q2", 2);

  trace_line(30);
  r2++;
  trace_var("r2", r2);
  trace_line(31);
  q2[r2] = 4;
  trace_queue_enqueue("Q2", 4);

  trace_line(33);
  r2++;
  trace_var("r2", r2);
  trace_line(34);
  q2[r2] = 6;
  trace_queue_enqueue("Q2", 6);

  trace_line(36);
  while (f1 <= r1 && f2 <= r2) {
    trace_line(36);
    trace_line(37);
    rr++;
    trace_var("rr", rr);
    trace_line(38);
    result[rr] = q1[f1];
    trace_queue_dequeue("Q1");
    trace_queue_enqueue("Result", q1[f1]);
    trace_line(39);
    f1++;
    trace_var("f1", f1);
    trace_line(40);
    rr++;
    trace_var("rr", rr);
    trace_line(41);
    result[rr] = q2[f2];
    trace_queue_dequeue("Q2");
    trace_queue_enqueue("Result", q2[f2]);
    trace_line(42);
    f2++;
    trace_var("f2", f2);
  }

  trace_line(45);
  while (f1 <= r1) {
    trace_line(45);
    trace_line(46);
    rr++;
    trace_var("rr", rr);
    trace_line(47);
    result[rr] = q1[f1];
    trace_queue_dequeue("Q1");
    trace_queue_enqueue("Result", q1[f1]);
    trace_line(48);
    f1++;
    trace_var("f1", f1);
  }

  trace_line(51);
  while (f2 <= r2) {
    trace_line(51);
    trace_line(52);
    rr++;
    trace_var("rr", rr);
    trace_line(53);
    result[rr] = q2[f2];
    trace_queue_dequeue("Q2");
    trace_queue_enqueue("Result", q2[f2]);
    trace_line(54);
    f2++;
    trace_var("f2", f2);
  }

  trace_line(57);
  while (fr <= rr) {
    trace_line(57);
    trace_line(58);
    printf("%d ", result[fr]);
    trace_queue_dequeue("Result");
    trace_line(59);
    fr++;
    trace_var("fr", fr);
  }
  trace_line(61);
  printf("\n");

  trace_line(63);
  return 0;
}
