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

  trace_line(10);
  rear++;
  trace_var("rear", rear);
  trace_line(11);
  queue[rear] = 7;
  trace_queue_enqueue("Q", 7);

  trace_line(13);
  rear++;
  trace_var("rear", rear);
  trace_line(14);
  queue[rear] = 14;
  trace_queue_enqueue("Q", 14);

  trace_line(16);
  printf("dequeued: %d\n", queue[front]);
  trace_queue_dequeue("Q");
  trace_line(17);
  front++;
  trace_var("front", front);

  trace_line(19);
  printf("dequeued: %d\n", queue[front]);
  trace_queue_dequeue("Q");
  trace_line(20);
  front++;
  trace_var("front", front);

  trace_line(22);
  if (front > rear) {
    trace_line(23);
    printf("queue is empty\n");
  } else {
    trace_line(25);
    printf("queue is not empty\n");
  }

  trace_line(28);
  return 0;
}
