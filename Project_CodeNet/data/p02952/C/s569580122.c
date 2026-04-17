#include<stdio.h>
int main(void)
{
  int i,j,k=1,l=1,m=0,o=1,p=1;
  
  for(i=0;i<=4;i++){
    
    for(j=1;j<=i;j++){
       o *= 10;
    }
    
      
    for(l=1;l<=i+1;l++){
       p *= 10;
    }
    
    if((i%2)==0){ 
      m += p-o+1;
    }
    
    o=1;
    p=1;
  }
  
  printf("%d",m);
  
  
  return 0;
}