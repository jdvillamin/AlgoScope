#include <stdio.h>
int main(void){
char s,t,u;
 s=t=u=0;
int ss=0,tt=0;
 
scanf("%s%s",&s,&t);
scanf("%d%d",&ss,&tt);
scanf("%s",&u);
 
if(u=s){
printf("%d %d",ss-1,tt);
}
 
if(u=t){
printf("%d %d",ss,tt-1);
}
 
return0;
}