#include<stdio.h>
#define MAX_N 10000000

void push(int);
int pop(void);

int heap[MAX_N],size=0;

int main(void){
  int n,x,i;
  
 scanf("%d",&n);

for(i=0;i<n;i++){
scanf("%d",&x);
    push(x);
  }
for(i=0;i<n;i++)
  printf("%d ",pop());
printf("\n");
  
  return 0;
}

void push(int x){
  int p;
  
  int i=size++;
  
  while(i>0){
    p=(i-1)/2;
    
    if(heap[p]<=x)break;
    
    heap[i]=heap[p];
    i=p;
  }
  heap[i]=x;
}

int pop(void){
  int ret,x,i=0,a,b;
  
  x=heap[--size];
  
  while(i*2+1<size){
    a=i*2+1;
    b=i*2+2;
    
    if(b<size && heap[b]<heap[a])a=b;
    
    if(heap[a]>x)break;
    
    heap[i]=heap[a];
    i=a;
  }
  heap[i]=x;
  
  return ret;
}