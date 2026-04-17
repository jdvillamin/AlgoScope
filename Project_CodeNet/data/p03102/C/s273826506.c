#include <stdio.h>

int main(){
  int N,M,C,ans=0,val;
  scanf("%d %d %d",&N,&M,&C);
  int B[N];
  int A[N][M];
  for(int i=0; i<M; i++){
    scanf("%d",&B[i]);
  }
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      scanf("%d", &A[i][j]);
    }
  }

  for(int i=0; i<N; i++){
    val =0;
    for(int j=0; j<M; j++){
      val += A[i][j]*B[j];
    }
    val += C;
    if(val > 0){
      ans += 1;
    }
  }
  printf("%d\n",ans);
  return 0;
}
