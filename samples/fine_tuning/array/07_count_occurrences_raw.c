#include <stdio.h>

int main() {
  int arr[8] = {3, 7, 3, 2, 3, 8, 7, 3};
  int n = 8;
  int target = 3;
  int count = 0;

  for (int i = 0; i < n; i++) {
    if (arr[i] == target) {
      count++;
    }
  }

  printf("Count: %d\n", count);
  return 0;
}
