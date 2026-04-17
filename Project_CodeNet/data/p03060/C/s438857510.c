#include <stdio.h>

int main(){
  int N; scanf("%d", &N);
  int i, j;
  int V[50] = {};
  int C[50] = {};
  int max = 0;
  
  for(i = 0; i < N; i++){
    scanf("%d", &V[i]);
  }

  for(j = 0; j < N; j++){
    scanf("&d", &C[j]);
    if(V[j] - C[j] > 0) max += V[j] - C[j];
  }

  printf("%d", max);

  return 0;
}
  
