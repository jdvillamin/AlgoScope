#include <stdio.h>

int main() {
  int arr[5] = {7, 3, 5, 1, 9};
  int n = 5;

  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }

  return 0;
}
