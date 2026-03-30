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

  int even[MAX];
  trace_line(11);
  int efront = 0;
  trace_var_init("efront", efront);
  trace_line(12);
  int erear = -1;
  trace_var_init("erear", erear);
  trace_queue_init("Even");

  int odd[MAX];
  trace_line(15);
  int ofront = 0;
  trace_var_init("ofront", ofront);
  trace_line(16);
  int orear = -1;
  trace_var_init("orear", orear);
  trace_queue_init("Odd");

  trace_line(18);
  rear++;
  trace_var("rear", rear);
  trace_line(19);
  queue[rear] = 3;
  trace_queue_enqueue("Q", 3);

  trace_line(21);
  rear++;
  trace_var("rear", rear);
  trace_line(22);
  queue[rear] = 8;
  trace_queue_enqueue("Q", 8);

  trace_line(24);
  rear++;
  trace_var("rear", rear);
  trace_line(25);
  queue[rear] = 5;
  trace_queue_enqueue("Q", 5);

  trace_line(27);
  rear++;
  trace_var("rear", rear);
  trace_line(28);
  queue[rear] = 12;
  trace_queue_enqueue("Q", 12);

  trace_line(30);
  rear++;
  trace_var("rear", rear);
  trace_line(31);
  queue[rear] = 7;
  trace_queue_enqueue("Q", 7);

  trace_line(33);
  while (front <= rear) {
    trace_line(33);
    trace_line(34);
    int val = queue[front];
    trace_var_init("val", val);
    trace_queue_dequeue("Q");
    trace_line(35);
    front++;
    trace_var("front", front);
    trace_line(36);
    if (val % 2 == 0) {
      trace_line(37);
      erear++;
      trace_var("erear", erear);
      trace_line(38);
      even[erear] = val;
      trace_queue_enqueue("Even", val);
    } else {
      trace_line(40);
      orear++;
      trace_var("orear", orear);
      trace_line(41);
      odd[orear] = val;
      trace_queue_enqueue("Odd", val);
    }
  }

  trace_line(45);
  printf("Even: ");
  trace_line(46);
  while (efront <= erear) {
    trace_line(46);
    trace_line(47);
    printf("%d ", even[efront]);
    trace_queue_dequeue("Even");
    trace_line(48);
    efront++;
    trace_var("efront", efront);
  }
  trace_line(50);
  printf("\n");

  trace_line(52);
  printf("Odd: ");
  trace_line(53);
  while (ofront <= orear) {
    trace_line(53);
    trace_line(54);
    printf("%d ", odd[ofront]);
    trace_queue_dequeue("Odd");
    trace_line(55);
    ofront++;
    trace_var("ofront", ofront);
  }
  trace_line(57);
  printf("\n");

  trace_line(59);
  return 0;
}
