#include <stdio.h>

int main(void){

  int a,b,c,d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  int left = a+b;
  int right = c+d;
  if (left > right) {
    printf("Left\n");
  } else if (left == right) {
    printf("Balanced\n");
  } else {
    printf("Right\n");
  }

  return 0;
}