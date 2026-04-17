#include<stdio.h>

int main(void){
  int i,x,n;

  scanf("%d",&n);

  for(i=1;i<=n;i++){
    x=i;
    if(x%3==0){
      printf(" %d",i);
      continue;
    }
    do{
      if(x%10==3){
	printf(" %d",i);
      }
      x/=10;
    }while(x!=0);
  }
  printf("\n");
}

