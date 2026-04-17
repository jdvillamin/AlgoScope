#define MAX 100
#define INF 168435450

typedef struct node{
 int flg;
 int cost;
}node;

int min(int a,int b){
if(a < b)return a;
return b;
}

int min_idx(node N[],int n){
int idx;
int i;
int mini=268435450;

for(i=0;i<n;i++){
 if(N[i].flg==0 && N[i].cost<mini){
   mini=N[i].cost;
   idx=i;
 }
}

return idx;
}

int main(){
int n,x,y,d;
int i,j,k,u;
int Dis[MAX][MAX];
node N[MAX];

scanf("%d",&n);

for(i=0;i<n;i++){N[i].flg=0;N[i].cost=INF;
 for(j=0;j<n;j++){
  Dis[i][j]=INF;
  if(i==j)Dis[i][j]=0;
 }
}

for(i=0;i<n;i++){
 scanf("%d %d",&x,&k);
 for(j=0;j<k;j++){
  scanf("%d %d",&y,&d);
  Dis[x][y]=d;
 }
}

N[0].cost=0;

for(i=0;i<n;i++){
 u=min_idx(N,n);

 if(N[u].flg==0){
    N[u].flg=1;
    for(j=0;j<n;j++){
     if(Dis[u][j]!=INF){
      N[j].cost=min(N[j].cost,N[u].cost+Dis[u][j]);
     }
    }
 }
}

for(i=0;i<n;i++)
 printf("%d %d\n",i,N[i].cost);

return 0;
}

