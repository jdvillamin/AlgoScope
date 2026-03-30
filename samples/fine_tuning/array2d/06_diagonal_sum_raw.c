#include <stdio.h>

int main() {
  int mat[3][3] = {
    {5, 2, 8},
    {1, 7, 3},
    {4, 6, 9}
  };

  int sum = 0;

  for (int i = 0; i < 3; i++) {
    sum += mat[i][i];
  }

  printf("diagonal sum: %d\n", sum);

  return 0;
}
