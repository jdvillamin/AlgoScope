#include <stdio.h>

int main() {
  int mat[3][3] = {
    {3, 7, 2},
    {9, 1, 8},
    {4, 6, 5}
  };

  int max = mat[0][0];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (mat[i][j] > max) {
        max = mat[i][j];
      }
    }
  }

  printf("max: %d\n", max);

  return 0;
}
