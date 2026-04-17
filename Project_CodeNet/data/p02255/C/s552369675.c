#include<stdio.h>

int main(){

  int i,j,n,min,g;
  int A[100];
  
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%d",&A[i]);
  
  for(i=1;i<n+1;i++){
    min = A[i];
    j = i-1;
     for(g=0;g<n;g++){
      printf("%d ",A[g]);
    }
    printf("\n");
    while(j >= 0 && A[j] > min){
      A[j+1] = A[j];
      j--;
      A[j+1] = min;
    }
   
  }
  return 0;
}