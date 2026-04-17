#include<stdio.h>
int MAX(int a,int b){return a<b?b:a;}
int main(){
  int a,b,c,d,n;
  scanf("%d %d %d %d",&a,&b,&c,&n);
  d=MAX(a,MAX(b,c));
  a=a+b+c-d;
  while(n--)d*=2;
  printf("%d\n",a+d);
  return 0;
}
