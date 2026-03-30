#include <stdio.h>

#define MAX 20

int main() {
  int q1[MAX];
  int f1 = 0;
  int r1 = -1;

  int q2[MAX];
  int f2 = 0;
  int r2 = -1;

  int result[MAX];
  int fr = 0;
  int rr = -1;

  r1++;
  q1[r1] = 1;

  r1++;
  q1[r1] = 3;

  r1++;
  q1[r1] = 5;

  r2++;
  q2[r2] = 2;

  r2++;
  q2[r2] = 4;

  r2++;
  q2[r2] = 6;

  while (f1 <= r1 && f2 <= r2) {
    rr++;
    result[rr] = q1[f1];
    f1++;
    rr++;
    result[rr] = q2[f2];
    f2++;
  }

  while (f1 <= r1) {
    rr++;
    result[rr] = q1[f1];
    f1++;
  }

  while (f2 <= r2) {
    rr++;
    result[rr] = q2[f2];
    f2++;
  }

  while (fr <= rr) {
    printf("%d ", result[fr]);
    fr++;
  }
  printf("\n");

  return 0;
}
