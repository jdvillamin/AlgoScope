#include <stdio.h>
int main(void){
   int a,b,c,X;
   scanf("%d",&a);
   scanf("%d",&b);
   scanf("%d",&c);
    
   if(a>b){
      X=a;
      a=b;
      b=X;
   }
   if(b>c){
      X=b;
      b=c;
      c=X;
   }
   if(a>b){
      X=a;
      a=b;
      b=X;
   }
 
    
   printf("%d %d %d\n",a,b,c);
   return 0;
}
