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
  queue[rear] = 8;
  trace_queue_enqueue("Q", 8);

  trace_line(13);
  rear++;
  trace_var("rear", rear);
  trace_line(14);
  queue[rear] = 12;
  trace_queue_enqueue("Q", 12);

  trace_line(16);
  rear++;
  trace_var("rear", rear);
  trace_line(17);
  queue[rear] = 4;
  trace_queue_enqueue("Q", 4);

  trace_line(19);
  printf("front: %d\n", queue[front]);
  trace_queue_front("Q", queue[front]);

  trace_line(21);
  printf("dequeued: %d\n", queue[front]);
  trace_queue_dequeue("Q");
  trace_line(22);
  front++;
  trace_var("front", front);

  trace_line(24);
  printf("front: %d\n", queue[front]);
  trace_queue_front("Q", queue[front]);

  trace_line(26);
  return 0;
}
