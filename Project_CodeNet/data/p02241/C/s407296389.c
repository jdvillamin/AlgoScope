#include<stdio.h>

#define MAX 100
#define INF 2001
#define NIL -1
#define WHITE 1
#define BLACK 2

void prim(int,int);

int d[MAX],pi[MAX],color[MAX];
int G[MAX][MAX];

int main(){
  int i,j,n,sum;

  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++) scanf("%d",&G[i][j]);
  }

  prim(n,0);

  sum=0;

  for(i=0;i<n;i++){
    if(pi[i]!=NIL) sum+=G[i][pi[i]];
  }

  printf("%d\n",sum);

  return 0;
}

void prim(int n,int r){
  int i,u,mincost;

  for(i=0;i<n;i++){
    d[i]=INF;
    pi[i]=NIL;
    color[i]=WHITE;
  }

  d[r]=0;

  while(1){
    mincost=INF;
    for(i=0;i<n;i++){
      if(color[i]!=BLACK && d[i]<mincost){
	mincost=d[i];
	u=i;
      }
    }

    if(mincost==INF) break;

    color[u]=BLACK;

    for(i=0;i<n;i++){
      if(G[u][i]==-1) continue;
      if(color[i]!=BLACK && G[u][i]<d[i]){
	pi[i]=u;
	d[i]=G[u][i];
      }
    }
  }
}
	

