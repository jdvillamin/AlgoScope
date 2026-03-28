#include <stdio.h>

#define MAX 20

int main() {
  int stack[MAX];
  int top = -1;

  int n;
  scanf("%d", &n);

  // ---- Push values from input ----
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    top++;
    stack[top] = val;
  }

  // ---- Pop all ----
  while (top >= 0) {
    printf("popped: %d\n", stack[top]);
    top--;
  }

  return 0;
}
