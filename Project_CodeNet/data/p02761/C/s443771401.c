#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int powx(long long int x,long long int y){
  int j;
  int a;
  a=1;
  for(j=1;j<y+1-x;j++){
   a=a*10;
  }
  return(a);
}


int main(){

 long long int N,M;
  scanf("%lld %lld",&N,&M);

/*
  char A[];
  scanf("%s",A);
  */

  
  long long int s[M+1],c[M+1],che[N+1];
  long long int i;
  for(i=1;i<=M;i++){
   scanf("%lld %lld",&s[i],&c[i]);
   }
  
  long long int A;
  A=0;
  for(i=1;i<=N;i++){
    che[i]=-1;
   }

  for(i=1;i<=M;i++){

    if(che[s[i]]==-1){
      che[s[i]]=c[i];
      A += c[i]*powx(s[i],N);
    }
    else if( che[s[i]] != c[i]){
      printf("-1");
      return(0);
    }
    else{}


   }  
  if(N == 1 && A == 0){
    printf("0");
  }

  else if(che[1] ==-1 || che[1]==0){
    printf("-1");
  }
  else{
    printf("%lld",A);
  }





 return(0);
 }
