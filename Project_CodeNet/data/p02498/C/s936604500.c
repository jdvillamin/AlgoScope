#include <stdio.h>
main(){
  char ch;
  while(1){
    scanf("%c",&ch);
    if(islower(ch)){
     ch=toupper(ch);
	}
    else if(isupper(ch)){
      ch=tolower(ch);
	}
    printf("%c",ch);
  }
  return 0;
}
      