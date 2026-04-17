#include<stdio.h>
int main(){
  int n,count=0,res=0;
  int h[100000];
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%d",&h[i]);
  }
  
  for(int i=0;i<n;i++){
    count=0;
    for(int j=i;j<n-1;j++){
      
      if(h[j]>=h[j+1]){
        count++;
      }else{
        count=0;
      }
    }
    if(count>res) res=count;
  }
  printf("%d",res);
  return 0;
}