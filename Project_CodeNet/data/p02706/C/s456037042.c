#include <stdio.h>
int main(void) {
  int N;
  int M;
  int sum = 0;

  scanf("%d", &N);
  scanf("%d", &M);

  int A[M];
  for (int i = 0; i < M; i++) {
    scanf("%d", &A[i]);
    sum += A[i];
  }
  if (N > sum) {
    printf("%d\n", N-sum);
  } else {
    printf("%d\n", -1);
  }
  return 0;
}