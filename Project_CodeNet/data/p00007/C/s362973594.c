#include <stdio.h>

int main(void){
  int n, i;
  int amount=100000, tmp;
  scanf("%d", &n);

  for(i=0;i<n;i++){
    amount *= 1.05;
    tmp = amount % 1000;
    if(tmp){
      amount = amount - tmp + 1000;
    }
  }
  printf("%d\n", amount);
  return 0;
}