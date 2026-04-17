#include <stdio.h>
 
int main(void){
  
  int N, R;
  scanf("%d %d", &N, &R);
  
  if((N < 1 || N > 100) || (R < 0 || R > 4111)){
    return 0;
  }
  
  if(N < 10){
    R = 100 * (10 - N);
    printf("%d\n", R);
  } else {
    printf("%d\n", R);
  }
  return 0;
}