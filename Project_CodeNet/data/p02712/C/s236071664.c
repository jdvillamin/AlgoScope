#include<stdio.h>
int main()[
  int N;
  scanf("%d",&N);
  
  long int ans;
  
  for (int i=1;i<=N;i++){
    if (i/3!=0){
      if(i/5!=0){
        ans+=i;
      }
    }
  }
  
  printf("%d",ans);
  return;
  }
  