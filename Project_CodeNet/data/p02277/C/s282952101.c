#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
  char sub;
  int figure;
  int order;
}card;

int partition(card*,int,int);
void quicksort(card*,int,int);
void swap(card*,int,int);
bool stablenor(card*,int);
int main(){
  int n,i,temp,r,l,flag=0;
  int *stablejudge;
  card *list;
  scanf("%d",&n);
  list=(card*)malloc(n*sizeof(card));
for(i=0;i<n;i++){
  scanf("%*c%c%d",&((list+i)->sub),&((list+i)->figure));
  ((list+i)->order)=i;
}
  r=n-1;
  l=0;
quicksort(list,l,r);
printf("%s\n",(stablenor(list,n)!=true)?"Not stable":"Stable");
  for(i=0;i<n;i++)printf("%c %d\n",((list+i)->sub),((list+i)->figure));
  return 0;
}
int partition(card *l,int left,int right){
int i;
  for(i=left;i<right;i++){
    if((l+right)->figure>=(l+i)->figure){
      swap(l,i,left);
      left++;
    }
  }
  swap(l,left,right);
  return left;
}
void quicksort(card *l,int left,int right){
int q;
  if(left<right){
    q=partition(l,left,right);
    quicksort(l,left,q-1);
    quicksort(l,q+1,right);
  }
}
void swap(card *x,int a,int b){
  card c;
  c=*(x+a);
  *(x+a)=*(x+b);
  *(x+b)=c;
}
bool stablenor(card *l,int n){
  while(n-1){
    if(((l+(n-2))->figure)==((l+(n-1))->figure)&&((l+(n-2))->order)>((l+(n-1))->order))return false;
    n--;
  }
  return true;
}

