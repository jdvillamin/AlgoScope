#include<stdio.h>

int main(){
  int n,a,b,c,d,e,f,g,h,sum;
  
  scanf("%d",&n);
  a=n%10;
  b=(n-a)%100;
  c=(n-n%100)%1000;
  d=(n-n%1000)%10000;
  e=(n-n%10000)%100000;
  f=(n-n%100000)%1000000;
  g=(n-n%1000000)%10000000;
  h=(n-n%10000000)%100000000;
  
  sum=a+b+c+d+e+f+g+h;
  if(n%sum=0) {
    printf("%c\n",Yes);
  } else {
    printf("%c\n",No);
  }
  return 0;
}
  