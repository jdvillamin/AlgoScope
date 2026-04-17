#include<stdio.h>

int main()
{
  int r,c,i,j,k,sum,input[100][100];
  sum=0;
  while(1){
    scanf("%d %d",&r,&c);
    if(1<=r && c<=100) break;
  }

  for(i=0;i<r;i++){
    for(j=0;j<c;j++){
      state :
      scanf("%d",&input[i][j]);
      if(0>input[i][j] || input[i][j]>100) goto state;
    }
  }

  for(i=0;i<r;i++){
    for(j=0;j<c;j++) sum+=input[i][j];
    input[i][c]=sum;
    sum=0;
  }

  for(i=0;i<=c;i++){
    for(j=0;j<r;j++) sum+=input[j][i];
    input[r][i]=sum;
    sum=0;
  }

  for(i=0;i<=r;i++){
    for(j=0;j<=c;j++){
      printf(" %d",input[i][j]);
    }
    printf("\n");
  }

  return 0;

}