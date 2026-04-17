#include <stdio.h>

int main()
{
  int a;
  char s[11];
  
  scanf("%d", &a);
  scanf("%s", s);
  
  if(a >= 3200)
    printf("%s\n", s);
  else
    printf("red\n");
  
  return 0;
}