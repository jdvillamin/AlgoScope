#include <stdio.h>

int main() {
  int mat[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };

  int isIdentity = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j && mat[i][j] != 1) {
        isIdentity = 0;
      }
      if (i != j && mat[i][j] != 0) {
        isIdentity = 0;
      }
    }
  }

  if (isIdentity) {
    printf("identity matrix\n");
  } else {
    printf("not identity matrix\n");
  }

  return 0;
}
