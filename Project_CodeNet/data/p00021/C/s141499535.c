#include<stdio.h>
#include<math.h>


int main(void){

  int n;
  double x[4], y[4];
  double ab[2], cd[2];

  
  scanf("%d", &n);
  while(n>0){
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);

    ab[0]=x[1]-x[0];
    ab[1]=y[1]-y[0];

    cd[0]=x[3]-x[2];
    cd[1]=y[3]-y[2];


    if(fabs(ab[0]*cd[1]-ab[1]*cd[0])<1e-10){
      printf("YES\n");
    }
    else{
      printf("NO\n");
    }
    

    n--;
  }

  return(0);
}

