#include <stdio.h>

int main() {
  int arr[5] = {3, 7, 1, 9, 4};
  int target = 9;
  int found = -1;

  for (int i = 0; i < 5; i++) {
    if (arr[i] == target) {
      found = i;
      break;
    }
  }

  if (found >= 0) {
    printf("Found at index %d\n", found);
  } else {
    printf("Not found\n");
  }

  return 0;
}
