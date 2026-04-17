#include<stdio.h>
#include<stdlib.h>

int main(){
  int n = 0;
  int h[100000] = {};
  int i = 0;
  int k = 0;
  int flag = 0;
  scanf("%d",&n);
  for(i = 0;i<n;i++){
    scanf("%d",&h[i]);
  }
  
  for(i = 0;i < n-1;i++){
   	if(h[n-1-i]<h[n-2-i]){
      h[n-2-i]--;
      if(h[n-1-i]<h[n-2-i]){
        flag = 1;
        break;
      }
    }
  }
  if(flag){
    printf("No");
  }else{
    printf("Yes");
  }
  return 0;
}
    
	

