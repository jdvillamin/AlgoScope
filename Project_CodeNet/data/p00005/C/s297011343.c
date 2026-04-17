#include <stdio.h>
 
int main()
{
 long long a, b, n, m, r;
 while(scanf("%lld%lld", &a, &b) != EOF){
  if(a>b){
   n=a;
   m=b;
  }else{
   n=b;
   m=a;
  }
  while((r=n%m)!=0){
   n=m;
   m=r;
  }
  printf("%lld %lld\n", m, a*b/m);
 }
 return(0);
}