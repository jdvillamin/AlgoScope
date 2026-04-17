#include <stdio.h>

int main(void) {
  int i, j, k, n, temp, minj, flag = 1;
  char a[10][3];
  char b[10][3];

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%s", a[i]);
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      b[i][j] = a[i][j];
    }
  }

  for (i = 0; i < n; i++) {
    for (j = n - 1; j > i; j--) {
      if (a[j][1] < a[j-1][1]) {
        temp = a[j][0];
        a[j][0] = a[j-1][0];
        a[j-1][0] = temp;
        temp = a[j][1];
        a[j][1] = a[j-1][1];
        a[j-1][1] = temp;
      }
    }
  }

  for (i = 0; i < n; i++) {
    printf("%s", a[i]);
    if (i < n - 1) {
      printf(" ");
    }
  }
  printf("\nStable\n");

  for (i = 0; i < n; i++) {
    minj = i;
    for (j = i; j < n; j++) {
      if (b[j][1] < b[minj][1]) {
        minj = j;
      }
    }
    temp = b[i][0];
    b[i][0] = b[minj][0];
    b[minj][0] = temp;
    temp = b[i][1];
    b[i][1] = b[minj][1];
    b[minj][1] = temp;
  }

  for (i = 0; i < n; i++) {
    printf("%s", b[i]);
    if (i < n - 1) {
      printf(" ");
    }
  }
  printf("\n");

  for (i = 0; i < n; i++) {
    if (flag == 0) {
      break;
    }
    for (j = 0; j < n; j++) {
      if (b[i][j] != a[i][j]) {
        printf("Not stable\n");
        flag = 0;
        break;
      }
    }
  }

  if (flag == 1) {
    printf("Stable\n");
  }


  return 0;
}

