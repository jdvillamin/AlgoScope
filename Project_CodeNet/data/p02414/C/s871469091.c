#include <stdio.h>

int main(void)
{
  int n = 0;
  int m = 0;
  int l = 0;
  int a[101][101];
  int b[101][101];
  int i, j, k;
  long sum = 0;
  
  scanf("%d %d %d", &n, &m, &l);

  for(i = 0; i < n; i++){
    for(j = 0; j < m; j++)
      scanf("%d ", &a[i][j]);
  }

  for(i = 0; i < m; i++){
    for(j = 0; j < l; j++)
      scanf("%d ", &b[i][j]);
  }
    
  for(i = 0; i < n; i++){
    for(j = 0; j < l; j++){
      for(k = 0; k < m; k++)
	sum += a[i][k] * b[k][j];
      if(j == l -1)
	printf("%ld\n", sum);
      else
	printf("%ld ", sum);
      sum = 0;
    }
  }

  return 0;
}