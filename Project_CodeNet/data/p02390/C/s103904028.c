#include<stdio.h>

int main(){
  int S, M, L, base = 3600;

  scanf("%d %d %d", &S, &M, &L);

  base += S;
  base += M + L;

  printf("%d\n", base);

  return 0;
}

