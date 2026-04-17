#include <stdio.h>

int main(){
  long long n,k,d,c,e,f;
  scanf("%lld%lld",&n,&k);
  long long a[n+1],b[n+1];
  for(int i=1;i<=n;i++){
    scanf("%lld",&a[i]);
    b[i]=0;
  }
  c=a[1];
  b[1]=1;
  for(int i=1;i<=n;i++){
    c=a[c];
    b[c]+=1;
    if(b[c]==2){d=i;e=c;break;}
  }
   c=a[1];
  for(int i=1;i<=n;i++){
    c=a[c];
    if(c==e){f=i;break;}
  }
  c=a[e];
  k=(k-f)%(d-f);
  for(int i=1;i<k;i++){
    c=a[c];
  }
  printf("%lld",c);
  return 0;
}
