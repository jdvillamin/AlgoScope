#include <stdio.h>

int main(){
  int N,i,j,count,sw;

  scanf("%d",&N);
  int A[N];
  for(i=0;i<=N-1;i++){
    scanf("%d",&A[i]);
    }
    for(i=0;i<N-1;i++){
      for(j=N-1;j>i;j--){
            if(A[j]<A[j-1]){
              sw=A[j-1];
              A[j-1]=A[j];
              A[j-1]=sw;

              count++;
            }
    }
  }
  for(i=0;i<N;i++){
    if(i==0) printf("%d",A[i]);
    else if(i>0) printf(" %d",A[i]);
  }
  printf("?\n");
  printf("%d?\n",count);
    return 0;
  }