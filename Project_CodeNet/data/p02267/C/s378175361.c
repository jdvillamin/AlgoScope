#include<stdio.h>

 int search(int n,int S[],int q){
          int i;
          S[n]=q;
          i=0;
          while(S[i] != q)i++;
          return i != n;
          }
       

 int main(){
          int i,n,q,S[10001],T[501],cnt=0,j;

          scanf("%d",&n);
          for(i=0;i<n;i++){
                    scanf("%d",&S[i]);
                    }
          scanf("%d",&q);
          for(i=0;i<q;i++){
                    scanf("%d",&T[i]);
                    if(search(n,S,q))cnt++;
                    }
          printf("%d\n",cnt);
          return 0;
          }
