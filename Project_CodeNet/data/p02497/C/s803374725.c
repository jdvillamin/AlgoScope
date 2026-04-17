#include <stdio.h>
int m,f,r;
int main(){
  for(;~scanf("%d%d%d",&m,&f,&r)&&m!=-1&&f!=-1;){
    m+=f;
    printf("%c\n",m>79?'A':m>64?'B':m>49?'C':r>49?'C':m>29?'D':'F');
  }
  return 0;
}