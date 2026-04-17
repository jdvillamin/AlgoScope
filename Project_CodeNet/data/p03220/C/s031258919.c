#include <stdio.h>
#include <math.h>
int main(){
  int i,N,ans;
  double A,T,H[100000],S[100000],subm=99999;
  scanf("%d",&N);
  scanf("%lf %lf",&T,&A );
  for(i=1;i<N+1;i++){
  scanf("%lf",&H[i] );
  S[i]=T-H[i]*0.006;
  S[i]=fabs(A-S[i]);
  if(S[i]<subm){
  subm=S[i];
  ans=i;
}
}
printf("%d",ans);
}


