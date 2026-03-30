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
  queue[rear] = 3;
  trace_queue_enqueue("Q", 3);

  trace_line(13);
  rear++;
  trace_var("rear", rear);
  trace_line(14);
  queue[rear] = 7;
  trace_queue_enqueue("Q", 7);

  trace_line(16);
  rear++;
  trace_var("rear", rear);
  trace_line(17);
  queue[rear] = 11;
  trace_queue_enqueue("Q", 11);

  trace_line(19);
  rear++;
  trace_var("rear", rear);
  trace_line(20);
  queue[rear] = 15;
  trace_queue_enqueue("Q", 15);

  trace_line(22);
  rear++;
  trace_var("rear", rear);
  trace_line(23);
  queue[rear] = 19;
  trace_queue_enqueue("Q", 19);

  trace_line(25);
  while (front <= rear) {
    trace_line(25);
    trace_line(26);
    printf("%d ", queue[front]);
    trace_queue_dequeue("Q");
    trace_line(27);
    front++;
    trace_var("front", front);
  }
  trace_line(29);
  printf("\n");

  trace_line(31);
  return 0;
}
