#include <stdio.h>

int main() {
  int mat[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  int sum = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 0 || i == 2 || j == 0 || j == 2) {
        sum += mat[i][j];
      }
    }
  }

  printf("border sum: %d\n", sum);

  return 0;
}
