
#include <stdio.h>

int main() {
  int H[300],W[300],i,j,n,m;
  for(n=0;;n++) {
    scanf("%d %d",&H[n],&W[n]);
    if (H[n] == 0 && W[n] == 0) break;
  }
  for(m=0;m<n;m++) {
    for (i=0;i<H[m];i++) {
      for(j=0;j<W[m];j++) printf("#");
      printf("\n");
    }
    printf("\n");
  }
}