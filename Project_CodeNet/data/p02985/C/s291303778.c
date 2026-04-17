#include<stdio.h>
int main(void){
  int n,k,v,e[100001];
  scanf("%d%d",&n,&k);
  long a=k;
  for(int i=0;i<2*n-2;i++){
    scanf("%d",&v);
    e[v]++;
    if(e[v]>1||v<2){
      a*=k-e[v];
      a%=1000000007;
    }
  }
  printf("%d",a);
  return 0;
}