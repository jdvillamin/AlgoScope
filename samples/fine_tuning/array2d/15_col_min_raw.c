#include <stdio.h>

int main() {
  int m[3][3] = {
    {5, 9, 2},
    {8, 3, 7},
    {1, 6, 4}
  };

  for (int j = 0; j < 3; j++) {
    int min = m[0][j];
    for (int i = 1; i < 3; i++) {
      if (m[i][j] < min) {
        min = m[i][j];
      }
    }
    printf("Col %d min: %d\n", j, min);
  }

  return 0;
}
