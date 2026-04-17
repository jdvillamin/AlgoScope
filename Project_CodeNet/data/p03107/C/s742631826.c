#include <stdio.h>

int main(void){
   
   char S[1000100];
   
   scanf("%s",S);
   
   int i,nei;
   int ans = 0;
   int flag = 0;
   int start = 0;
   
   while(flag == 0){
      flag = 1;
      for(i = start; S[i] != '\0';i++){
         if(i == start){
            while(S[i] == '2'){
               i = i + 1;
            }
            start = i;
         }
         else {
            while(S[i] == '2'){
               i = i + 1;
            }
         }
         
         
         nei = i + 1;
         while(S[nei] == '2'){
            nei = nei + 1;
         }
         if((S[i] == '0' && S[nei] == '1') || (S[i] == '1' && S[nei] == '0')){
            ans    = ans + 2;
            S[i]   = '2';
            S[nei] = '2';
            i = nei + 1;
            flag = 0;
         }
         else {
            i = nei - 1;
         }
         //printf("%c\n",S[i]);
      }
   }
   printf("%d\n",ans);
   return 0;
}
