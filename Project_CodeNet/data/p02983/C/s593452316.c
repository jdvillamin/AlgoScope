#include<stdio.h>

int main(){
  int l,r,min = 100000000;
  scanf("%d %d",&l,&r);
  for(int i=l;i<=r;i++){
    for(int j=i+1;j<=r;j++){
      if(min > i*j%2019)min = i*j%2019;
      if(min == 0){
        printf("%d\n",min);
        return 0;
      }
    }
  }
  printf("%d\n",min);
  return 0;
}
