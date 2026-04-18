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
  queue[rear] = 1;
  trace_queue_enqueue("Q", 1);

  trace_line(13);
  rear++;
  trace_var("rear", rear);
  trace_line(14);
  queue[rear] = 2;
  trace_queue_enqueue("Q", 2);

  trace_line(16);
  rear++;
  trace_var("rear", rear);
  trace_line(17);
  queue[rear] = 3;
  trace_queue_enqueue("Q", 3);

  trace_line(19);
  rear++;
  trace_var("rear", rear);
  trace_line(20);
  queue[rear] = 4;
  trace_queue_enqueue("Q", 4);

  int temp[MAX];
  trace_line(23);
  int count = rear - front + 1;
  trace_var_init("count", count);

  trace_line(25);
  for (int i = 0; i < count; i++) {
    trace_line(25);
    trace_var_init("i", i);
    trace_line(26);
    temp[i] = queue[front];
    trace_queue_dequeue("Q");
    trace_line(27);
    front++;
    trace_var("front", front);
  }

  trace_line(30);
  front = 0;
  trace_var("front", front);
  trace_line(31);
  rear = -1;
  trace_var("rear", rear);

  trace_line(33);
  for (int i = count - 1; i >= 0; i--) {
    trace_line(33);
    trace_var_init("i", i);
    trace_line(34);
    rear++;
    trace_var("rear", rear);
    trace_line(35);
    queue[rear] = temp[i];
    trace_queue_enqueue("Q", temp[i]);
  }

  trace_line(38);
  while (front <= rear) {
    trace_line(38);
    trace_line(39);
    printf("%d ", queue[front]);
    trace_queue_dequeue("Q");
    trace_line(40);
    front++;
    trace_var("front", front);
  }
  trace_line(42);
  printf("\n");

  trace_line(44);
  return 0;
}
