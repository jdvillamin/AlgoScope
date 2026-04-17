#include<stdio.h>
int main(){

  int n,i,j,box,c=0,x=0;
  int G[101][101],a[101],k[101],p[101];

  scanf("%d",&n);

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      scanf("%d",&G[i][j]);

  k[0] = 0;

  for(i=0;i<n;i++){
    a[i] = 0;
    p[i] = -1;

    if(i!=0)k[i]=2001;
  }

  while(x != 2001){
    x = 2001;
    for(i = 0; i < n; i++){
      if(a[i] != 2 && k[i] < x){
	box = i;
	x = k[i];
      }
    }
    
    a[box]=2;
    for(i=0 ; i<n ; i++){
      if(G[box][i] != -1 && a[i] != 2 && G[box][i] < k[i]){
        a[i] = 1;
	p[i] = box;
	k[i] = G[box][i];
      }
    }
  }
  
  for(i=0 ; i<n ; i++){
    if(p[i] != -1){
      c += G[i][p[i]];
    }
  }
  
  printf("%d\n",c);
  
  return 0;
}