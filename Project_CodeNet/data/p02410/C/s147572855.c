#include<stdio.h>

int main(void){
  int i,j,s,n,m;
  static int a[100][100],b[100],c[100];

  scanf("%d%d",&n,&m);

  for(i=0;i<n;i++)
    for(j=0;j<m;j++)
      scanf("%d",&a[i][j]);

  for(i=0;i<m;i++)
    scanf("%d",&c[i]);

  for(i=0;i<n;i++){
    s = 0;
    for(j=0;j<m;j++)
      s += a[i][j] * c[j];
    printf("%d\n",s);
  }
  
  return 0;
}

