#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  int arr[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int target;
  scanf("%d", &target);

  // ---- Linear Search ----
  int found = -1;
  for (int i = 0; i < n; i++) {
    if (arr[i] == target) {
      found = i;
      break;
    }
  }

  if (found >= 0) {
    printf("Found %d at index %d\n", target, found);
  } else {
    printf("%d not found\n", target);
  }

  return 0;
}
