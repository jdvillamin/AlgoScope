#include <stdio.h>

int main() {
  int m[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  for (int i = 0; i < 3; i++) {
    int maxVal = m[i][0];
    int maxCol = 0;
    for (int j = 1; j < 3; j++) {
      if (m[i][j] > maxVal) {
        maxVal = m[i][j];
        maxCol = j;
      }
    }

    int isSaddle = 1;
    for (int k = 0; k < 3; k++) {
      if (m[k][maxCol] < maxVal) {
        isSaddle = 0;
      }
    }

    if (isSaddle) {
      printf("Saddle at (%d,%d) = %d\n", i, maxCol, maxVal);
    }
  }

  return 0;
}
