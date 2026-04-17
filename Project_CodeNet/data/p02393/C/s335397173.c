#include<stdio.h>
#define N 3
void ascendingSort(int,int[]);
void printArray(int,int[]);
int main(void)
{
  int i;
  int arr[N];
  for(i=0;i<N;i++) scanf("%d",&arr[i]);
  ascendingSort(N,arr);
  printArray(N,arr);
  return 0;
}
void ascendingSort(int n,int arr[])
{
  int i,j;
  int key;
  for(i=1;i<n;i++)
    {
      key=arr[i];
      for(j=i-1;j>=0;j--)
        {
          if(key<arr[j]) arr[j+1]=arr[j];
          else break;
        }
      arr[j+1]=key;
    }
}
void printArray(int n,int arr[])
{
  int i;
  for(i=0;i<n;i++)
    {
      if(i>0) printf(" ");
      printf("%d",arr[i]);
    }
  printf("\n");
}

