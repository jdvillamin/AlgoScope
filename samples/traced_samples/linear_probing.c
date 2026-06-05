#include <stdio.h>
#include "tracer.h"

#define SIZE 7

int keys[SIZE];
int values[SIZE];
int occupied[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  trace_line(12);
  int index = hash(key);
  trace_var_init("index", index);
  trace_line(13);
  while (occupied[index]) {
    trace_line(13);
    trace_line(14);
    index = (index + 1) % SIZE;
    trace_var("index", index);
  }
  trace_line(16);
  keys[index] = key;
  trace_line(17);
  values[index] = value;
  trace_line(18);
  occupied[index] = 1;
  trace_hash_put("H", key, value, index);
}

int main() {
  trace_hash_init("H", SIZE);

  trace_line(22);
  for (int i = 0; i < SIZE; i++) {
    trace_line(22);
    trace_line(23);
    occupied[i] = 0;
  }

  trace_line(26);
  put(10, 100);
  trace_line(27);
  put(17, 170);
  trace_line(28);
  put(24, 240);
  trace_line(29);
  put(3, 30);

  trace_line(31);
  return 0;
}
