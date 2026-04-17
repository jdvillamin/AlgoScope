#include <stdio.h>
#define N 200000
int A[N];

unsigned long long int gcd(int x, int y){
  while(x != 0){
    int z = x;
    x = y%x;
    y = z;
  }
  return y;
} 

unsigned long long int lcm(int x, int y){
  int z = gcd(x, y);
  int a = x*y/z;
  return a;
}

unsigned long long int main(){
  int n,i,j,z;
  unsigned long long int sum, r;
  scanf("%llu", n);
  for(i=0; i<n; i++) scanf("%llu", &A[i]);
  sum = 0;
  for(i=0; i<=n-2; i++){
    for(j=i+1; j<=n-1; j++){
      z = lcm(A[i], A[j]);
      sum = sum + z;
    }
  }
  r = sum % 998244353;
  printf("%llu\n", r);
  return 0;
}