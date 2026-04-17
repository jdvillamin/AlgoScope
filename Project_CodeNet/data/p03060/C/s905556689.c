#include <stdio.h>
int main(){
  int n,i,a[20],b[20],result;
  
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",a[i]);
  }
  for(i=0;i<n;i++){
    scanf("%d",b[i]);
  }
  
  result=0;
  for(i=0;i<n;i++){
    if(a[i]>b[i]){
      result+=(a[i]-b[i]);
    }
  }
  
  printf("%d",result);
}