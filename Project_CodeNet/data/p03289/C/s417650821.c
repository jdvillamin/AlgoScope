#include <stdio.h>
#include<string.h>
int main(){
  
   char str[10] ;
   scanf("%s",&str);

   int length = strlen(str);
   int count = 0 , i;
   
   for(i = 0 ; i<length ; i++){
       if(str[i]<97){
           count++;
       }
   }
   //printf("%d",size);
   int count2 = 0;
   if(str[0] = 'A' && count==2){
       for(i = 2 ; i<length-2; i++){
           if(str[i]=='C'){
               count2++;
               break;
           }
       }
   }
   if(count2!=0){
       printf("AC");
   }else{
       printf("WA");
   }

}