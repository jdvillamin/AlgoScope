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
  int n;

  trace_line(11);
  scanf("%d", &n);
  trace_var_init("n", n);

  trace_line(13);
  for (int i = 0; i < n; i++) {
    trace_line(13);
    trace_var_init("i", i);
    trace_line(14);
    int val;
    trace_line(15);
    scanf("%d", &val);
    trace_var_init("val", val);
    trace_line(16);
    rear++;
    trace_var("rear", rear);
    trace_line(17);
    queue[rear] = val;
    trace_queue_enqueue("Q", val);
  }

  trace_line(20);
  while (front <= rear) {
    trace_line(20);
    trace_line(21);
    printf("%d ", queue[front]);
    trace_queue_dequeue("Q");
    trace_line(22);
    front++;
    trace_var("front", front);
  }
  trace_line(24);
  printf("\n");

  trace_line(26);
  return 0;
}
