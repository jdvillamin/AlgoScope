#include <stdio.h>
#include <string.h>
int main(void){
 char a[3][101];
 int b[3]={0};
 int i,j=0;
 for(i=0;i<3;i++) scanf("%s",a[i]);
 while(1){
  if(a[j][b[j]]=='\0') break;
  j=a[j][b[j]++]-'a';
 }
 printf("%c",'A'+j);
 return 0;
}