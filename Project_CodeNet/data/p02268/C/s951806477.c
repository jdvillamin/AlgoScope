#include <stdio.h>
#include <stdlib.h>
#define NOT_FOUND -1

int binarySearch(int);

int n,*S,q,*T;
int main(){
  int C=0,i,j,key;
  scanf("%d",&n);
  S=(int *)malloc(sizeof(int)*n);
  for(i=0;i<n;i++) scanf("%d",&S[i]);
  
  scanf("%d",&q);
  T=(int *)malloc(sizeof(int)*q);
  for(i=0;i<q;i++) scanf("%d",&T[i]);

  

  while(j!=q){
    key=T[j];
    if(binarySearch(key)!=NOT_FOUND) C++;
    j++;
  }
  
  printf("%d\n",C);
  return 0;
}

int binarySearch(int key){
  int left=0;
  int right=n;
  int mid;
  while(left<right){
    mid=(left+right)/2;
    if(S[mid]==key){
      return mid;
    }else if(key<S[mid]){
      right=mid;
    }else{
      left=mid+1;
    }
  }
  return NOT_FOUND;
}

