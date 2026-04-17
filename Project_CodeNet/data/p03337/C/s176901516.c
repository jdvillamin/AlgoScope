#include<stdio.h>
int main()
{
    int A,B,c,d,e;
    scanf("%d%d",&A,&B);
    c=(A+B);
    d=(A-B);
    e=(A*B);
    if ((c>d) && (c>e))
    {
        printf("%d\n", c);
    }
    else if((d>c) && (d>e))
    {
        printf("%d\n", d);
    }
    else if((e>c) && (e>d))
    {
        printf("%d\n", e);
    }
    return 0;
}
