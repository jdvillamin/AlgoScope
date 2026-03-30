#include <stdio.h>

int main() {
  int mat[3][3] = {
    {4, 8, 2},
    {6, 1, 9},
    {3, 7, 5}
  };

  int target = 9;
  int found = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (mat[i][j] == target) {
        printf("found %d at (%d, %d)\n", target, i, j);
        found = 1;
      }
    }
  }

  if (!found) {
    printf("%d not found\n", target);
  }

  return 0;
}
