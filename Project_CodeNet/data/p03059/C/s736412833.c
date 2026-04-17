#include<stdio.h>
int main(){
    double A,B,T;
    scanf("%lf",&A);
    scanf("%lf",&B);
    scanf("%lf",&T);
    double x = (T+0.5) / A;
    printf("%g\n",(int)x*B);
    return 0;
}
