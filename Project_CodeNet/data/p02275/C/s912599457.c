#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define VMAX 10000

void CountingSort(unsigned short*,unsigned short*,int *,int,int);

int main(){
  unsigned short *A, *B;
  int C[VMAX+1];
  int n, i, j;

  scanf("%d", &n);

  A = malloc(sizeof(short)*n+1);
  B = malloc(sizeof(short)*n+1);

  /* your code */
  j=-1;
  for(i=0;i<n;i++){ /* jに最大値を入れる＋ Aにすべての数を入れる */
    scanf("%d",&A[i]);
    if(j<A[i]) j=A[i];
  }
  
  CountingSort(A,B,C,j,n);
  


  for(i=1;i<=n;i++){
    printf("%d",B[i]); /* Bは 1からn までの要素に入れられるため */
    
    if(i!=n) printf(" ");
    else printf("\n");
  }

  return 0;
}

void CountingSort(unsigned short* A,unsigned short* B,int *C,int k,int n){
  int i;

  for(i=0;i<=k;i++) C[i]=0;/* Cを初期化 */

  for(i=0;i<n;i++) C[A[i]]++;

  for(i=1;i<=k;i++) C[i]=C[i]+C[i-1]; /* 最後の要素は必ず n になる */

  for(i=n-1;i>=0;i--){
    B[C[A[i]]]=A[i]; 
    C[A[i]]--;
  }

  return;
}

