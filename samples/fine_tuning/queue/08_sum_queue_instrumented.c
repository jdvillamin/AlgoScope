#include <stdio.h>

#include "tracer.h"

#define MAX 20

int main() {
  int queue[MAX];
  trace_line(7);
  int front = 0;
  trace_var_init("front", front);
  trace_line(8);
  int rear = -1;
  trace_var_init("rear", rear);
  trace_queue_init("Q");
  trace_line(9);
  int sum = 0;
  trace_var_init("sum", sum);

  trace_line(11);
  rear++;
  trace_var("rear", rear);
  trace_line(12);
  queue[rear] = 4;
  trace_queue_enqueue("Q", 4);

  trace_line(14);
  rear++;
  trace_var("rear", rear);
  trace_line(15);
  queue[rear] = 9;
  trace_queue_enqueue("Q", 9);

  trace_line(17);
  rear++;
  trace_var("rear", rear);
  trace_line(18);
  queue[rear] = 2;
  trace_queue_enqueue("Q", 2);

  trace_line(20);
  rear++;
  trace_var("rear", rear);
  trace_line(21);
  queue[rear] = 11;
  trace_queue_enqueue("Q", 11);

  trace_line(23);
  while (front <= rear) {
    trace_line(23);
    trace_line(24);
    sum += queue[front];
    trace_var("sum", sum);
    trace_queue_dequeue("Q");
    trace_line(25);
    front++;
    trace_var("front", front);
  }

  trace_line(28);
  printf("sum: %d\n", sum);

  trace_line(30);
  return 0;
}
