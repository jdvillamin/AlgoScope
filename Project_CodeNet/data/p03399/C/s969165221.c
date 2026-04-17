#include<stdio.h>
int main(void){
int A,B,C,D,tmp1=0,tmp2=0,min=0;
  scanf("%d%d%d%d",&A,&B,&C,&D);
  if(A>=B){
    min+=B;
    tmp1=B;
  }else{
      min+=A;
      tmp1=A;
  }
  if(C>=D){
      min+=D;
      tmp2=D;
  }else{
      min+=C;
      tmp2=C;
  }
  printf("%d+%d=%d",tmp1,tmp2,min);
  return 0;
}