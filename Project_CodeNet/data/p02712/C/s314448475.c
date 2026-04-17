#include<stdio.h>
int main(void){
  int n,s,a,b,c,d,e,f,g;
  scanf("%d", &n);
  s=(n*(n+1))/2;
  a=3*(n/3);
  b=5*(n/5);
  c=15*(n/15);
  d=((3+a)*(n/3))/2;
  e=((5+b)*(n/5))/2;
  f=((15+c)*(n/15))/2;
  g=s+f-d-e;
  printf("%d", g);
  return 0;
}