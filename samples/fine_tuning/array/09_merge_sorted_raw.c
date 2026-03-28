#include <stdio.h>

int main() {
  int a[3] = {1, 4, 7};
  int b[3] = {2, 5, 8};
  int merged[6];
  int i = 0, j = 0, k = 0;

  while (i < 3 && j < 3) {
    if (a[i] <= b[j]) {
      merged[k] = a[i];
      i++;
    } else {
      merged[k] = b[j];
      j++;
    }
    k++;
  }

  while (i < 3) {
    merged[k] = a[i];
    i++;
    k++;
  }

  while (j < 3) {
    merged[k] = b[j];
    j++;
    k++;
  }

  return 0;
}
