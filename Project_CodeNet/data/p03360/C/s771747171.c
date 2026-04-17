#include <stdio.h>
int main(void)
{
    int a,b,c,n,tmp,i,s;
    
    scanf("%d%d%d%d",&a,&b,&c,&n);
    if(a<b) {tmp=a; a=b; b=tmp;}
    if(a<c) {tmp=a; a=c; c=tmp;}
    for(i=0;i<n;i++)
        a=a*2;
    s=a+b+c;
    printf("%d\n",s);
    return 0;
}