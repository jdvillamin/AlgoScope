#include <stdio.h>

int main() {
  int m[3][3] = {
    {3, 7, 2},
    {8, 1, 5},
    {4, 9, 6}
  };

  for (int i = 0; i < 3; i++) {
    int max = m[i][0];
    for (int j = 1; j < 3; j++) {
      if (m[i][j] > max) {
        max = m[i][j];
      }
    }
    printf("Row %d max: %d\n", i, max);
  }

  return 0;
}
