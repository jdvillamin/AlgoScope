#include<stdio.h>
int main(){
  int n;
  scanf("%d",&n);
  int a[n];
  int i,j;
  for(i=0; i<n; i++){
    scanf("%d",&a[i]);}
  for(i=0; i<n-1; i++){
    for(j=0; j<(n-1)-i; j++){
      if(a[j]>a[j+1]){
	int temp=a[j];
	a[j] = a[j+1];
	a[j+1] = temp;
      }
    }
  }
  for(i=0; i<n-1; i++){
    printf("%d ",a[i]);
  }
  printf("%d\n",a[n-1]);
  return 0;
}