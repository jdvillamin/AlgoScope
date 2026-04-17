#include <stdio.h>

int main(void){
int a;
int aa;
int b;
int bb;
int c;
scanf("%d %d %d",&a,&b,&c);
if(a > b){
aa=a;
a=b;
b=aa;
}
if(b > c){
bb=b;
b=c;
c=bb;
}
if(a > b){
bb=a;
a=b;
b=bb;
}
printf("%d %d %d",a,b,c);
}
