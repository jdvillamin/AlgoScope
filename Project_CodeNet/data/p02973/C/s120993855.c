#include <stdio.h>

int main()
{
  int i, j, k, n;
  long a[100000];
  long color[100000];
  int numcolor=0;
  scanf("%d", &n);
  for(i=0;i<n;i++){
    scanf("%ld", &a[i]);
    if(numcolor==0){
      color[numcolor]=a[i];
      numcolor++;
    }else{
      if(a[i]<=color[0]){
        for(j=numcolor; j>0; j--){
          color[j]=color[j-1];
        }
        color[0]=a[i];
        numcolor++;
      }else{
        j=0;
        while(color[j]<a[i]) j++;
        color[j-1]=a[i];
      }
    }
  }

  printf("%d\n", numcolor);

  return 0;
}