#include <stdio.h>
int main()
{
  int a,b,c;
  scanf("%d",&a);
  scanf("%d",&b);
  scanf("%d",&c);
  printf("%s",a==b?b==c?"No":"Yes":b==c?"Yes":a==c?"Yes":"No");
  return 0;
}