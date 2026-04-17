#include<stdio.h>
int main(){
  int n,r,l,id,t,p,s=0,mi=1,max=0;
  int i,j;
  scanf("%d %d %d",&n,&r,&l);
  int d[100000][2]={0};
  for(i=0;i<r;i++){
    scanf("%d %d %d",&id,&t,&p);
    d[id][0]+=p;
    d[mi][1]+=t-s;
    s=t;
    if(p>0){
      if(max<d[id][0]){
	max=d[id][0];
	mi=id;
      }
      else if(max==d[id][0]&&mi>id)mi=id;
    }
    else{
      max=d[1][0];
      mi=1;
      for(j=2;j<=n;j++){
	if(max<d[j][0]){
	  max=d[j][0];
	  mi=j;
	}
      }
    }
    /*for(j=0;j<n;j++)printf("\t%d",d[j+1][0]);
    printf("\n");
    for(j=0;j<n;j++)printf("\t%d",d[j+1][1]);
    printf("\n\n");*/
  }
  d[mi][1]+=l-t;
  max=d[1][1];
  mi=1;//printf("\t%d",d[1][1]);
  for(i=2;i<=n;i++){//printf("\t%d",d[i][1]);
    if(max<d[i][1]){
      max=d[i][1];
      mi=i;
    }
  }
  printf("%d\n",mi);
  return 0;
}