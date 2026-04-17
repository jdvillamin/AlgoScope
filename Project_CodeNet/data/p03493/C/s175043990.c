#include <stdio.h>
#include <string.h>
 
int main(void){
  char a[3];
  int b = 0
  int i = 0;
  scanf("%c",a);
  for(i = 0;i<3;i++){
   if(a[i] == 1){
     b++;
   }
  }
  printf("%d",b);
  
  return 0; 
}