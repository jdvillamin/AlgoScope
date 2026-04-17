#include <stdio.h>

int main(void) {

  char s[10], t[11];
  int i,flag=0;

  scanf("%s%s", s,t);

  for(i=0;i<11;i++){
    if(s[i]=='\0') break;
    if(s[i]!=t[i]) flag=1;
  }

  if(flag==0) printf("Yes");
  else printf("No");

  return 0;
}
