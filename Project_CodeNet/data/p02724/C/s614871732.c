#include <stdio.h>
int main(void){
    long long n,ans=0;
    scanf("%lld",&n);
    ans=n/500*1000;
    ans+=n%500/5*5;
    printf("%lld",ans);
}
