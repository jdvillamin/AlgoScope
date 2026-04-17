#include <stdio.h>
#define NUM (1000000000 + 7)

int main(void)
{
  long long int n;
  long long int k;
  long long int i;
  long long int count = 0;

  scanf("%lld%lld", &n, &k);
  /*
  for (i = k; i <= n + 1; k++) {
    count += i * n + 1 - i * (i - 1);
    count %= NUM;
  }
  */

  count = (n+1)*(n+k+1)*(n-k+2)/2 + (n-k+2) - (n+1)*(n+2)*(2*n+3)/6 + (k-1)*k*(2*k-1)/6;

  count %= NUM;

  printf("%lld\n", count);

  return 0;
}

