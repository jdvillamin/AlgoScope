#include <stdio.h>

int main() {
  int mat[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
  };

  for (int j = 0; j < 4; j++) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
      sum += mat[i][j];
    }
    printf("col %d sum: %d\n", j, sum);
  }

  return 0;
}
