#include<stdio.h>
int main()
{
  char a,b;
  scanf("%c %c",&a,&b);
  if(a=='H' || a=='D' && b=='H'|| b=='D')
  {
    if(a == b) printf("H");
    else printf("D");
  }

return 0;
}