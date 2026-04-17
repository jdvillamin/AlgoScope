#include<stdio.h>
int main(){
  int A[10][10];
  int i,j;
  int H,W,h,w;
  
  scanf("%d %d",&H,&W);
  scanf("%d %d",&h,&w);
  
  int ans;
  ans=H*W-(h*W+w*H-h*w);
  printf("%d",ans);
  return 0;
}