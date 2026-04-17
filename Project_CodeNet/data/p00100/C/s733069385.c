#include <stdio.h>
#define N 4000

int main (void){
  int x,y,z;
  int data[N][2];
  int i, j, k;
  for(;;){
    for(i=0;i<N;i++){
      data[i][0] =0;
      data[i][1] =0;
    }
    scanf("%d",&i);
    if(i == 0)break;
    for(j=0,k=0;j<i;j++){
      scanf("%d %d %d",&x,&y,&z);
      data[x][0] += y*z;
      if(data[x][0] >=1000000){
        printf("%d\n",x);
        k =1;
        data[x][1] =1;

      }
    }
    if(k==0)printf("NA\n");
  }
  return 0;

}