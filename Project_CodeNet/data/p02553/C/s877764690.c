#include<stdio.h>

int main(){
  int a, b, c, d, i;
  long int x[4], max=0;

  scanf("%d %d %d %d", &a, &b, &c, &d);
  x[0]=a*c;
  x[1]=a*d;
  x[2]=b*c;
  x[3]=b*d;
  for(i=0; i<4; i++)
    if(x[i]>max)
      max=x[i];

  printf("%d\n", max);

return 0;}
