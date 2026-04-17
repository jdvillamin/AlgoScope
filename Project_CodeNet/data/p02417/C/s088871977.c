#include <stdio.h> 
 #include <ctype.h> 
 
 
 int main(){ 
     int count[26]={0}; 
     char ch; 
     int i, num; 

     while(scanf("%c", &ch)!=EOF){ 
         if(islower(ch)){ 
             num=ch-'a'; 
         }else if(isupper(ch)){ 
             num=ch-'A'; 
         }else{ 
             continue; 
         } 
         count[num]++; 
     } 
     for(i=0;i<26;i++){ 
         printf("%c : %d\n", 'a'+i, count[i]); 
     } 
 
 
     return 0; 
 } 

