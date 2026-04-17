#include<stdio.h>
signed main(){
  char a;
  scanf("%c",&a);
  if(a>='a'&&a<='z'){
    printf("a\n");
  }
  else{
    printf("A\n");
  }
  return(0);
}