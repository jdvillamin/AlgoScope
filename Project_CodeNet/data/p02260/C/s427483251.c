#include <stdio.h>

int main()
{
  int i, j, n, temp;
  int a[100];

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for (i = 0; i < n; i++) {
    minj = i;
    for (j = i; j < n; j++) {
      if (a[j] < [minj])
        minj = j;
      }
    }
    temp = a[i];
    a[i] = a[minj];
    a[minj] = temp;
  }

  for (i = 0;i < n; i++) {
    printf("%d ", a[i]);
  }
    puts("");
    printf("%d\n", a[minj]);

  return 0;
}