#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  int i,j,n,m,**D;
  char buf1[1001],buf2[1001],*X,*Y;
  
  if (scanf("%s %s",buf1,buf2) < 2) exit(1);
  n = strlen(buf1);
  m = strlen(buf2);
  X = malloc((n+1)*sizeof(char));
  Y = malloc((m+1)*sizeof(char));
  for (i=1;i<n+1;i++) X[i] = buf1[i-1];
  for (j=1;j<m+1;j++) Y[j] = buf2[j-1];
  
  D = malloc((n+1)*sizeof(int*));
  for (i=0;i<n+1;i++) {
    D[i] = malloc((m+1)*sizeof(int));
  }
  for (i=0;i<n+1;i++) {
    for (j=0;j<m+1;j++) {
      D[i][j] = 0;
    }
  }
  
  for (i=1;i<n+1;i++) D[i][0] = i;
  for (j=1;j<m+1;j++) D[0][j] = j;
  
  for (i=1;i<n+1;i++) {
    for (j=1;j<m+1;j++) {
      if (X[i] == Y[j]) D[i][j] = D[i-1][j-1];
      else D[i][j] = D[i-1][j-1] + 1;
      if (D[i][j] > D[i][j-1] + 1) D[i][j] = D[i][j-1] + 1;
      if (D[i][j] > D[i-1][j] + 1) D[i][j] = D[i-1][j] + 1;
    }
  }

  printf("%d\n",D[n][m]);
  
  return 0;
}