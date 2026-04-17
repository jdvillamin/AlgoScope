#include<stdio.h>
 
int main(void)
{
  int N, K, num1, num2;
  int flag = 0;
  
  scanf("%d %d", &N, &K);
  
  num1 = N % K;
  
  num2 = num1 - K;
  
  if(num2 < 0)
    num2 *= -1;
  
  if(num1 < num2)
    printf("%d\n", num1);
  
  else
    printf("%d\n", num2);
  
  return 0;
}