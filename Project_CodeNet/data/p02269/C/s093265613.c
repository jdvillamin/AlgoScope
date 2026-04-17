#include<stdio.h>
#include<string.h>

#define M 100000
#define L 12

void insert(int *str);
int find(int *str);

char H[M][L];
int a=0;


int main(){
  int i,n;
  char str[L],com[9];
  for(i=0;i<M;i++)
    H[i][0]='\0';

  scanf("%d",&n);

  for(i=0;i<n;i++){
    scanf("%s%s",com,str);

    if(com[0]=='i'){
      insert(str);
    }
    else{
      if(find(str)==1){
        printf("yes\n");
      }
      else{
        printf("no\n");
      }
    }
  }
  return 0;
}

void insert(int *str){
  strcpy(H[a],str);
  a++;
}

int find(int *str){
  int i;
  for(i=0;i<a;i++){
    if(strcmp(H[i],str)==0)
      return 1;
  }
  return 0;
}