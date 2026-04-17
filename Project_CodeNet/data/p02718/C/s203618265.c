#include <string.h>
#include <stdio.h>
int main(void){
  int n=0;
  int m=0;
  int a[1000];
  int i;
  int t=0;
  int total=0;
  while(n<1 || n>100){scanf("%d",&n);}
  while(m<1 || m>n){scanf("%d",&m);}
  for(i=0;i<n;i++){
    while(a[i]<1 || a[i]>1000){scanf("%d",&a[i]);}
    total=total+a[i];
  }
  for(i=0;i<n;i++){if(a[i]<=total/(4*m));
                  else t++;}
  if(t>=m)printf("Yes");
  else printf("No");
  return 0;
}
