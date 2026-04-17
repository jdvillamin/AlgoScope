#include <stdio.h>

int main(void){
  long long N;

  scanf("%lld",&N);

  if(N%2 == 0) printf("%lld\n",N);
  else printf("%lld\n",2*N);

  return 0;
}