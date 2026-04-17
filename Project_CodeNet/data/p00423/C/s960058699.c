#include <stdio.h>

int main(){
  int n, a=0, b=0, i, j, k=0;
  int x[256], y[256],z[256][2];

  while(1){
    scanf("%d",&n);
    if(n==0)break;

    for(i=0; i<n ; i++){
      scanf("%d%d",&x[i],&y[i]);
    }

    for(j=0; j<i; j++){
      if(x[j]<y[j]){
	b+=x[j]+y[j];
      }
      else if(x[j]==y[j]){
	a+=x[j];b+=y[j];
      }
      else{
	a+=x[j]+y[j];
      }
    }
    z[k][0]=a;
    z[k][1]=b;
    k++;
    a=0;b=0;
  }


  for(i=0;i<k;i++){
    printf("%d %d\n",z[i][0],z[i][1]);
  }

  return 0;
}