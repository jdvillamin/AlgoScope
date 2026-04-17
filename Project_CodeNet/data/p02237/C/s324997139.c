#include<stdio.h>
#define  n 101

int main(){
  int G[n][n];
  int i , j ,a,b,c,d;
  scanf("%d",&d);
  for(i#include<stdio.h>
#define  n 101

int main(){
  int G[n][n];
  int i , j ,a,b,c,d;
  scanf("%d",&d);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      G[i][j]=0;
    }
  }
  for(i=0;i<d;i++){
    scanf("%d%d",&a,&b);
    for(j=0;j<b;j++){
      scanf("%d",&c);
      G[i][c-1]=1;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      printf("%d",G[i][j]);
      if(j<d-1){
	printf(" ");
      }
    }
      printf("\n");
    


  }
    return 0 ;
}