#include <stdio.h>
unsigned long long Fibonacci(unsigned long long m)
{
  static unsigned long long n1 = 0,n2 = 1;
  if(m == 0) return n1 + n2;
  n2 += n1 ^= n2 ^= n1 ^= n2;
  return Fibonacci(m - 1);
}
int main()
{
  unsigned long long i;
  scanf("%llu",&i);
  printf("%llu\n",Fibonacci(i));
  return 0;
}