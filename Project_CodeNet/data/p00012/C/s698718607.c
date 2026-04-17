#include <stdio.h>

int calc(double *base,double *des,double *p){
    double a[2]={des[0]-base[0],des[1]-base[1]};
    double b[2]={p[0]-base[0],p[1]-base[1]};
    return a[0]*b[1]-a[1]*b[0];
}
int main(void){
    double A[2],B[2],C[2],P[2],ans1,ans2,ans3;
    for(;~scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&A[0],&A[1],&B[0],&B[1],&C[0],&C[1],&P[0],&P[1]);){
        ans1=calc(A,B,P);ans2=calc(B,C,P);ans3=calc(C,A,P);
        if((ans1<0.0 && ans2<0.0 && ans3<0.0) || (ans1>=0.0 && ans2>=0.0 && ans3>=0.0))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}