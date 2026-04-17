#include<stdio.h>
#include<math.h>
long long MAX(long long a,long long b){return a<b?b:a;}
double PI=acos(-1);
int main(){
  int n,i,j;
  long long x[110],y[110],m=0,sx,sy;
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%lld %lld",&x[i],&y[i]);
  for(i=0;i<n;i++){
    sx=sy=0;
    for(j=0;j<n;j++){
      if(x[i]*x[j]+y[i]*y[j]>=0){
	sx+=x[j];
	sy+=y[j];
      }
    }
    m=MAX(m,sx*sx+sy*sy);
  }
  printf("%.12lf\n",sqrt(m));
  return 0;
}
	
    
