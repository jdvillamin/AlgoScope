#include <stdio.h>

int main()
{
int N;
int sum = 0;

scanf("%d", &N);

while(N > 0){

 sum += N%10;
  N = N/10;
}

if (sum%9 == 0){
  printf("Yes");
}else if(sum%9 != 0){
  printf("No");
}

    return 0;
}
