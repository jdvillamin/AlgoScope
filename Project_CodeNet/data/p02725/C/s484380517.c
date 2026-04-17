#include <stdio.h>

int main(void)
{
 int k,n,max = 0,i;
  
 int a[200000];
  
  scanf("%d %d", &k, &n);
  
  for(i=0;i<n;i++)
     scanf("%d", &a[i]);
  
  for(i=0;i<n;i++){
      if(a[i] - a[i-1] > max ){
        max = a[i] - a[i-1];
      }
      if((k-a[i]) + a[0] > max && i == 0){
        max = (k-a[i]) + a[0];
      }
  }
  
  printf("%d", k - max);
  
      return 0;
  
}
