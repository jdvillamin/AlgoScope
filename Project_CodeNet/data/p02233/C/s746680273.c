#include <stdio.h>
#define N 44
int makeFibonacci(int);
int F[N];
int main(){
  int n,x=0;
  scanf("%d",&n);
  x=makeFibonacci(n);
  printf("%d\n",x);  
  return 0;
}
int makeFibonacci(int n){
  int i,x=0; 
  F[0]=1;
  F[1]=1;
  if(n==0||n==1){
    return 1;
  }
  for(i=2;i<n;i++){
    x+=F[i]=F[i-2]+F[i-1];
  }
  return x;
}