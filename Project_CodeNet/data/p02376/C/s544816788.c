#include<stdio.h>
#include<stdlib.h>
  
typedef struct{
  int fmax;
  int flow;
  int n[2];
}TEdge;
  
typedef struct{
  int num;
  int e[1200];
}TVertex;
  
TEdge e[1200];
TVertex v[120];
#define MIN(x,y) ((x)<(y)?(x):(y))
int V,E;
int et[120];
int route(int s, int ed,int c){
  int res=0,r,m,i;
  //printf("{%d,%d",s,c);
  r=-1;
  et[s]=1;
  for(i=0;i<v[s].num;i++){
    if(e[v[s].e[i]].n[0]==s){
      if(et[e[v[s].e[i]].n[1]]==0){
        if(e[v[s].e[i]].fmax-e[v[s].e[i]].flow>0){
          m=MIN(c,e[v[s].e[i]].fmax-e[v[s].e[i]].flow);
          if(e[v[s].e[i]].n[1]==ed){
            r=m;
            e[v[s].e[i]].flow+=r;
            //printf(":%d}",r);
            res+=r;
            if(res>=c){
              et[s]=0;
              //printf("}");
              return res;
            }
            c-=r;
          }
          r=route(e[v[s].e[i]].n[1],ed,m);
          if(r>0){
            e[v[s].e[i]].flow+=r;
            //printf("}");
            res+=r;
            if(res>=c){
              et[s]=0;
              return res;
            }
            c-=r;
          }
        }
      }
    }else{
      if(et[e[v[s].e[i]].n[0]]==0){
        if(e[v[s].e[i]].flow>0){
          m=MIN(c,e[v[s].e[i]].flow);
          r=route(e[v[s].e[i]].n[0],ed,m);
          if(r>0){
            e[v[s].e[i]].flow-=r;
            res+=r;
            if(res>=c){
              et[s]=0;
              //printf("}");
              return res;
            }
            c-=r;
          }
        }
      }
    }//*/
  }
  et[s]=0;
  //printf(":-1}");
  return res;
}
  
int main(){
  int i;
  int res;
  scanf("%d %d",&V,&E);
  for(i=0;i<V;i++){
    v[i].num=0;
  }
  for(i=0;i<E;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    e[i].n[0]=a;
    e[i].n[1]=b;
    v[a].e[v[a].num++]=i;
    v[b].e[v[b].num++]=i;
    e[i].fmax=c;
    e[i].flow=0;
  }
  //return 0;
  res=0;
    for(i=0;i<100;i++){
      et[i]=0;
    }
  while(1){
    int x;
    x=route(0,V-1,100000);
    if(x<=0){
      printf("%d\n",res);
      return 0;
    }
    res+=x;
  }
  return 0;
}