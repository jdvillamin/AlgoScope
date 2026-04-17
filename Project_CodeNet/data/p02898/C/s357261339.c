#include <stdio.h>

int main(void)
{
 int N,i,K,h[1000];
 int count=0;

 scanf("%d%d",&N,&K);

 for(i=0;i<N;i++){
  scanf("%d",&h[i]);
  if(h[i]>=K)
   count++;
 }

 printf("%d\n",count);
 return 0;
}
