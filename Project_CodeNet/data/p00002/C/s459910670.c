#include<stdio.h>

int main()
{
    long long int n,x,y,a,b;
    while((scanf("%lld%lld",&a,&b))!=EOF)
    {
        long long int ca=0,cb=0;
        while(a!=0)
        {
            x=a/10;
            y=a%10;
            if(y!=0)
                ca++;
            a=x;
        }
        while(b!=0)
        {
            x=b/10;
            y=b%10;
            if(y!=0)
                cb++;
            b=x;
        }
        printf("%lld\n",ca+cb);
    }
    return 0;
}