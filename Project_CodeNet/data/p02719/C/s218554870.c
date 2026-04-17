#include <stdio.h>

int main(){
   int n,k;
 int ans;

  scanf("%d%d",&n,&k);
  ans=n%k;
  if (ans > k-ans) ans=k-ans;
  printf("%d",ans);
  return 0;

}