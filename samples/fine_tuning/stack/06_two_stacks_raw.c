#include <stdio.h>

#define MAX 10

int main() {
  int s1[MAX], s2[MAX];
  int top1 = -1, top2 = -1;

  top1++;
  s1[top1] = 3;
  top1++;
  s1[top1] = 6;

  top2++;
  s2[top2] = 9;
  top2++;
  s2[top2] = 12;

  printf("s1 top: %d\n", s1[top1]);
  printf("s2 top: %d\n", s2[top2]);

  top1--;
  top2--;

  return 0;
}
