#include<stdio.h>
int main()
{
  long long int a;
  int x=0;
  scanf("%lld",&a);
  while(a>=3)
    {
      a/=3;
      x++;
    }
  printf("%d\n",x+1);
  exit(0);
}