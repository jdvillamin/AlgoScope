#include <stdio.h>

int main() {
  int m[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };

  int u[4][4];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (j >= i) {
        u[i][j] = m[i][j];
      } else {
        u[i][j] = 0;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d ", u[i][j]);
    }
    printf("\n");
  }

  return 0;
}
