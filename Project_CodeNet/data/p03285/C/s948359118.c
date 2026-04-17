#include<stdio.h>
int main(){
  int n,i,j;
  scanf("%d",&n);
  n%=28;
  for(i=0;i<7;i++)
    for(j=0;j<4;j++)
      if(n==4*i+7*j){
        puts("Yes");
        return 0;
      }
  puts("No");
  return 0;
}
