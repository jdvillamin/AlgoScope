#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(void)
{
  int N;
  scanf("%d",&N);
  char str[N][11];
  for(int i=0;i<N;i++){
    scanf("%s",str[i]);
  }
  
  char str1[N][11];
  int count[N],flag=0,tmp2=0;
  for(int i=0;i<N;i++){
    count[i]=0;
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(strcmp(str[i],str1[j])==0){
        tmp2++;
        flag=1;
      }
    }
    if(flag==0){
      for(int k=0;k<11;k++){
        str1[i][k]=str[i][k];
      }
      count[i]=1;
    }
    flag=0;
  }
  int tmp=0;
  for(int i=0;i<N;i++){
    tmp+=count[i];
  }
  
  printf("%d",tmp);
}