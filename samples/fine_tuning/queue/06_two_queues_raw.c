#include <stdio.h>

#define MAX 20

int main() {
  int q1[MAX];
  int front1 = 0;
  int rear1 = -1;

  int q2[MAX];
  int front2 = 0;
  int rear2 = -1;

  rear1++;
  q1[rear1] = 2;

  rear1++;
  q1[rear1] = 4;

  rear1++;
  q1[rear1] = 6;

  rear2++;
  q2[rear2] = 1;

  rear2++;
  q2[rear2] = 3;

  rear2++;
  q2[rear2] = 5;

  printf("Q1: ");
  while (front1 <= rear1) {
    printf("%d ", q1[front1]);
    front1++;
  }
  printf("\n");

  printf("Q2: ");
  while (front2 <= rear2) {
    printf("%d ", q2[front2]);
    front2++;
  }
  printf("\n");

  return 0;
}
