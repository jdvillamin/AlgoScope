#include<stdio.h>
#define N 20//the maximum number of first elements
int solve(int[],int,int,int);
int main(void)
{
  int i;//counter
  int n;//the number of elements that can be used
  int arr[N];//input of second line
  int q;//the number of elements judged
  int x;//input of forth line
  scanf("%d",&n);
  for(i=0;i<n;i++) scanf("%d",&arr[i]);
  scanf("%d",&q);
  for(i=0;i<q;i++)
    {
      scanf("%d",&x);
      if(solve(arr,n,0,x)==1) printf("yes\n");
      else printf("no\n");
    }
  return 0;
}
int solve(int arr[],int n,int p,int t)//checks whether we can make t by selecting after p-th element (inclusive)
{
  int i;//counter
  //printf("solve(arr,%d,%d,%d)\n",n,p,t); //debugging
  if(t==arr[p]) return 1;
  if(p>=n||t<0) return 0;
  for(i=p+1;i<n;i++)
    {
      if(solve(arr,n,i,t-arr[p])==1) return 1;
    }
  if(solve(arr,n,p+1,t)==1) return 1;
  return 0;
}
