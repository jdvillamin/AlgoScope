#include<stdio.h>
#include<stdlib.h>

int compare_int(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main(){
  int i,j=0,k=0,N,M;
  scanf("%d %d",&N);
  
  int D[N];
  for(i=0;i<N;i++)
    scanf("%d ",&D[i]);
  scanf("%d",&M);
  int T[M];
  for(i=0;i<M;i++)
    scanf("%d ",&T[i]);
  qsort(D,N,sizeof(int),compare_int);
  qsort(T,M,sizeof(int),compare_int);
  while(k!=M){
    if(D[j] == T[k]){
      j++;
      k++;
    }
    else
      j++;
    if(j==N){
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  return 0;
}