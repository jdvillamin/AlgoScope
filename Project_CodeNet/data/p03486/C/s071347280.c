#include <stdio.h>
#include <string.h>

int main(void){
  char s[101], t[101], tmp;
  int ls, lt, i, j;
  
  scanf("%s %s", s, t);

  ls = strlen(s);
  lt = strlen(t);
 
  for( i = 0; i < ls; i++){
    for( j = i+1; j < ls; j++){
      if(s[i] > s[j]){
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
      }
    }
  }
  for( i = 0; i < lt; i++){
    for( j = i+1; j < lt; j++){
      if(t[i] < t[j]){
	tmp = t[i];
	t[i] = t[j];
	t[j] = tmp;
      }
    }
  }

  printf("%s %s\n", s, t);
  i = 0;
  while(i < lt){
    if(s[i] < t[i]){
      printf("YES\n");
      break;
    }
    else if(s[i] == t[i]){
      i++;
    }
    else{
      printf("NO\n");
      break;
    }
  }
  if(i == lt)printf("NO");
  return 0;
}
  
