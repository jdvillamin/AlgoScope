#include<stdio.h>

int main(){
int y=1,x=1,f,s;
while(y!=0&&x!=0){
scanf("%d %d",&x,&y);
if(x==0&&y==0)break;
f=x;
s=y;
if(f>s){
f=y;
s=x;
}
printf("%d %d\n",f,s);
}
return 0;
}