#include<stdio.h>

int main(void)
{
  int a,b;
  scanf("%d%d",&a,&b);
  if(a%b==0) printf("%d",a+b);
  else printf("%d",b-a);

  return 0;
}