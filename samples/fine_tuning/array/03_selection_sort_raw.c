#include <stdio.h>

int main() {
  int arr[5] = {8, 4, 2, 9, 1};
  int n = 5;

  for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIdx]) {
        minIdx = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[minIdx];
    arr[minIdx] = temp;
  }

  return 0;
}
