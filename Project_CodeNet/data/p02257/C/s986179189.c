#include<stdio.h>
#include<math.h>

int n;
long x;

long isprime(x){
  //printf("x;%d\n",x);
  if(x==2){
    return 1;
  }else if(x<2 || x%2==0){
    return 0;
  }

  int i=3;
  while(i<=sqrt(x)){

    if(x%i==0){
      return 0;
    }
    i=i+2;
  }
  return 1;
}


int main(){
  int sum=0;
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%ld",&x);
    if(isprime(x)==1){
      //printf("added!\n");
      sum=sum+1;
    }
  }
  printf("%d\n",sum);


  return 0;
}

