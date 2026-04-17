#include<stdio.h>
#include<stdlib.h>

#define N 2*123456

int isPrime[1+N];

void sieve()
{
  int i, j;
  
  for(i = 2; i <= N; ++i){
    isPrime[i] = 1;
  }
  
  for(i = 2; i <= N; ++i){
    if( isPrime[i] ){
      for(j = 2; i * j <= N; ++j){
        isPrime[i * j] = 0;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  sieve();

  while(1){
    int x, n;
    int res = 0;

    // printf("n = ");
    scanf("%d", &n);
    if( n == 0 ) break;
    
    for(x = n+1; x <= 2*n; ++x){
      if( isPrime[ x ] ) ++res;
    }

    // printf("Answer : %d\n", res);
  }
  return (EXIT_SUCCESS);
}