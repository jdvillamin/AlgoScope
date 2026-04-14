#include <stdio.h>

int main() {
  int m[3][3] = {
    {1, 2, 3},
    {2, 5, 6},
    {3, 6, 9}
  };

  int symmetric = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < i; j++) {
      if (m[i][j] != m[j][i]) {
        symmetric = 0;
      }
    }
  }

  if (symmetric) {
    printf("Matrix is symmetric\n");
  } else {
    printf("Matrix is not symmetric\n");
  }

  return 0;
}
