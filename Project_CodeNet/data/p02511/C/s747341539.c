#include <stdio.h>

int main() {
  int i, temp, n, page[50];
  while(1) {
    scanf("%d", &n);
    if(n == 0) break;
    for(i = 0; i < n; i++) {
      scanf("%d", &page[i]);
    }

    temp = page[0];
    printf("%d", page[0]);
    for(i = 1; i < n; i++) {
      if(page[i] - i != temp) {
        if(temp == page[i-1] - (i-1)) {
          printf(" %d", page[i]);
        } else {
          printf("-%d %d", page[i-1], page[i]);
        }
        temp = page[i] - i;
      }
    }
    printf("\n");
  }
}