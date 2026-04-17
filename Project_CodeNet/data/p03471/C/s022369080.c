#include <stdio.h>

int main(){
  int n,y;
  scanf("%d%d",&n,&y);
  int i,j,k;
  for(i=0;i<=n;i++)for(j=0;j<=n;j++){
    if(i*10000+j*5000+(n-i-j)*1000 == y){
      printf("%d %d %d\n",i,j,k);
      return 0;
    }
  }
  
  printf("-1 -1 -1\n");
  return 0;
}
 