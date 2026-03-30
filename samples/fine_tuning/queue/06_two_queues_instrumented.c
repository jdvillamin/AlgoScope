#include <stdio.h>

#include "tracer.h"

#define MAX 20

int main() {
  int q1[MAX];
  trace_line(7);
  int front1 = 0;
  trace_var_init("front1", front1);
  trace_line(8);
  int rear1 = -1;
  trace_var_init("rear1", rear1);
  trace_queue_init("Q1");

  int q2[MAX];
  trace_line(11);
  int front2 = 0;
  trace_var_init("front2", front2);
  trace_line(12);
  int rear2 = -1;
  trace_var_init("rear2", rear2);
  trace_queue_init("Q2");

  trace_line(14);
  rear1++;
  trace_var("rear1", rear1);
  trace_line(15);
  q1[rear1] = 2;
  trace_queue_enqueue("Q1", 2);

  trace_line(17);
  rear1++;
  trace_var("rear1", rear1);
  trace_line(18);
  q1[rear1] = 4;
  trace_queue_enqueue("Q1", 4);

  trace_line(20);
  rear1++;
  trace_var("rear1", rear1);
  trace_line(21);
  q1[rear1] = 6;
  trace_queue_enqueue("Q1", 6);

  trace_line(23);
  rear2++;
  trace_var("rear2", rear2);
  trace_line(24);
  q2[rear2] = 1;
  trace_queue_enqueue("Q2", 1);

  trace_line(26);
  rear2++;
  trace_var("rear2", rear2);
  trace_line(27);
  q2[rear2] = 3;
  trace_queue_enqueue("Q2", 3);

  trace_line(29);
  rear2++;
  trace_var("rear2", rear2);
  trace_line(30);
  q2[rear2] = 5;
  trace_queue_enqueue("Q2", 5);

  trace_line(32);
  printf("Q1: ");
  trace_line(33);
  while (front1 <= rear1) {
    trace_line(33);
    trace_line(34);
    printf("%d ", q1[front1]);
    trace_queue_dequeue("Q1");
    trace_line(35);
    front1++;
    trace_var("front1", front1);
  }
  trace_line(37);
  printf("\n");

  trace_line(39);
  printf("Q2: ");
  trace_line(40);
  while (front2 <= rear2) {
    trace_line(40);
    trace_line(41);
    printf("%d ", q2[front2]);
    trace_queue_dequeue("Q2");
    trace_line(42);
    front2++;
    trace_var("front2", front2);
  }
  trace_line(44);
  printf("\n");

  trace_line(46);
  return 0;
}
