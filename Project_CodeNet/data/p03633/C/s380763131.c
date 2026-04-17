#include<stdio.h>
#include<math.h>

long long gcd(long long a,long long b);

int main(){
  
  long long n;

  scanf("%lld",&n);

  long long t[n];

  for(long long i=0;i<n;i++){
    scanf("%lld",&t[i]);
  }

  long long ka=1;

  for(long long i=0;i<n;i++){
    ka=(ka/gcd(ka,t[i]))*t[i];
  }

  printf("%lld\n",ka);
    
  return 0;
}

long long gcd(long long a,long long b){
  long long d,s;
  if(a>=b){
    d=a;
    s=b;
  }
  else{
    d=b;
    s=a;
  }

  if(s==1){
    return 1;
  }
  else if(d%s==0){
    return s;
  }
  else{
    return (gcd(s,d%s));
  }
}


