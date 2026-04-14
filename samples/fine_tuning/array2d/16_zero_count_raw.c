#include <stdio.h>

int main() {
  int m[3][3] = {
    {0, 2, 0},
    {4, 0, 6},
    {0, 8, 0}
  };

  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (m[i][j] == 0) {
        count++;
      }
    }
  }

  printf("Zeros: %d\n", count);

  return 0;
}
