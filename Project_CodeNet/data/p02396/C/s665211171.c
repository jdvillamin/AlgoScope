#include <stdio.h>
 
int main(void){
 
  long x;
  int i = 1;
 
  while(1){
    scanf("%d",&x);
    if(x == 0){
      break;
    }
    printf("Case %d: %d",i,x);
    i++;
  }
  return 0;
}