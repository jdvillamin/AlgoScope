#include<stdio.h>
#define MAX 100
#define W 0
#define G 1
#define B 2

int INFTY = 1<<21;
int n,A[MAX][MAX];

void dijkstra(){
  int min,i,v,u;
  int d[MAX],color[MAX];

  for(i=0;i<n;i++){
    d[i]=INFTY; 
    color[i]=W;
}
  d[0]=0;
  color[0]=G;
  while(1){
    min = INFTY;
    u=-1;
    for(i=0;i<n;i++){
      if(min>d[i]&&color[i]!=B){
	u=i;
	min= d[i];
      }
    }
    if(u==-1) break;
    color[u]=B;
    for(v=0;v<n;v++){
      if(color[v]!=B&&A[u][v]!=INFTY){
	if(d[v]>d[u]+A[u][v]){
	  d[v]=d[u]+A[u][v];
	  color[v]=G;
      }
    }
  }
}
for(i=0;i<n;i++){
    printf("%d ",i);
    if(d[i]==INFTY){
         printf("%d\n",-1);
    }
    else{
         printf("%d\n",d[i]);
    }
    }
}
int main(){
  int i,j,k,c,u,v;
  scanf("%d",&n);

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        A[i][j]=INFTY;
    }
  }
    for(i=0;i<n;i++){
        scanf("%d%d",&u,&k);
        for(j=0;j<k;j++){
            scanf("%d%d",&v,&c);
        A[u][v]=c;
    }
}
dijkstra();
return 0;
}
  

