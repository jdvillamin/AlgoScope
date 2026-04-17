#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,n;
    scanf("%d%d",&a,&b);
    n=a*b;
    if(n%2==0)
        printf("Even\n");
    else
        printf("Odd\n");
    return 0;
}
