#include<stdio.h>
#include<math.h>

int main(void){
 	int num=0;
  	int co=0;
  	int max=0;
  	int min=999999;
  	scanf("%d %d",&num,&co);
    int h[co];
  	for(int i;i<co;i++){
     scanf("%d",&h[i]); 
      if(h[i]>max){
      	max=h[i];
      }
      else if(h[i]<min){
      	min=h[i];
      }
    }
  int re=max-min;
  printf("%d",re);
}
