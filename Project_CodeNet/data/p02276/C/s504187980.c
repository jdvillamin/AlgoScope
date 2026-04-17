#include<stdio.h>
#include<stdlib.h>
void partition(int *A,int p,int r);
int main(){
  int n,*S,q,*T,i,N,count=0;
  scanf("%d\n",&n);
  S=(int *)malloc(n*sizeof(int));
  for(i=0;i<n;i++){
    scanf("%d",&S[i]);
  }
  partition(S,0,n-1);
  return 0;
}
void partition(int *A,int p,int r){
  int x,i,j,swap,k;
  x=A[r];
  i=p-1;
  for(j=p;j<r;j++){
    if(A[j]<=x){
      i++;
      swap=A[i];
      A[i]=A[j];
      A[j]=swap;
    }
  }
  
  /*printf("[%d] ",A[r]);
  for(k=r+1;k<i+1;k++){
    printf("%d ",A[k]);
  }
  printf("%d\n",A[i+1]);*/
  swap=A[i+1];
  A[i+1]=A[r];
  A[r]=swap;
  for(k=0;k<i+1;k++){
    printf("%d ",A[k]);
  }
  printf("[%d] ",A[i+1]);
for(k=i+2;k<r;k++){
    printf("%d ",A[k]);
  }
 printf("%d\n",A[r]);
}

