#include <stdio.h>
int main(void){
int a,b;
  scanf("%d %d",&a,&b);
  for(;;){
  a=a-500;
    if(a==0){printf("Yes");
            break;}
    if(a<0){a=a+500;
           break;
           }
  }
    if(a-b<=0){printf("Yes");}
  else{printf("No");}
return 0;
}