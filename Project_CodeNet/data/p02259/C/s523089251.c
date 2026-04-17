#include<stdio.h>
int main(void){
  int i,j,k;
  int flag=1;
  int N;
  int a[200];
  int t;
  int count=0;
  scanf("%d",&N);
  for(i=0;i<N;i++)  scanf("%d",&a[i]);

  while(flag==1){
    flag=0;
    for(j=N-1;j>=1;j--){
      if(a[j]<a[j-1]){
        t=a[j];
        a[j]=a[j-1];
        a[j-1]=t;
        flag=1;
        count++;
      }
    }

  }
  for(i=0;i<N-1;i++)  printf("%d ",a[i]);
  printf("%d\n",a[N-1]);
  
  printf("%d\n",count);


  return 0;
}