#include<stdio.h>

int main(){
  int n, tmp;
  scanf("%d", &n);
  int a[n + 1];
  for(int i = 0;i < n;i++){
    a[i] = 0;
  }
  for(int i = 1;i < n;i++){
    scanf("%d", &tmp);
    a[tmp - 1]++;
  }
  for(int i = 0;i < n;i++){
    printf("%d\n", a[i]);
  }

  return 0;
}