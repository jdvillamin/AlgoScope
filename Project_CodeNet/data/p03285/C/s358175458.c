#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int n;
    scanf("%d",&n);
    while(n>=0)
    {
        if(n%4==0)
        {
            printf("Yes");
            return 0;
        }
        else
            n-=7;
    }
    printf("No");
    return 0;
}