#include<stdio.h>

int main(){
  int N;
  scanf("%d",&N);
  int ans[200010];
  
  for(int i=2;i<=N;i++){
    int a;
    scanf("%d",&a);
    ans[a]++;
  }
  
  for(int i=1;i<=N;i++)printf("%d\n",ans[i]);

  return 0;
}
