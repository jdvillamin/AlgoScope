#include<stdio.h>
#include<stdlib.h>

void CountingSort(int*, int*, int);
int n;
main() {
  int i,*A,*B;
  scanf("%d",&n);
  A = (int *)malloc(sizeof(int) * n+1);
  B = (int *)malloc(sizeof(int) * n+1);
  if(A == NULL) {
    printf("メモリが確保できません\n");
    exit(EXIT_FAILURE);
  }
  if(B == NULL) {
    printf("メモリが確保できません\n");
    exit(EXIT_FAILURE);
  }

  for(i = 1; i <= n; i++) {
    scanf("%d",&A[i]);
  }

  CountingSort(A, B,10000);

  for(i = 1; i <= n; i++) {
    if(i > 1) printf(" ");
    printf("%d",B[i]);
  }
  printf("\n");
  free(A);
  free(B);

  return 0;
}

void CountingSort(int *A,int *B, int k) {
  int i,j;
  int C[10001];
  for(i = 0; i < k; i++) {
    C[i] = 0;
  }

/* C[i]にiの出現数を記録する。 */
  for(j = 1; j < n+1; j++) {
    C[A[j]]++;
  }

/* C[i]にi以下の数の出現数を記録する */
  for(i = 1; i < k; i++) {
    C[i] = C[i] + C[i-1];
  }

  for(j = n; j > 0; j--) {
    B[C[A[j]]] = A[j];
    C[A[j]]--;
  }
}