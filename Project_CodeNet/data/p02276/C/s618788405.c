#include<stdio.h>
int P(*int,int,int);

int main(void){
  int n,i,A[100000],p;
  scanf("%d",&n);
  for(i=0;i<n;i++)
    scanf("%d",&A[i]);
  p=Partition(&A[0],0,n-1);
  printf("%d",A[0]);
  for(i=1;i<n;i++)
    if(i==p){
      printf(" [%d]",A[i]);
  }
    else printf(" %d",A[i]);
  printf("\n");
  return 0;
}
int Partition(int *A,int p,int q){
  int i,x,j,temp;
  x = A[q];
   
  i = p-1;
  for(j = p;j <= q-1;j++){
    if(A[j] <= x){
      i = i + 1;
      temp=A[i];
      A[i]=A[j];
      A[j]=temp;
    }
  } 
  temp=A[i+1];
  A[i+1]=A[r];
  A[r]=temp;
  return i+1;
}