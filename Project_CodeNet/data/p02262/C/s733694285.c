#include<stdio.h>

int cnt = 0;
void insertionSort(int* A, int n, int g){
  int i,v,j;
  for(i=g;i<=n-1;i++){
    v = A[i];
    j = i - g;
    while(j>=0 && A[j] > v){
      A[j+g] = A[j];
      j = j-g;
      cnt++;
    }
    A[j+g] = v;
  }
  return;
}

void shellSort(int* A,int n){
  cnt = 0;
  int m=0 ,i=0,a;
  int G[n];
  G[0]=1;
  for(a=0;a<n/2;a++){
    G[a+1]=3*G[a]+1;
    m++;
    
  }

  for(i = 0;i<=m-1;i++){
    insertionSort(A,n,G[i]);
  }
  printf("%d\n",m);
  for(i = 0;i<m;i++){
    if(i!=0) printf(" ");
    printf("%d",G[i]);
  }
  printf("\n");
  printf("%d\n",cnt);
  for(i=0;i<n;i++){
    printf("%d\n",A[i]);
  }
}

int main(){
  int n,i,A[1000000];
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
  }
  shellSort(A,n);
  return 0;
}
  