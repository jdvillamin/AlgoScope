#include<stdio.h>
#include<math.h>
int main()
{
long long int a,b,ans,mod,i,modp[200001];
  scanf("%lld %lld",&a,&b);
  mod=pow(10,9)+7;
  modp[0]=1;
  for(i=1;i<200001;++i)
  {
  modp[i]=(modp[i-1]*i)%mod;
  }
  ans=(modp[a]*modp[b])%mod;
  if(llabs(a-b)>1) printf("0");
  else if(a==b) printf("%lld",(ans*2)%mod);
  else printf("%lld",ans);
return 0;}