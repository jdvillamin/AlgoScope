#include<stdio.h>

int main()
{

    long long int a,b;
    char c;

    scanf("%lld %c %lld",&a,&c,&b);

    if(c=='+')
    {
        printf("%lld\n",a+b);
    }
    else
    {
        printf("%lld\n",a-b);

    }
    return 0;
}
