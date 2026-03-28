#include <stdio.h>

int main() {
  int arr[6] = {4, 7, 4, 2, 4, 9};
  int n = 6;
  int target = 4;
  int newSize = 0;

  for (int i = 0; i < n; i++) {
    if (arr[i] != target) {
      arr[newSize] = arr[i];
      newSize++;
    }
  }

  return 0;
}
