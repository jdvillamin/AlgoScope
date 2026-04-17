#include<stdio.h>

int main(void) {
int n,m,l;
int i,j,k;

scanf("%d %d %d", &n, &m, &l);

int matA[n][m];
int matB[m][l];

for (i = 0; i < n; i++)
for (j = 0; j < m; j++)
scanf("%d", &matA[i][j]);

for (i = 0; i < m; i++)
for (j = 0; j < l; j++)
scanf("%d", &matB[i][j]);

for (i = 0; i < l; i++) {
for (j = 0; j < m; j++) {
for (k = 0; k < m; k++) {
ans += matA[j][k] * matB[k}[j];
}
printf("%d ", ans);
}
printf("%d\n"ans);
}

return (0);
}