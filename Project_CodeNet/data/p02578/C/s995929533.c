#include<stdio.h>
int main(void){
  int n,ans=0,i;
  scanf("%d",&n);
  int a[n];
  for(i=0;i<n;i++)scanf("%d",a[i]);
  for(i=1;i<n;i++){
    if(a[i-1]-a[i]>0)ans=ans+a[i-1]-a[i];a[i]=a[i]+a[i-1]-a[i];
  }
  printf("%d",ans);
  return 0;
}
