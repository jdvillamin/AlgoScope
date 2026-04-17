#include<stdio.h>
#include<math.h>
int main(){
  int n,d;
  scanf("%d%d", &n, &d);
  int ans=n/((d*2)+1);
  if(n%((d*2)+1)!=0){
    ans++;
  }
  printf("%d", ans);
  return 0;
}