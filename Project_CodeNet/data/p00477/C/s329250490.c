#include<stdio.h>
int main(void){
  int a,b,c,d,m=0,s=0;
  scanf("%d",&a);
  scanf("%d",&b);
  a=a+b;
  scanf("%d",&c);
  a=a+c;
  scanf("%d",&d);
  a=a+d;
  m=a/60;
  s=a%60;
  printf("%d\n",m);
  printf("%d\n",s);
  return(0);
}