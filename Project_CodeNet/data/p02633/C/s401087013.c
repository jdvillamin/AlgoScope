#include<stdio.h>
#define ll long long

int main()
{
  ll x;
  scanf("%lld",&x);
  ll ans=360LL/x;
  if(360LL%x)ans++;
  printf("%lld",ans);
}