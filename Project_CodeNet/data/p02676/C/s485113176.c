#include <stdio.h>
#include <string.h>

int main(void)
{
  int k;
  char s1[100];
  char s2[100];
  scanf("%d", &k);
  scanf("%s", s1);
  int i = strlen(s1);
  if(i<=k){
    printf("%s\n", s1);
  } else {
    strncpy(s2,s1,k);
    s2[k]='\0';
    printf("%s...\n", s2);
  }
  return 0;
}
