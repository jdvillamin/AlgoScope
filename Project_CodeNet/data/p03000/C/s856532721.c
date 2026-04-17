#include <stdio.h>

int main(){
  int N,X;
  int L[101];
  scanf("%d %d",&N,&X);
  int cnt = 0;
  int D = 0;
  for(int i=0; i<N; i++){
    scanf("%d",&L[i]);
    if(D <= X){
     cnt++; 
    }
    D += L[i];
  }
  printf("%d\n",cnt);
}