#include  <stdio.h>

int main(void)
{
   long long int n,m,sum=1;
    scanf("%lld",&n);
    
    for(long long int i=0;i<n;i++)
    {
        scanf("%lld",&m);
        sum = sum * m ;
    }
    if(sum>1000000000000000000)
    {
        sum = -1;
    }
    printf("%lld",sum);
    
  
            
    
    return 0;
    }