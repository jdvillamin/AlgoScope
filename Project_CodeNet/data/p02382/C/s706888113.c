#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1024

int main(void){
  int n, i;
  double vecx[SIZE] = {0}, vecy[SIZE] = {0};
  double D[4] = {0};

  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%lf", &vecx[i]);
  for (i = 0; i < n; i++)
    scanf("%lf", &vecy[i]);

  // calculate D1
  D[0] = 0;
  for (i = 0; i < n; i++)
    D[0] += abs(vecx[i] - vecy[i]);

  // calculate D2
  D[1] = 0;
  for (i = 0; i < n; i++)
    D[1] += pow(abs(vecx[i] - vecy[i]), 2);
  D[1] = sqrt(D[1]);

  // calculate D3
  D[2] = 0;
  for (i = 0; i < n; i++)
    D[2] += pow(abs(vecx[i] - vecy[i]), 3);
  D[2] = cbrt(D[2]);

  // calculate D_infinity
  D[3] = 0;
  for (i = 0; i < n; i++) {
  if (D[3] < abs(vecx[i] - vecy[i]))
    D[3] = abs(vecx[i] - vecy[i]);
  }

  for (i = 0; i < 4; i++)
    printf("%lf\n", D[i]);
  return 0;
}