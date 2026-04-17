#include <stdio.h>

int main(void){
  long n, k, x, y;
  scanf("%ld %ld", &n, &k);

  x = n%k;
  y = k-x;

  if(x < y) printf("%ld\n", x);
  else printf("%ld\n", y);

  return 0;
}
