#include <stdio.h>
#include <math.h>
int main(void){
  int a,b,c;
  char s[1000];
  scanf("%d%d%d",&a,&b,&c);
  int d=fmin(c,b/a);
  printf("%d",d);
  return 0;
}