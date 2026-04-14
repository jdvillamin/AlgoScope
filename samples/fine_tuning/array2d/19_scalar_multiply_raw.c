#include <stdio.h>

int main() {
  int m[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  int scalar = 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m[i][j] = m[i][j] * scalar;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }

  return 0;
}
