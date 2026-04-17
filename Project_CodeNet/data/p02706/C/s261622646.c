#include<stdio.h>
int main()
{
    long int x,n,m,a[10010],i,sum=0;
    scanf("%ld%ld",&n,&m);
    for(i=0;i<m;i++)
    {
        scanf("%ld",&a[i]);
        sum+=a[i];
    }
    x=n-sum;
    if(x<0)
        printf("-1\n");
    else
        printf("%d\n",x);
    return 0;
}
