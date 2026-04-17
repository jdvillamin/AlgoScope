#include <stdio.h>
#define MAX 100

int chenge;

void SelectionSort(int [],int);
void swap(int [],int,int);

int main(void){
  
  int i,n;
  int A[MAX];
  
  scanf("%d",&n);

  for(i=0;i<n;i++)
    scanf("%d",&A[i]);

  SelectionSort(A,n);

  for(i=0;i<n-1;i++)
    printf("%d ",A[i]);
  printf("%d\n",A[i]);

  printf("%d\n",chenge/2);

  return 0;
}

void SelectionSort(int A[],int n){

  int i,j;
  int mini;

  chenge = 0;

  for(i=0;i<n;i++){
    mini = i;
    for(j=i+1;j<n;j++){
      if(A[j] < A[mini]){
        mini = j;
	chenge=n;   
      }   
    }
    swap(A,i,mini);
  }
}

void swap(int A[],int i,int mini){

  int tmp;

  tmp = A[i];
  A[i] = A[mini];
  A[mini] = tmp; 
}