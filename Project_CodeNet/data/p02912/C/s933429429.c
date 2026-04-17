#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


int N,M;
int *A,fact[31],**count;

int dp(int n,int m)
{
  int temp,k;
  int s;
  
  if(count[n][m]!=-1)
  {
    return count[n][m];
  }
  else
  {
    temp=dp(n-1,m)+A[n];
    
    for(s=1;s<m+1;s++)
    {
      if(s<31)
      {
        k=dp(n-1,m-s)+A[n]/fact[s];
      }
      else
      {
        k=dp(n-1,m-s);
      }
      
      if(temp>k)
      {
        temp=k;
      }
    }

  }
  count[n][m]=temp;
  
  return temp; 

  
}


int main()
{
  
  int i,j;
  scanf("%d %d",&N,&M);
  
  A=(int *)malloc(sizeof(int )*(N+1)); 

  
  count=(int **)malloc(sizeof(int * )*(N+1));
  for(i=0;i<N+1;i++)
  {
    count[i]=(int *)malloc(sizeof(int )*(M+1));
  }


  
  for(i=1;i<N+1;i++)
  {
    scanf("%d",&A[i]);
  }
  
  for(i=0;i<N+1;i++)
  {
    for(j=0;j<M+1;j++)
    {
      count[i][j]=-1;
    }
  }
  
  fact[0]=1;
  for(i=1;i<31;i++)
  {
    fact[i]=fact[i-1]*2;
  }

  
  for(i=0;i<M+1;i++)
  {
    count[0][i]=0;
  }

  printf("%d",dp(N,M));
  
  
 return 0; 
}