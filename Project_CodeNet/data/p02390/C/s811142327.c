#include<stdio.h>
int main()
{
    int s,m,h,a;
    scanf("%d %d %d %d" ,&s,&m,&h,&a);
    s=a%60;
    m=a%3600;
    h=a/3600;
    return 0;
}