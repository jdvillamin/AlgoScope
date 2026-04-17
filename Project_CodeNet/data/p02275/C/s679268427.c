#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define VMAX 10

int main(){
  unsigned short *A, *B;
  int C[VMAX+1];
  int n, i, j;

  scanf("%d", &n);

  A = malloc(sizeof(short)*n+1);
  B = malloc(sizeof(short)*n+1);

  /* your code */
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
  }

  for(i=0;i<=n;i++){
    C[i]=0;
  }

  for(i=0;i<n;i++){
    C[A[i]]++;
  }

  for(i=0;i<n;i++){
    C[i+1]+=C[i];
  }

  for (i = n - 1; i >= 0; i--) {
    B[--C[A[i]]] = A[i];
  }

  for(i=0;i<n;i++){
    printf("%d ",B[i]);
  }

  printf("\n");

  


  return 0;
}
