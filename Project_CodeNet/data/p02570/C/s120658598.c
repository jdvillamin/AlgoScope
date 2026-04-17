#include<stdio.h>
int main(){
  int answer,b,c,d,t,s;
  scanf("%d %d %d",&d,&t,&s);
  answer=d/s;
  if(answer<=t){
    printf("Yes");
  }
  else{
    printf("No");
  }
  return 0;
}