#include <stdio.h>

int main(int argc, char const *argv[]) {
  int a,b;
  scanf("%d\n", &a);
  for (b = 3 ; b <= a ; b++) {
    if (a % b == 0){
      break;
    }
    else if ( a <= 2 ){
      printf("%d\n", a/b);
      return 0;
    }
  }
  printf("%d\n", a/b);

  return 0;
}
