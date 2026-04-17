#include<stdio.h>
#include<stdlib.h>

int main(){
  int *A,n,temp,i,j,flag,cnt=0;
    scanf("%d",&n);
   
 
  A =(int *)malloc(n * sizeof(int));
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
     
  }
  flag = 1;
  i = 0;
  while(flag){
    flag = 0;
    for(j=n-1;j>=i+1;j--){
      if(A[j]<A[j-1]) {
	temp = A[j-1];
	A[j-1] =A[j];
	A[j] = temp;
	flag = 1;
	cnt++;
      }
    }
    i++;
  

  }
  for(i=0;i<n;i++){
    if(i==n-1) printf("%d",A[i]);
    else if(A[i]>9) printf("%-3d",A[i]);
    else printf("%-2d",A[i]);
  
    
  }
  printf("\n");
  printf("%d\n",cnt);
  free(A);
    return 0;


}

