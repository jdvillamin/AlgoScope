#include<stdio.h>
#define N 101
#define WHITE 0
#define GRAY 1
#define BLACK 2

int f[N],d[N],color[N],id[N][N],time,n;

void visit(int u){
  int i;
  color[u] = GRAY;
  d[u] = ++time;
  for(i=1 ; i<=n ; i++){
    if(id[u][i] == 1){
      if(color[i] == WHITE) visit(i);
    }}
  color[u] = BLACK;
  f[u] = ++time;
} 



void dfs(void){
  int i;
  for(i=1 ; i<=n ; i++){
    color[i] = WHITE;
  }
  time = 0;
  for(i=1 ; i<=n ; i++){
    if(color[i] == WHITE) visit(i);
  }
}

 
int main(){
  int u,k,v,i,j;
    
  scanf("%d",&n);
  for(i=1 ; i<=n ; i++){
    for(j=1 ; j<=n ; j++){
      id[i][j] = 0;
    }}
    
  for(i=1 ; i<=n ; i++){
    scanf("%d%d",&u,&k);
    for(j=1 ; j<=k ; j++){
      scanf("%d",&v);
      id[u][v] = 1;
    }
  }

  dfs();
  
  for(i=1 ; i<=n ; i++){
    printf("%d %d %d\n",i,d[i],f[i]);
  }
  return 0;
}

  

