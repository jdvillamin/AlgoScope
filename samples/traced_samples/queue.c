#include <stdio.h>

#include "tracer.h"

#define MAX 10

int main() {
  trace_queue_init("Q");

  int queue[MAX];
  int front = 0, rear = -1;

  // enqueue 5
  rear++;
  trace_line(__LINE__ - 1);
  queue[rear] = 5;
  trace_line(__LINE__ - 1);
  trace_queue_enqueue("Q", 5);

  // enqueue 10
  rear++;
  trace_line(__LINE__ - 1);
  queue[rear] = 10;
  trace_line(__LINE__ - 1);
  trace_queue_enqueue("Q", 10);

  // enqueue 15
  rear++;
  trace_line(__LINE__ - 1);
  queue[rear] = 15;
  trace_line(__LINE__ - 1);
  trace_queue_enqueue("Q", 15);

  // dequeue
  trace_line(__LINE__ - 1);
  trace_queue_dequeue("Q");
  front++;
  trace_line(__LINE__ - 1);

  return 0;
}