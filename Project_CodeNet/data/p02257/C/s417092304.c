#include<stdio.h>
#include<math.h>
#define N 10000

int main(void)
{
  int n;
  //printf("n:");
  scanf("%d",&n);

  int x[N];
  int cnt[N]={};
  int i;
  int cntp=0;

  for(i=0;i<n;i++){
    //printf("number:");
    scanf("%d",&x[i]);
  }
  
  double rtx[n];

  for(i=0;i<n;i++)
    rtx[i]=sqrt(x[i]);

  int j;
  for(i=0;i<n;i++){
    if(x[i]%2==1){
      for(j=2;j<=rtx[i]+1;j+=1){
	if(x[i]%j==0){
	  cnt[i]++;
	}
      }
    }
    else{
      cnt[i]++;
    }
  }

  for(i=0;i<n;i++){
    if(x[i]!=1&&cnt[i]==0) cntp++;
  }
  for(i=0;i<n;i++){
    if(x[i]==2) cntp++;
  }

  //printf("The number of prime numbers:%d\n",cntp);
  printf("%d",cntp);

  return 0;
}
