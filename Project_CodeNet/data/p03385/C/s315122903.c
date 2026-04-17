#include<stdio.h>
int main(void)
{
  char a;
  scanf("%s",a);
    if(a='abc'||a='acb'||a='bac'||a='bca'||a='cab'||a='cba')
      printf("Yes");
  else printf("No");

}