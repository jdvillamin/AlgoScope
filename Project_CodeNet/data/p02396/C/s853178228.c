#include <stdio.h>
int x;
int i=1;
main(){
   
   scanf("%d",&x);
   if(x==0){
    return 0;
   }
   
   else{
    printf("Case %d: %d\n",i,x);
   i++;
   }
}