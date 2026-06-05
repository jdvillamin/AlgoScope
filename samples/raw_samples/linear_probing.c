#include <stdio.h>

#define SIZE 7

int keys[SIZE];
int values[SIZE];
int occupied[SIZE];

int hash(int key) { return key % SIZE; }

void put(int key, int value) {
  int index = hash(key);
  while (occupied[index]) {
    index = (index + 1) % SIZE;
  }
  keys[index] = key;
  values[index] = value;
  occupied[index] = 1;
}

int main() {
  for (int i = 0; i < SIZE; i++) {
    occupied[i] = 0;
  }

  put(10, 100);
  put(17, 170);
  put(24, 240);
  put(3, 30);

  return 0;
}
