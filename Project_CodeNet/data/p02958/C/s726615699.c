#include <stdio.h>

int main(void){
  int n,s=0,i,x;
  scanf("%d",&n);
  for(i=1;i<=n;++i){
    scanf("%d",&x);
    if(x!=i) s++;
  }
  if(s==0 || s==2)  printf("YES\n");
  else printf("NO\n");
  return 0;
}