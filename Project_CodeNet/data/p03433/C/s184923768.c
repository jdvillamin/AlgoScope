#include <stdio.h>
 
int main() {
  int A,N;
  
  scanf("%d",A);
  scanf("%d",N);
  
  if( (N / 500) > A) {
    printf("YES");
  } else {printf("NO");}