#include <stdio.h>

int main() {
  int arr[6] = {4, 11, 2, 19, 7, 3};
  int n = 6;
  int max = arr[0];

  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  printf("Max: %d\n", max);
  return 0;
}
