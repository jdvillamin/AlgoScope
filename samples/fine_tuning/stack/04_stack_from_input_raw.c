#include <stdio.h>

#define MAX 20

int main() {
  int stack[MAX];
  int top = -1;
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    top++;
    stack[top] = val;
  }

  while (top >= 0) {
    printf("%d ", stack[top]);
    top--;
  }
  printf("\n");

  return 0;
}
