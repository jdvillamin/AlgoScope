#include <stdio.h>
#include <stdlib.h>

void SimSelSort(int num[ ], int n,int K);
void tyoku(int num [ ],int n, int K);

int main(void){
  int N;
  int K;
  int a[10000] = {};
  int i=0; 
  int b;

  scanf("%d",&N);

  scanf("%d",&K);

  for(i;i<N;i++){

   scanf("%d",&b);
   a[i]=b;
  }
 
  //SimSelSort(a,N,K);
  
  tyoku(a,N,K);

}

void SimSelSort(int num[ ], int n,int K)
{
  int i, j, k, min, temp;
  int time=0;
  int sum=0;
  int kazu=1;

    for (i = 0; i < n - 1; i++) {
        min = num[i];                
        k = i;                       
        for (j = i + 1; j < n; j++) {
            if (num[j] < min) {      
                min = num[j];        
                k = j;                
            }
        }                             
        temp = num[i];                
        num[i] = num[k];
        num[k] = temp;
    }
    for(time=1; time<n;++time){
      if(num[time]==kazu){
	kazu++;
      }
     
      if(kazu-1==K){
      printf("%d\n",K);
      break;      
      } 
    }   
   
    if(kazu-1<K){
      printf("0\n");       
    }   

}


void tyoku(int num [ ],int n, int K)
{
  int i;
  int cp[10000]={};
  for(i=0;i<n;i++){
    cp[num[i]]=num[i];
    
  }
  
  for(i=1;i<=K;i++){
    if(cp[i]!=i){
       printf("0\n");    
       exit(0);
    }
  } 
 
  printf("%d\n",K);


}