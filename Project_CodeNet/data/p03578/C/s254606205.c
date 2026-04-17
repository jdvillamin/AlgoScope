#include <stdio.h>

int main() {
int N,M;
int i,j,k;
scanf("%d",&N);
int D[200000];
for (i=0;i<N;i++)
 scanf("%d",&D[i]);
scanf("%d",&M);
int T[200000];
for (i=0;i<M;i++)
 scanf("%d",&T[i]);

k=0;
for (i=0;i<M;i++) {
j=0;
while (D[j]!=T[i]) {
 j=j+1;
 if (j==N) {
  k=1;
  break;
  break;
  break;
 }
}
D[j]=0;
}

if (k==1)
 printf("No\n");
else
 printf("Yes\n");

return 0;
}