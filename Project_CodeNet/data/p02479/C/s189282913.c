#include <stdio.h>
#define PI 3.14159265358979

void rr(double);

int main(void){
  double r;

  scanf("%lf" ,&r);

  rr(r);

 return 0;
}

void rr(double r){
  printf("%f %f\n" ,PI*r*r ,2*PI*r);
}