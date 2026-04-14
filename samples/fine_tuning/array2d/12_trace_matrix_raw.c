#include <stdio.h>

int main() {
  int m[4][4] = {
    {5, 1, 2, 3},
    {4, 8, 6, 7},
    {9, 0, 3, 1},
    {2, 4, 7, 6}
  };

  int trace = 0;
  for (int i = 0; i < 4; i++) {
    trace += m[i][i];
  }

  printf("Trace: %d\n", trace);

  return 0;
}
