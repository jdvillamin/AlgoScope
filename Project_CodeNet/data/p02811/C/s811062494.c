#include<stdio.h>
int main(void){
  int k,x;
  scanf("%d %d",&k,&x);
  if(500*k>=x) printf("Yes");
  else printf("No");
  return 0;
}