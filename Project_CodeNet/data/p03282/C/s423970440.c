#include<stdio.h>
int main(){
  char s[110],a[2];
  long long int k;
  int i=0;
  scanf("%s%lld",s,&k);
  for(i=0;i<k;i++){
    if(s[i]!='1'){
      printf("%c\n",s[i]);
      return 0;
    }
  }
  printf("%c\n",s[i]);
  return 0;
}