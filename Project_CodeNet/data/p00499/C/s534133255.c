#include<stdio.h>


int main( ){

  int a, b, c, d, l, e, f;

  scanf("%d\n %d\n %d\n %d\n %d", &l, &a, &b, &c, &d);

  if(a%c == 0)
    e = a/c;
  else
    e = a/c+1;
  
  if(b%d == 0)
    f = b/d;
  else
    f = b/d+1;

  if(e > f)
    printf("%d\n", l-e);
  else
    printf("%d\n", l-f);
  


  return 0;
}