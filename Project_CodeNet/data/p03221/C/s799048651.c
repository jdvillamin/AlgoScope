#include <stdio.h>
#include<stdlib.h>

int main(){
  int n,m,i,j,k;
  scanf("%d %d",&n,&m);
  int p[m],y[m],x[m];
  for(i=0;i<m;i++){
    scanf("%d %d",&p[i],&y[i]);
    x[i]=1;
  }

  int count,same[n],yet[m],temp;
  for(i=0;i<m;i++){
    yet[i]=0;
  }
  for(j=0;j<m;j++){
    if(yet[j]==0){
      yet[j]=1;
      count = 0;
      same[0]=j;
      for(i=j+1;i<m;i++){
        if(p[i]==p[j]){
          yet[i]=1;
          count+=1;
          same[count]=i;
        }
      }

      if(count>0){
        for(i=0;i<count+1;i++){
          for(k=count;k>i;k--){
            if(y[same[k]]<y[same[k-1]]){
              temp=same[k];
              same[k]=same[k-1];
              same[k-1]=temp;
            }
          }
        }
        for(i=0;i<count+1;i++){
          x[same[i]]=i+1;
        }
      }


    }
  }

  for(i=0;i<m;i++){
    printf("%06d%06d\n",p[i],x[i]);
  }
  return 0;
}
