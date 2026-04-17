#include<stdio.h>
 
int main(void) {
  int n, m, i, a;
  scanf("%d %d", &n, &m);
  for(i=0; i<m; i++) {
    scanf("%d", &a);
    n-=a;
  }
  if(n<0) {
    n = -1;
  }
  printf("%d\n", n);
  
  return 0;
}