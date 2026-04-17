#include <stdio.h>

int main()
{
  int x;
  scanf("%d",&x);
  int i = 0;
  float n = 1.08;
  while (n * i <= x)
  {
    i++;
    if (n*i >= x+1)
    {
      printf(":(");
      return (0);
    }
  }
  printf("%d",i);
}